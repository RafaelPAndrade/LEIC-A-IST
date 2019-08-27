#!/usr/bin/env python3
""" This file/module implements the Backup Server.

    The BS listens for requests of the Central Server to add users,
    so that those users may upload directories with files, and after that
    restore them. The communication with the CS is via UDP; with clients
    is via TCP
"""


import os
from socket import timeout
from sys import argv
from getopt import getopt, GetoptError
from signal import signal, pause, SIGINT, SIGTERM, SIG_IGN
from multiprocessing import Process
from multiprocessing.managers import SyncManager
from time import strptime, strftime, gmtime
from calendar import timegm
from lib.server import udp_client, udp_server, tcp_server
from lib.utils import (read_bytes_until, chunked_read_socket, chunked_read_fd,
                       DEFAULT_CS_PORT, DEFAULT_BS_PORT, BS_USER_SAVEFILE,
                       backup_dict_to_file, restore_dict_from_file,
                       ignore_sigint, print_connection_event,
                       get_best_ip)

# Functions to register/deregister from CS (UDP client)

def register_in_cs(cs_host, cs_port, my_address, my_port):
    """ Contact the CS via UDP to register itself """

    try:
        cs_socket = udp_client(cs_host, cs_port)

        message = "REG {} {}\n".format(my_address, my_port)
        print_connection_event((cs_host, cs_port), "Registering in CS Server", message[:-1], "<-")
        cs_socket.sendall(message.encode())

        response = cs_socket.recv(16)
        response = response.decode()
        cs_socket.close()

        res = (response == "RGR OK\n")
        if res:
            message = "Registered in CS Server"
        else:
            message = "Unable to register in CS Server"

        print_connection_event((cs_host, cs_port), message, response[:-1])
        return res

    except timeout:
        print("Error: CS server took too long to respond.")
        exit(1)
    except (ConnectionError, ConnectionRefusedError):
        print("Error: CS server does not seem active. Shutting down.\n")
        exit(1)


def unregister_from_cs(cs_host, cs_port, my_address, my_port):
    """ Contact the CS via UDP to unregister itself """

    try:
        cs_socket = udp_client(cs_host, cs_port)
        print()
        print_connection_event((cs_host, cs_port), "Unregistering from CS", "", "<-")

        cs_socket.sendall("UNR {} {}\n".format(my_address, my_port).encode())
        response = cs_socket.recv(16).decode()
        cs_socket.close()
        return response == "UAR OK\n"

    except timeout:
        print("Error: CS server took too long to respond.")
        print("Shutting down uncleanly.\n")
        exit(1)
    except (ConnectionError, ConnectionRefusedError):
        print("Error: CS server does not seem active.")
        print("Shutting down uncleanly.\n")
        exit(1)


def unexpected_command(my_socket, address=None):
    """ Informs that there was a error. TCP and UDP compatible. """
    if not address:
        my_socket.sendall("ERR\n".encode())
    else:
        my_socket.sendto("ERR\n".encode(), address)


def deal_with_udp(udp_socket, known_users):
    """ UDP server process function / program

    Used for dealing with UDP queries from the CS. Because, by design, there
    is only 1 CS, no fork-on-receive is necessary (also, because UDP has
    datagrams and no concept of connection).
    """

    def signal_handler(_signum, _frame):
        udp_socket.close()
        exit(0)


    # ignore CTRL-C; handle .terminate() from parent
    signal(SIGINT, SIG_IGN)
    signal(SIGTERM, signal_handler)

    while True:
        # Not checking address, assuming only CS will contact UDP server
        response, address = udp_socket.recvfrom(128)

        if response.decode()[-1] != "\n":
            print("Error: Malformed UDP message")
            unexpected_command(udp_socket, address)

        response = response.decode()[:-1]
        command, *args = response.split(" ")

        print_connection_event(address, "Got new UDP message", response, "->")

        if command == "LSU":
            add_user(known_users, args, udp_socket, address)
        elif command == "DLB":
            remove_dir(known_users, args, udp_socket, address)
        elif command == "LSF":
            list_user_files(known_users, args, udp_socket, address)
        else:
            unexpected_command(udp_socket, address)



# Specific protocol functions

def add_user(known_users, args, udp_socket, address):
    """ Register user in this BS (LSU/LUR)

    The registration process entails 2 things:
    1. The creation of a directory with the user's name
    2. The insertion in the "global" dictionary known_users of user:password
    """

    status = "ERR\n"
    if len(args) != 2 or len(args[1]) > 8 or not args[1].isalnum():
        print("Error in arguments received from CS server: {}".format(args[0]))
    elif args[0] in known_users and args[1] != known_users[args[0]]:
        print("Error: Already knew user {}".format(args[0]))
        status = "NOK\n"
    else:
        try:
            os.mkdir(args[0])
        except FileExistsError:
            pass
        known_users[args[0]] = args[1]
        backup_dict_to_file(known_users, BS_USER_SAVEFILE)
        status = "OK\n"

    response = "LUR " + status
    print_connection_event(address, "Responding to add user message", response[:-1], "<-")
    udp_socket.sendto(response.encode(), address)



def remove_dir(known_users, args, udp_socket, address):
    """ Remove directory of user (DLB/DBR)

    Returns ERR if user not found, NOK if user exists but folder was not found
    """

    status = "ERR\n"
    if not args[0] in known_users or not os.path.isdir(args[0]):
        print("Error: no files from user exist in this server")
    elif not os.path.isdir(os.path.join(args[0], args[1])):
        print("Error: no such folder exists: {}".format(args[1]))
        status = "NOK\n"
    else:
        base_dir = os.path.join(args[0], args[1])
        for userfile in os.listdir(base_dir):
            os.remove(os.path.join(base_dir, userfile))
        os.rmdir(base_dir)

        # No more files from user, remove from known_users
        if not os.listdir(args[0]):
            known_users.pop(args[0], 0)
            os.rmdir(args[0])

        status = "OK\n"


    response = "DBR " + status
    print_connection_event(address, "Responding to remove dir request", response[:-1], "<-")
    udp_socket.sendto(response.encode(), address)


def list_user_files(known_users, args, udp_socket, address):
    """ List files of user present in this BS server

    Returns ERR if user not found, NOK if user exists but folder was not found
    (like remove_dir).
    """

    status = "0\n"
    n_files = 0
    if not args[0] in known_users or not os.path.isdir(args[0]):
        print("Error: no files from user exist in this server")
    elif not os.path.isdir(os.path.join(args[0], args[1])):
        print("Error: no such folder exists: {}".format(args[1]))
    else:
        listing = ""
        for user_file in os.scandir(os.path.join(args[0], args[1])):
            n_files += 1
            f_stat = user_file.stat()
            f_time = strftime("%d.%m.%Y %H:%M:%S", gmtime(f_stat.st_mtime))
            listing += " {} {} {}".format(user_file.name, f_time, f_stat.st_size)

        status = "{} {}\n".format(n_files, listing)

    response = "LFD " + status
    print_connection_event(address, "Responding to list files request", "LFD " + str(n_files), "<-")
    udp_socket.sendto(response.encode(), address)




# Code to deal with client queries (TCP server)

def deal_with_tcp(tcp_socket, known_users):
    """ TCP server process function / program

    Used for dealing with TCP queries from clients. Because we may have
    concurrent connections from various clients, we use a policy of
    fork-on-connection. We assume that 2 distinct clients will not make
    destructive changes in the same user account.
    """
    def signal_handler(_signum, _frame):
        tcp_socket.close()
        exit(0)


    def deal_with_client(client, known_users):
        """ Code / function for forked worker """

        conn = client[0]
        logged_in = False       # this var is False or contains the user id
        while True:
            try:
                command = read_bytes_until(conn, " \n")
                print_connection_event(client[1], "TCP request type: ", command, "  ")
                if command == "AUT":
                    logged_in = authenticate_user(known_users, client)
                elif command == "UPL" and logged_in:
                    backup_user_files(logged_in, client)
                    break
                elif command == "RSB" and logged_in:
                    restore_user_files(logged_in, client)
                    break
                else:
                    unexpected_command(conn)
            except (BrokenPipeError, ConnectionResetError):
                print("{}: connection closed".format(client[1]))
                exit(0)

        conn.close() # EOC (end of code)


    # Mask CTRL-C, handle SIGTERM (terminate, from father)
    signal(SIGINT, SIG_IGN)
    signal(SIGTERM, signal_handler)
    while True:
        client = tcp_socket.accept()
        print_connection_event(client[1], "Got new TCP connection", "", "->")
        p_client = Process(target=deal_with_client,
                           args=(client, known_users),
                           daemon=True)
        p_client.start()


def authenticate_user(known_users, client):
    """ Authenticates user, returns user id (AUT/AUR) """
    username = read_bytes_until(client[0], " ")
    password = read_bytes_until(client[0], "\n")

    print_connection_event(client[1], "AUT args: ", [username, password], "  ")

    users = dict(known_users)

    res = False
    status = "NOK\n"
    if username not in users:
        print("User not known to this BS")
    elif users[username] != password:
        print("Password received does not match")
    else:
        status = "OK\n"


    response = "AUR " + status
    print_connection_event(client[1], "Response to auth_request", response[:-1])
    client[0].sendall(response.encode())
    return username



def backup_user_files(logged_in, client):
    """ Receives files from user. (UPL/UPR) """

    folder = read_bytes_until(client[0], " ")
    number_of_files = int(read_bytes_until(client[0], " "))

    print_connection_event(client[1], "Backup args: ", [folder, number_of_files], "  ")

    try:
        os.makedirs(os.path.join(logged_in, folder))
    except FileExistsError:
        pass

    status = "OK\n"
    for _i in range(0, number_of_files):
        filename = read_bytes_until(client[0], " ")
        date = read_bytes_until(client[0], " ")
        date = date + " " + read_bytes_until(client[0], " ") # do not forget hour
        size = int(read_bytes_until(client[0], " "))
        print_connection_event(client[1], "    Receiving {}".format(filename), "", "  ")


        # Opening file now
        filepath = os.path.join(logged_in, folder, filename)
        filefd = os.open(filepath, os.O_WRONLY | os.O_CREAT, mode=0o660)


        for data in chunked_read_socket(client[0], size):
            os.write(filefd, data)

        if os.stat(filefd).st_size != size:
            print("ERROR: Unable to fully write {}".format(filename))
            status = "NOK\n"
            break
        print_connection_event(client[1], "     Received {}".format(filename), "", "  ")
        os.close(filefd)

        # Set mtime to the sent one (and atime to now)
        file_mtime = timegm(strptime(date, "%d.%m.%Y %H:%M:%S"))
        os.utime(filepath, times=(timegm(gmtime()), file_mtime))


        last = client[0].recv(1)
        if __debug__:
            assert last.decode() in (' ', '\n')

    response = "UPR " + status
    print_connection_event(client[1], "Response to backup request", response[:-1], "<-")
    client[0].sendall(response.encode())


def restore_user_files(logged_in, client):
    """ Sends back files to user. (RSB/RSR) """

    try:
        folder = read_bytes_until(client[0], "\n")
        print_connection_event(client[1], "Upload args: ", folder, "  ")
    except:
        print_connection_event(client[1], "Error in request for restoration", "RBR ERR", "<-")
        client[0].sendall("RBR ERR\n".encode())
        exit(2)

    dirpath = os.path.join(logged_in, folder)
    if not os.path.isdir(dirpath):
        print_connection_event(client[1], "Directory not found", "RBR EOF", "<-")
        client[0].sendall("RBR EOF\n".encode())
        exit(1)

    file_list = [f for f in os.scandir(dirpath) if f.is_file()]
    message = "RBR {}".format(len(file_list))

    print_connection_event(client[1], "Start sending back files", message, "<-")
    client[0].sendall(message.encode())

    for user_file in file_list:

        f_stat = user_file.stat()
        f_time = strftime("%d.%m.%Y %H:%M:%S", gmtime(f_stat.st_mtime))
        mess_part = " {} {} {} ".format(user_file.name, f_time, f_stat.st_size)
        print_connection_event(client[1], "    Sending {}".format(user_file.name), "", "  ")
        client[0].sendall(mess_part.encode())

        filefd = os.open(user_file.path, os.O_RDONLY)
        for data in chunked_read_fd(filefd, f_stat.st_size, 4096):
            client[0].sendall(data)
        print_connection_event(client[1], "       Sent {}".format(user_file.name), "", "  ")

    client[0].sendall("\n".encode())
    print_connection_event(client[1], "Finished sending back files", message, "<-")



def main():
    """ BS main process """

    manager = SyncManager()
    manager.start(ignore_sigint)
    known_users = manager.dict() # Shared dict across processes
    my_ip = get_best_ip()
    my_port = DEFAULT_BS_PORT
    cs_host = my_ip
    cs_port = DEFAULT_CS_PORT


    try:
        options = getopt(argv[1:], "b:n:p:")[0]
    except GetoptError as error:
        print(error)
        exit(2)

    for opt, arg in options:
        if opt == '-b':
            my_port = int(arg)
        elif opt == '-n':
            cs_host = arg
        elif opt == '-p':
            cs_port = int(arg)




    # Getting sockets for the servers ready
    udp_receiver = udp_server(my_ip, my_port)
    tcp_receiver = tcp_server(my_ip, my_port)


    # Retrieving previously known users
    if os.path.isfile(BS_USER_SAVEFILE):
        known_users.update(restore_dict_from_file(BS_USER_SAVEFILE))

    try:
        # "Forking"
        p_udp = Process(target=deal_with_udp, args=(udp_receiver, known_users),
                        name="UDP dealer")
        p_tcp = Process(target=deal_with_tcp, args=(tcp_receiver, known_users),
                        name="TCP dealer")
        p_udp.start()
        p_tcp.start()

        register_in_cs(cs_host, cs_port, my_ip, my_port)
        pause()
    except KeyboardInterrupt:
        unregister_from_cs(cs_host, cs_port, my_ip, my_port)
    finally:
        udp_receiver.close()
        tcp_receiver.close()
        p_tcp.terminate()
        p_udp.terminate()
        p_tcp.join()
        p_udp.join()
        backup_dict_to_file(known_users, BS_USER_SAVEFILE)



if __name__ == "__main__":
    main()
