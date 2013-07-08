#!/usr/bin/env python3
'''errors.py
' 
' Defines Errors for format mistakes
'
' Copyright (C) 2013 Fabian Neuschmitd. All Rights Reserved.
' Written by Fabian Neuschmidt (fabian.neuschmidt@googlemail.com)
'
' This program is free software: you can redistribute it and/or modify it under
' the terms of the GNU General Public License as published by the Free Software
' Foundation, either version 3 of the License, or (at your option) any later
' version.
'''

class Error(Exception):
	'''Base class for exceptions in this module'''
	pass

class CodeIncompleteError(Error):
	"""Exception raised if 'TODO', 'FIXME' or 'BUG' appears in source
	
	Attributes:
		line -- source line in which the error appeared
		insect -- word that raised the error
	"""

	def __init__(self, line, insect):
		self.message = "CodeIncompleteError: '{}' found in line {}!".format(insect, line)

class LineTooLongError(Error):
	"""Exception raised if the length of a line of code exceeds 80 characters
	
	Attributes:
		line -- source line in which the error appeared
		message -- explanation of the error
	"""

	def __init__(self, line, message):
		self.message = message

class HeaderIncompleteError(Error):
	"""Exception raised if Header is missiong or not matching global criteria
	
	Attributes:
		message -- explanation of the error
	"""

	def __init__(self, message):
		self.message = message

class DocumentationIncompleteError(Error):
	"""Exception raised if densiy of comments is too low
	
	Attributes:
		message -- explanation of the error
	"""

	def __init__(self, message):
		self.message = message
