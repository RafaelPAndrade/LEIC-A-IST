#!/usr/bin/env python3

import sys, getopt, os
from socket import gethostname, gethostbyname, timeout
from time import strptime, strftime, gmtime
from calendar import timegm
from lib.server import tcp_client
from lib.utils import (read_bytes_until, chunked_read_socket, chunked_read_fd,
                       get_best_ip)


def authenticate(cs_socket, user, password):

    if(user=="" and password==""):
        print("You have to be logged in to use this command\n")
        return False

    cs_socket.sendall("AUT {} {}\n".format(user, password).encode())

    response = read_bytes_until(cs_socket, "\n")

    if response != "AUR OK":
        print("Authentication failed\n")
        cs_socket.close()
        return False

    return True

def login_user(args, host, port):
    cs_socket = tcp_client(host, port)

    if (len(args) != 2 or len(args[0]) != 5 or len(args[1]) != 8 or not args[0].isdigit()
            or not args[1].isalnum()):

        print("Invalid user/password pair\n")
        return "", ""

    user = args[0]
    password = args[1]

    cs_socket.sendall("AUT {} {}\n".format(user, password).encode())

    response = read_bytes_until(cs_socket, "\n")

    if response == "AUR OK":
        print("Logged in successfully\n")
    elif response == "AUR NOK":
        print("Incorrect password\n")
        user, password = "", ""
    elif response == "AUR NEW":
        print("Logged in with a new user\n")

    return user, password



def delete_user(host, port, user, password):
    cs_socket = tcp_client(host, port)

    if not authenticate(cs_socket, user, password):
        return user, password

    cs_socket.sendall("DLU\n".encode())

    response = read_bytes_until(cs_socket, "\n")

    if response == "DLR OK":
        print("User was deleted\n")
        user, password = "", ""

    elif response == "DLR NOK":
        print("User couldn't be deleted\n")

    cs_socket.close()

    return user, password


def backup_dir(args, host, port, user, password):
    cs_socket = tcp_client(host, port)

    if not authenticate(cs_socket, user, password):
        return

    # Validates the arguments for the function

    if len(args) != 1:
        print("Invalid arguments\n")
        cs_socket.close()
        return

    directory = args[0]

    if not os.path.isdir(directory):
        print("The directory does not exist\n")
        cs_socket.close()
        return

    file_list = [f for f in os.scandir(directory) if f.is_file()]

    if len(file_list) > 20:
        print("The directory is too big to be backed up\n")
        cs_socket.close()
        return

    # Send the files in the directory to the Central Server
    # to check which ones should be backed up

    cs_socket.sendall("BCK {} {}".format(directory, len(file_list)).encode())

    for f in file_list:

        f_stat = f.stat()
        f_time = strftime("%d.%m.%Y %H:%M:%S", gmtime(f_stat.st_mtime))
        cs_socket.sendall(" {} {} {}".format(f.name, f_time, f_stat.st_size).encode())

    cs_socket.sendall("\n".encode())

    response = read_bytes_until(cs_socket, " \n")
    bs_ip = read_bytes_until(cs_socket, " \n")

    if response != "BKR":
        print("Protocol was not followed\n")
        cs_socket.close()
        return

    elif bs_ip == "ERR":
        print("An error ocurred sending the backup request\n")
        cs_socket.close()
        return

    elif bs_ip == "EOF":
        print("The backup request cannot be answered\n")
        cs_socket.close()
        return

    # Check which files are already backed up

    bs_port = int(read_bytes_until(cs_socket, " "))
    n_files = int(read_bytes_until(cs_socket, " \n"))

    if n_files == 0:
        print("All files are backed up already\n")
        cs_socket.close()
        return

    files_to_backup = []

    for _i in range(n_files):
        filename = read_bytes_until(cs_socket, " ")
        date = read_bytes_until(cs_socket, " ")
        date = date + " " + read_bytes_until(cs_socket, " ")  # do not forget hour
        size = int(read_bytes_until(cs_socket, " \n"))
        print(filename, date, size)

        for f in file_list:
            if f.name == filename:
                files_to_backup.append(f)

    cs_socket.close()

    # create a connection with the Backup Server and send the files

    bs_socket = tcp_client(bs_ip, bs_port)

    if not authenticate(bs_socket, user, password):
        return

    bs_socket.sendall("UPL {} {}".format(directory,len(files_to_backup)).encode())

    for f in files_to_backup:
        f_stat = f.stat()
        f_time = strftime("%d.%m.%Y %H:%M:%S", gmtime(f_stat.st_mtime))
        bs_socket.sendall(" {} {} {} ".format(f.name, f_time, f_stat.st_size).encode())

        filefd = os.open(f.path, os.O_RDONLY)
        for chunk in chunked_read_fd(filefd, f_stat.st_size):
            bs_socket.sendall(chunk)

    bs_socket.sendall("\n".encode())

    response = read_bytes_until(bs_socket, " ")
    status = read_bytes_until(bs_socket, " \n")

    if response == "UPR" and status == "OK":
        print("File transfer successful\n")
    elif status == "NOK":
        print("File transfer unsuccessful\n")
    else:
        print("A protocol error ocurred\n")

    bs_socket.close()



def restore_dir(args, host, port, user, password):
    cs_socket = tcp_client(host, port)

    if not authenticate(cs_socket, user, password):
        return

    if len(args) != 1:
        print("Invalid arguments\n")
        cs_socket.close()
        return

    directory = args[0]

    cs_socket.sendall("RST {}\n".format(directory).encode())

    response = read_bytes_until(cs_socket, " \n")
    bs_ip = read_bytes_until(cs_socket, " \n")

    if response != "RSR":
        print("Protocol was not followed\n")
        cs_socket.close()
        return

    elif bs_ip == "ERR":
        print("An error ocurred sending the backup request\n")
        cs_socket.close()
        return

    elif bs_ip == "EOF":
        print("The backup request cannot be answered\n")
        cs_socket.close()
        return

    bs_port = int(read_bytes_until(cs_socket, "\n"))

    cs_socket.close()

    # create a connection with the Backup Server and receive the files

    bs_socket = tcp_client(bs_ip, bs_port)

    if not authenticate(bs_socket, user, password):
        return

    bs_socket.sendall("RSB {}\n".format(directory).encode())

    response = read_bytes_until(bs_socket, " \n")
    n_files = read_bytes_until(bs_socket, " \n")

    if response != "RBR":
        print("Protocol was not followed\n")
        bs_socket.close()
        return

    elif n_files == "ERR":
        print("An error ocurred sending the backup request\n")
        bs_socket.close()
        return

    elif n_files == "EOF":
        print("The backup request cannot be answered\n")
        bs_socket.close()
        return

    n_files = int(n_files)

    if n_files == 0:
        print("All files are already up to date\n")
        bs_socket.close()
        return

    # create directory
    try:
        os.mkdir(directory)
    except FileExistsError:
        pass

    print("Restoring the following directory: {}\n".format(directory))


    for _i in range(n_files):
        filename = read_bytes_until(bs_socket, " ")
        date = read_bytes_until(bs_socket, " ")
        date = date + " " + read_bytes_until(bs_socket, " ") # do not forget hour
        size = int(read_bytes_until(bs_socket, " "))


        #Opening file now
        filepath = os.path.join(directory, filename)
        filefd = os.open(filepath, os.O_WRONLY | os.O_CREAT, mode=0o660)

        written = 0
        for d in chunked_read_socket(bs_socket, size):
            written += len(d)
            os.write(filefd, d)
        if written != size:
            print("ERROR: Unable to fully write {}".format(filename))
            break

        print("Restored following file: {}\n".format(filename))
        os.close(filefd)

        # Set mtime to the sent one (and atime to now)
        file_mtime = timegm(strptime(date, "%d.%m.%Y %H:%M:%S"))
        os.utime(filepath, times=(timegm(gmtime()), file_mtime))

        bs_socket.recv(1)


    bs_socket.close()



def list_dir(host, port, user, password):
    cs_socket = tcp_client(host, port)

    if not authenticate(cs_socket, user, password):
        return

    cs_socket.sendall("LSD\n".encode())

    response = read_bytes_until(cs_socket, " \n")
    n_files = int(read_bytes_until(cs_socket, " \n"))

    if response != 'LDR':
        print("The request was unsuccessful\n")
    elif n_files == 0:
        print("No directories are backed up yet\n")
    else:
        print("The following directories are backed up:")
        directories = read_bytes_until(cs_socket, "\n").split()
        for d in directories:
            print(d)

    cs_socket.close()


def filelist_dir(args, host, port, user, password):
    cs_socket = tcp_client(host, port)

    if not authenticate(cs_socket, user, password):
        return

    if len(args) != 1:
        print("Invalid arguments\n")
        cs_socket.close()
        return

    directory = args[0]

    cs_socket.sendall("LSF {}\n".format(directory).encode())

    response = read_bytes_until(cs_socket, " \n")
    bs_ip = read_bytes_until(cs_socket, " \n")


    if response != "LFD":
        print("Protocol was not followed\n")
        cs_socket.close()
        return

    elif bs_ip == "NOK":
        print("The request cannot be answered\n")
        cs_socket.close()
        return

    bs_port = read_bytes_until(cs_socket, " ")
    n_files = int(read_bytes_until(cs_socket, " \n"))

    print("At the BS in ip {} in port {} there are {} files backed up\n".format(bs_ip, bs_port, n_files))

    print("The files are:")

    for i in range(n_files):
        filename = read_bytes_until(cs_socket, " ")
        date = read_bytes_until(cs_socket, " ")
        date = date + " " + read_bytes_until(cs_socket, " ") # do not forget hour
        size = int(read_bytes_until(cs_socket, " \n"))

        print(" - {} {} {}".format(filename, date, size))

    print()
    cs_socket.close()



def delete_dir(args, host, port, user, password):
    cs_socket = tcp_client(host, port)

    if not authenticate(cs_socket, user, password):
        return

    if len(args) != 1:
        print("Invalid arguments\n")
        cs_socket.close()
        return

    cs_socket.sendall("DEL {}\n".format(args[0]).encode())

    response = read_bytes_until(cs_socket, "\n")

    if response == "DDR OK":
        print("The request was successful\n")

    elif response == "DDR NOK":
        print("The request was unsuccessful\n")

    cs_socket.close()

def logout(user, password):
    if(user=="" and password==""):
        print("You have to be logged in to logout\n")

    else:
        print("Logout successful\n")

    return "",""

def exit_user():
    print("Adios!")
    sys.exit(0)




def main():
    cs_host = get_best_ip()
    cs_port = 58028

    try:
        opts = getopt.getopt(sys.argv[1:], "n:p:")[0]
    except getopt.GetoptError as error:
        print(error)
        sys.exit(2)


    for opt, arg in opts:
        if opt == '-n':
            cs_host = arg
        elif opt == '-p':
            cs_port = int(arg)

    current_user = ''
    current_password = ''

    while True:
        try:
            inp = input("> ")

            args = inp.split(" ")

            command = args[0]
            args = args[1:]

            if command == 'login':
                current_user, current_password = login_user(args, cs_host, cs_port)

            elif command == 'deluser':
                current_user, current_password = delete_user(cs_host, cs_port, current_user, current_password)

            elif command == 'backup':
                backup_dir(args, cs_host, cs_port, current_user, current_password)

            elif command == 'restore':
                restore_dir(args, cs_host, cs_port, current_user, current_password)

            elif command == 'dirlist':
                list_dir(cs_host, cs_port, current_user, current_password)

            elif command == 'filelist':
                filelist_dir(args, cs_host, cs_port, current_user, current_password)

            elif command == 'delete':
                delete_dir(args, cs_host, cs_port, current_user, current_password)

            elif command == 'logout':
                current_user, current_password = logout(current_user, current_password)

            elif command == 'exit':
                exit_user()

            else:
                print("No such command!\n")
        except (ConnectionError, ConnectionRefusedError, timeout) as error:
            print("Could not complete {} ({})".format(command, error))
        except EOFError:
            exit_user()


if __name__ == "__main__":
    main()
