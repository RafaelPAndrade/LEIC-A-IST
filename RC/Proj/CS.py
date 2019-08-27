#!/usr/bin/env python3

import socket, sys, getopt, os
from signal import signal, pause, SIGINT, SIGTERM, SIG_IGN
from pickle import load, dump
from multiprocessing import Process
from multiprocessing.managers import SyncManager
from lib.server import tcp_server, udp_server, udp_client
from lib.utils  import (read_bytes_until, DEFAULT_CS_PORT, CS_KNOWN_BS_SAVEFILE,
                        CS_VALID_USERS_SAVEFILE, CS_DIRS_LOCATION_SAVEFILE,
                        backup_dict_to_file, restore_dict_from_file,
                        ignore_sigint, get_best_ip)


# Function to deal with any protocol unexpected error
def unexpected_command(my_socket):
    """ Informs that there was a error. TCP and UDP compatible. """
    my_socket.sendall("ERR\n".encode())


# Code to deal with queries from BS (UDP server)
def deal_with_udp(udp_socket, known_bs):
    def signal_handler(_signum, _frame):
        udp_socket.close()
        exit(0)

    # ignore CTRL-C; handle .terminate() from parent
    signal(SIGINT, SIG_IGN)
    signal(SIGTERM, signal_handler)

    while True:
        response, address = udp_socket.recvfrom(32)
        args = response.decode().split(" ")
        command = args[0]
        args = args[1:]

        if command == "REG":
            add_bs(known_bs, args, udp_socket, address)
        elif command == "UNR":
            remove_bs(known_bs, args, udp_socket, address)
        else:
            unexpected_command(udp_socket)



def add_bs(known_bs, args, udp_socket, address):

    status = "ERR"

    ip_bs = args[0]
    port_bs = args[1].split("\n")[0]

    if len(args) != 2 or port_bs.isdigit() is False:
        print("Error in arguments received from BS server: {} {}".format(ip_bs, port_bs))
    elif (ip_bs, port_bs) in known_bs:
        print("Error: Already added BS {}".format(ip_bs))
        status = "NOK"
    else:
        known_bs[(ip_bs, port_bs)] = 0
        backup_dict_to_file(known_bs, CS_KNOWN_BS_SAVEFILE)
        status = "OK"

    print("-> BS added:\n  - ip: {}\n  - port: {}\n".format(ip_bs, port_bs))
    udp_socket.sendto("RGR {}\n".format(status).encode(), address)


def remove_bs(known_bs, args, udp_socket, address):

    status = "ERR\n"

    ip_bs = args[0]
    port_bs = args[1].split("\n")[0]

    if len(args) != 2 or port_bs.isdigit() is False:
        print("Error in arguments received from BS server: {} {}".format(ip_bs, port_bs))
    elif (ip_bs, port_bs) not in known_bs:
        print("Error: User {} does not exist".format(ip_bs))
        status = "NOK\n"
    else:
        del known_bs[(ip_bs, port_bs)]
        backup_dict_to_file(known_bs, CS_KNOWN_BS_SAVEFILE)
        status = "OK\n"

    print("-> BS removed:\n  - ip: {}\n  - port: {}\n".format(ip_bs, port_bs))
    udp_socket.sendto("UAR {}\n".format(status).encode(), address)




def deal_with_tcp(tcp_socket, valid_users, dirs_location, known_bs):

    def signal_handler(_signum, _frame):
        tcp_socket.close()
        exit(0)


    def deal_with_client(client, valid_users, dirs_location, known_bs):
        """ Code / function for forked worker """

        conn = client[0]
        logged_in = False       # this var is False or contains the user id
        while True:
            try:
                command = read_bytes_until(conn, " \n")

                if command == "AUT":
                    logged_in, password = authenticate_user(valid_users, conn)
                elif command == "DLU" and logged_in:
                    delete_user(logged_in, conn, dirs_location, valid_users)
                    break
                elif command == "BCK" and logged_in:
                    backup_dir(logged_in, conn, known_bs, password, dirs_location)
                    break
                elif command == "RST" and logged_in:
                    restore_dir(logged_in, conn, dirs_location)
                    break
                elif command == "LSD" and logged_in:
                    list_user_dirs(logged_in, conn, dirs_location)
                    break
                elif command == "LSF" and logged_in:
                    list_files_in_dir(logged_in, conn, dirs_location)
                    break
                elif command == "DEL" and logged_in:
                    delete_dir(logged_in, conn, dirs_location)
                    break
                else:
                    unexpected_command(conn)
            except (BrokenPipeError, ConnectionResetError):
                print("{}: connection closed\n".format(client[1]))
                exit(0)

        conn.close() # end of code


    # Mask CTRL-C, handle SIGTERM (terminate, from father)
    signal(SIGINT, SIG_IGN)
    signal(SIGTERM, signal_handler)
    while True:
        client = tcp_socket.accept()
        p_client = Process(target=deal_with_client, args=(client, valid_users, dirs_location, known_bs), daemon=True)
        p_client.start()



def authenticate_user(valid_users, conn):
    """ Authenticates user, returns (user,pass) (AUT/AUR) """

    username = read_bytes_until(conn, " ")
    password = read_bytes_until(conn, "\n")

    print("-> AUT {} {}".format(username, password))

    res = (False, False)
    status = "NOK"
    if username not in valid_users:
        valid_users[username] = password
        backup_dict_to_file(valid_users, CS_VALID_USERS_SAVEFILE)
        res = (username, password)
        status = "NEW"
        print("New user: {}".format(username))
    elif valid_users[username] != password:
        print("Password received does not match")
    else:
        res = (username, password)
        status = "OK"
        print("User {} logged in sucessfully".format(username))

    response = "AUR {}\n".format(status)
    conn.sendall(response.encode())
    return res



def delete_user(username, conn, dirs_location, valid_users):

    print(">> DLU")
    status = "NOK\n"

    if username in [f[0] for f in dict(dirs_location)]:
        print("There is still information stored for user\n")
    else:
        del valid_users[username]
        backup_dict_to_file(valid_users, CS_VALID_USERS_SAVEFILE)
        status = "OK\n"
        print("User {} deleted sucessfully\n".format(username))

    response = "DLR " + status
    conn.sendall(response.encode())



def backup_dir(username, conn, known_bs, password, dirs_location):

    flag = 0
    folder = read_bytes_until(conn, " ")
    nr_user_files = int(read_bytes_until(conn, " "))
    print(">> BCK {} {}".format(folder, str(nr_user_files)))
    user_dict = {} # {"filename": [date, time, size]}
    bs_dict = {}   # {"filename": [date, time, size]}
    string_of_files = ""
    registered_in_bs = 0

    files_user = read_bytes_until(conn, "\n").split()

    for i in range(nr_user_files):
        filename = files_user[4*i]
        date = files_user[4*i+1]
        time = files_user[4*i+2]
        size = files_user[4*i+3]
        user_dict[filename] = [date, time, size]
        string_of_files += " {} {} {} {}".format(filename, date, time, size)


    if (username, folder) in dirs_location:
        flag = 1
        ip_bs = dirs_location[(username, folder)][0]
        port_bs = dirs_location[(username, folder)][1]

        print("BCK {} {} {} {}".format(username, folder, ip_bs, port_bs))

        bs_socket = udp_client(ip_bs, int(port_bs))
        bs_socket.sendall("LSF {} {}\n".format(username, folder).encode())
        response = bs_socket.recv(2048).decode().split()
        bs_socket.close()
        command = response[0]

        if command != "LFD":
            print("Error in command")
            exit(0)


        nr_bs_files = int(response[1])
        for i in range(nr_bs_files):
            filename = response[2 + 4*i]
            date = response[2 + 4*i + 1]
            time = response[2 + 4*i + 2]
            size = response[2 + 4*i + 3]
            bs_dict[filename] = [date, time, size]


        final_string_of_files = ""
        nr_files_final = 0
        for user_file in user_dict:
            for bs_file in bs_dict:
                if user_file == bs_file and user_dict[user_file] != bs_dict[bs_file]:
                    final_string_of_files += " {} {} {} {}".format(user_file, bs_dict[user_file][0], bs_dict[user_file][1], bs_dict[user_file][2])
                    nr_files_final += 1
        if nr_files_final == 0:
            print("No files to backup\n")
        response = "BKR {} {} {}{}\n".format(ip_bs, port_bs, nr_files_final, final_string_of_files)
        conn.sendall(response.encode())

    if flag == 0:
        ip_bs = ""
        flag_bs = 0
        flag_first_user = 1
        first_user = ()
        if not known_bs:
            print("No BS available to backup [BKR EOF]\n")
            conn.sendall("BKR EOF\n".encode())
            return
        known_bs_temp = dict(known_bs)
        for (ip, port) in known_bs_temp:
            '''verifica se e a primeira chave do dicionario
               Se for, guarda caso os BS ja tenham sido usados para backup
               o mesmo numero de vezes'''
            if flag_first_user:
                ip_bs, port_bs = (ip, port)
                flag_first_user = 0
            elif known_bs_temp[(ip, port)] < known_bs_temp[(ip_bs, port_bs)]:
                ip_bs, port_bs = (ip, port)

        known_bs[(ip_bs, port_bs)] += 1
        print("BS with ip: {} and port: {} was chosen for backup".format(ip_bs, port_bs))

        for (user, directory) in dict(dirs_location):
            if dirs_location[(user, directory)] == (ip_bs, port_bs) and user == username:
                print("User {} is already registered in BS with ip: {} and port: {}\n".format(username, ip_bs, port_bs))
                registered_in_bs = 1
                break

        dirs_location[(username, folder)] = (ip_bs, port_bs)
        backup_dict_to_file(dirs_location, CS_DIRS_LOCATION_SAVEFILE)

        if not registered_in_bs:
            bs_socket = udp_client(ip_bs, int(port_bs))
            response = "LSU {} {}\n".format(username, password)
            bs_socket.sendall(response.encode())
            command, status = bs_socket.recv(32).decode()[:-1].split()
            bs_socket.close()

            if command != "LUR":
                print("Error in command\n")
                exit(0)
            elif status == "NOK\n":
                print("Already knew user\n")
                exit(0)
            elif status == "ERR\n":
                print("Error in arguments sent from CS to BS\n")
                exit(0)
            else:
                print("User {} was added to BS with ip: {} and port: {} sucessfully\n".format(username, ip_bs, port_bs))
        
        response = "BKR {} {} {}{}\n".format(ip_bs, port_bs, nr_user_files, string_of_files)
        conn.sendall(response.encode())



#check conditions of error
def restore_dir(username, conn, dirs_location):

    flag = 0
    folder = read_bytes_until(conn, "\n")

    print("Restore {}".format(folder))

    if (username, folder) in dirs_location:
        print("Entered")
        flag = 1
        ip_bs = dirs_location[(username, folder)][0]
        port_bs = dirs_location[(username, folder)][1]
        response = "RSR {} {}\n".format(ip_bs, port_bs)
        print(response)
        conn.sendall(response.encode())

    if flag == 0:
        print("RSR EOF")
        response = "RSR EOF\n"
        conn.sendall(response.encode())


def list_user_dirs(username, conn, dirs_location):

    print(">> LSD")
    nr_files = 0
    dirs_str = ""

    if dirs_location:
        for (user, folder) in dict(dirs_location):
            if user == username:
                nr_files += 1
                dirs_str += folder + " "
                print(folder)

    response = "LDR {} {}\n".format(str(nr_files), dirs_str)
    print(response)
    conn.sendall(response.encode())



def list_files_in_dir(username, conn, dirs_location):

    flag = 0
    folder = read_bytes_until(conn, " \n")
    print(">> LSF {}".format(folder))

    if (username, folder) in dirs_location:
        flag = 1
        ip_bs = dirs_location[(username, folder)][0]
        port_bs = dirs_location[(username, folder)][1]

        bs_socket = udp_client(ip_bs, int(port_bs))
        bs_socket.sendall("LSF {} {}\n".format(username, folder).encode())
        response = bs_socket.recv(2048).decode().split()
        bs_socket.close()


        if response[0] != "LFD":
            print("Error in command\n")
            exit(0)


        nr_bs_files = int(response[1])
        conn.sendall("LFD {} {} {}".format(ip_bs, port_bs, nr_bs_files).encode())

        for i in range(nr_bs_files):
            filename = response[2 + 4*i]
            date = response[2 + 4*i + 1]
            time = response[2 + 4*i + 2]
            size = response[2 + 4*i + 3]
            conn.sendall(" {} {} {} {}".format(filename, date, time, size).encode())

        conn.sendall("\n".encode())

    if flag == 0:
        response = "LFD NOK\n"
        conn.sendall(response.encode())



def delete_dir(username, conn, dirs_location):

    print(">> DEL")

    status_del = "NOK"
    flag = 0
    folder = read_bytes_until(conn, " \n")

    if (username, folder) in dirs_location:
        flag = 1
        ip_bs = dirs_location[(username, folder)][0]
        port_bs = dirs_location[(username, folder)][1]

        bs_socket = udp_client(ip_bs, int(port_bs))
        bs_socket.sendall("DLB {} {}\n".format(username, folder).encode())
        command, status = bs_socket.recv(8).decode().split(" ")
        bs_socket.close()

        if command != "DBR":
            print("Error in protocol\n")
            conn.sendall("ERR\n".encode())
        else:
            if status == "NOK":
                print("No such folder exists in the chosen BS\n")
            else:
                status_del = "OK"
                del dirs_location[(username, folder)]
                backup_dict_to_file(dirs_location, CS_DIRS_LOCATION_SAVEFILE)
                print("Directory {} was sucessfully deleted\n".format(folder))
            response = "DDR {}\n".format(status_del)
            conn.sendall(response.encode())

    if flag == 0:
        print("No such folder for the user {}\n".format(username))
        response = "DDR {}\n".format(status_del)
        conn.sendall(response.encode())





def main():

    manager = SyncManager()
    manager.start(ignore_sigint)
    known_bs = manager.dict()        # {("ip_BS", "port_BS"): counter}
    valid_users = manager.dict()     # {"user": password}
    dirs_location = manager.dict()   # {(username, "folder"): (ipBS, portBS)}

    my_address = get_best_ip()
    my_port = DEFAULT_CS_PORT


    try:
        a = getopt.getopt(sys.argv[1:], "p:")[0]
    except getopt.GetoptError as error:
        print(error)
        exit(2)

    for opt, arg in a:
        if opt == '-p':
            my_port = int(arg)



    print("My address is {}\n".format(my_address))

    udp_receiver = udp_server(my_address, my_port)
    tcp_receiver = tcp_server(my_address, my_port)


    if os.path.isfile(CS_KNOWN_BS_SAVEFILE):
        known_bs.update(restore_dict_from_file(CS_KNOWN_BS_SAVEFILE))

    if os.path.isfile(CS_VALID_USERS_SAVEFILE):
        valid_users.update(restore_dict_from_file(CS_VALID_USERS_SAVEFILE))

    if os.path.isfile(CS_DIRS_LOCATION_SAVEFILE):
        dirs_location.update(restore_dict_from_file(CS_DIRS_LOCATION_SAVEFILE))


    try:
        # "Forking"
        p_udp = Process(target=deal_with_udp, args=(udp_receiver, known_bs))
        p_tcp = Process(target=deal_with_tcp, args=(tcp_receiver, valid_users, dirs_location, known_bs))
        p_udp.start()
        p_tcp.start()

        pause()
    except KeyboardInterrupt:
        pass
    finally:
        tcp_receiver.close()
        udp_receiver.close()
        p_tcp.terminate()
        p_udp.terminate()
        p_tcp.join()
        p_udp.join()

        backup_dict_to_file(known_bs, CS_KNOWN_BS_SAVEFILE)
        backup_dict_to_file(valid_users, CS_VALID_USERS_SAVEFILE)
        backup_dict_to_file(dirs_location, CS_DIRS_LOCATION_SAVEFILE)

        print()


if __name__ == '__main__':
    main()
