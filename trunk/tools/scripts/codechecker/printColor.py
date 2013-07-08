#!/usr/bin/env python3
'''printColor.py
' 
' printColor - miniature library that provides a Python print wrapper that
' makes colored output easier to use and keeps the code clean.
' (eg. without having to mess around with NASI escape sequences)
'
' Copyright (C) 2013 Fabian Neuschmitd. All Rights Reserved.
' Written by Fabian Neuschmidt (fabian.neuschmidt@googlemail.com)
'
' This program is free software: you can redistribute it and/or modify it under
' the terms of the GNU General Public License as published by the Free Software
' Foundation, either version 3 of the License, or (at your option) any later
' version.
'''

import inspect #get name of calling function
import re

colorCodes = {
	'black':    '0;30',     'bright gray':  '0;37',
	'blue':     '0;34',     'white':        '1;37',
	'green':    '0;32',     'bright blue':  '1;34',
	'cyan':     '0;36',     'bright green': '1;32',
	'red':      '0;31',     'bright cyan':  '1;36',
	'purple':   '0;35',     'bright red':   '1;31',
	'yellow':   '0;33',     'bright purple':'1;35',
	'dark gray':'1;30',     'bright yellow':'1;33',
	'normal':   '0',
}

titleColor = 'bright blue'
docColor = 'normal'
functionColor = 'bright blue'
warningColor = 'yellow'
notificationColor = 'normal'
normalColor = 'normal'
okColor='green'
errorColor='normal'
errorFileColor='bright red'
warningFileColor='bright yellow'
okFileColor='bright green'

def printColor(text, color='normal', endLine='\n'):
	"""prints text in color if verbosity is True

	:text: string that is printed out
	:color: color as in table above
	:verbosity: bool that determines whether to print or not
	:returns: None

	"""

	try:
		print("\033["+colorCodes[color]+"m", end='')
		print(text, end='')
		print("\033[0m", end=endLine)
	except:
		print(text)

def printWarning(text):
	if not inspect.stack()[1][3][0] == "<":	printColor(inspect.stack()[1][3]+": ", functionColor, '') 
	else: printColor("codeChecker: ", functionColor, '')
	printColor("WARNING: "+text, warningColor)

def printNotification(text):
	if not inspect.stack()[1][3][0] == "<":	printColor(inspect.stack()[1][3]+": ", functionColor, '') 
	else: printColor("codeChecker: ", functionColor, '')
	printColor(text, notificationColor)

def printInformation(title, doc):
	printColor("{:*^80}".format(title), titleColor)
	printColor(doc, docColor)

def printOkColor(text):
	printColor(text, okColor)

def printOkFileColor(text):
	printColor(text, okFileColor)

def printNormalColor(text):
	printColor(text)

def printErrorColor(text):
	printColor(text, errorColor)

def printErrorFileColor(text):
	printColor(text, errorFileColor)

def printWarningColor(text):
	printColor(text, warningColor)

def printWarningFileColor(text):
	printColor(text, warningFileColor)

def printErrors(errorList):
	for error in errorList:
		printColor(error, errorColor)

if __name__ == '__main__':
	print("Welcome to the test routine!")
	print("I will now try to print a line of text in each color.")
	for color in colorCodes.keys():
		printColor(color, color,)
