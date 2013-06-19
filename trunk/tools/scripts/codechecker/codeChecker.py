#!/usr/bin/env/python

import argparse #processing of arguments
import sys	#unused til now
import os	#get path

parser = argparse.ArgumentParser(description='process and help') 
parser.add_argument('-d', default=os.getcwd(), metavar='DIR', help="Destination to be checked")
parser.add_argument('-c', nargs='*', metavar='FILE', help="Rulefiles to be used")
parser.add_argument('-f', nargs='*', metavar='EXT', help="filetypes to be checkes")
parser.add_argument('-b', nargs='*', metavar='EXT', help = "filetypes to be ignored")
parser.add_argument('-a', action='store_true', help= "check for all errors")
parser.add_argument('-t', nargs='*', metavar='NUM', help="check errors with given error typenumbers")
parser.add_argument('-e', nargs='*', metavar='ERR', help="check errors with given error codes")
parser.add_argument('-i', nargs='*', metavar='ERR', help="show information about given error code")
parser.add_argument('-r', action='store_true', help="FILENAME is to be interpreted as regular expression")
print("\nEingabe OK! Argumente:\n")
print(vars(parser.parse_args()))

