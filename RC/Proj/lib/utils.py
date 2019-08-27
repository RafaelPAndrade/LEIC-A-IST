#!/usr/bin/env python3
# RC 2018/19 IST
# Grupo 28

from os import read
from socket import timeout, gethostname, gethostbyname_ex
from ipaddress import IPv4Address
from signal import signal, SIGINT, SIG_IGN
from pickle import load, dump

DEFAULT_CS_PORT = 58028
DEFAULT_BS_PORT = 59000

BS_USER_SAVEFILE = "./BS_users.pickle"
CS_KNOWN_BS_SAVEFILE = "./CS_known_bs.pickle"
CS_VALID_USERS_SAVEFILE = "./CS_valid_users.pickle"
CS_DIRS_LOCATION_SAVEFILE = "./CS_dirs_location.pickle"


def read_bytes_until(conn, separators=" "):
    """ Returns str retrieved from socket conn, until any separator is found

    Note that separators is a string, and each character in that string is
    an alternative (field) separator. When a separator is found, it is
    removed from the connection. TCP and UDP compatible.
    """

    try:
        res = ""
        new = conn.recv(1).decode()
        while new not in separators:
            res += new
            new = conn.recv(1).decode()
        return res
    except timeout:
        print("read_bytes_until: Already had \"{}\"".format(res))
        raise

def chunked_read_fd(filefd, size_to_read, chunk_size=1024):
    """ Iterates over file, returns chunks

    This function is a generator, that at each successive invocation reads at
    most "chunk_size" bytes, and returns the contents in bytestring form
    """

    while size_to_read > 0:
        this_chunk = min(chunk_size, size_to_read)
        data = read(filefd, this_chunk)
        size_to_read -= len(data)
        yield data


def chunked_read_socket(my_socket, size_to_read, chunk_size=1024):
    """ Read socket in chunks

    This function is a generator, that at each successive invocation reads at
    most "chunk_size" bytes, and returns the contents in bytestring form
    """


    while size_to_read > 0:
        this_chunk = min(chunk_size, size_to_read)
        data = my_socket.recv(this_chunk)
        size_to_read -= len(data)
        yield data


def ignore_sigint():
    """ Small function used in SyncManager to ignore CTRL-C """
    signal(SIGINT, SIG_IGN)


def backup_dict_to_file(my_dict, pickle_file):
    """ Turns any type of dict into a basic dict and serializes it to file """
    with open(pickle_file, "wb") as savefile:
        dump(dict(my_dict), savefile)



def restore_dict_from_file(pickle_file):
    """ Deserializes dict from file """
    with open(pickle_file, "rb") as savefile:
        return load(savefile)


def print_connection_event(address, message, other, direction="->"):
    print("{} {}: {} {}".format(direction, address, message.ljust(34), "[{}]".format(other)))


def get_best_ip():
    """ Best IP: Public if possible """

    candidate_IPs = gethostbyname_ex(gethostname())[2]

    if not candidate_IPs:
        raise ValueError("No IP addresses available to use")

    public_ips = [ip for ip in candidate_IPs if IPv4Address(ip).is_global]

    if public_ips:
        return public_ips[0]
    else:
        return candidate_IPs[0]
