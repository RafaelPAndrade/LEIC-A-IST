#!/usr/bin/env python3

import sys, os
import re #Regex module


save_folder = "src_readable/"
'''
Usage: rem_error_checking.py src/*


This program assumes the following style for error checking:

    retVal = some_that_returns_errors(arg1,arg2,...);
    if (retVal) {
        // some code in the block
    }

'''

test = re.compile(r"exit")
error_capturing = re.compile(r"retVal\s*=\s*(errno;)?")
if_error_print = re.compile(r"if.*\n\t*err.*\n(\t*exit.*;.*\n)?\t*\}", re.MULTILINE)

def main():
    if not os.path.exists(save_folder): os.makedirs(save_folder)
    for c_file_path in sys.argv[1:]:
        print("Removing error checking for file "+c_file_path)
        rem_error_checking(c_file_path)

# takes a path and returns the filename
def getFileName(filepath):
    return filepath[filepath.rfind("/")+1:]

# removes error checking in a file
# and produces a copy of the fule
def rem_error_checking(c_file_path):
    c_file = getFileName(c_file_path)
    f = open(c_file_path, 'r')
    all_text = f.read()
    f.close()


    print(len(all_text))

    all_text = if_error_print.sub("", all_text)
    all_text = error_capturing.sub("", all_text)


    print(len(all_text))

    # writing the error checking part
    f = open(save_folder+c_file,'w')
    f.write(all_text)
    f.close()

main()
