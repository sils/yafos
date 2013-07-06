#!/usr/bin/env python
#import sys,os
#sys.path.insert(1, os.path.join(sys.path[0], '..'))
import printColor
import re
import errors

def todoCheck(lineList):
	"""raises CodeIncompleteError if 'TODO' is found in the file

	:lineList: file as list of strings
	:returns: all error messages

	"""
	pass


	returnList=[]
	for lineNumber in range(len(lineList)):
		try:
			if re.search("TODO", lineList[lineNumber]):
				raise errors.CodeIncompleteError(lineNumber+1,'TODO')
		except errors.CodeIncompleteError as CIerr:
			returnList.append(CIerr.message)
	return returnList

def fixmeCheck(lineList):
	"""raises CodeIncompleteError if 'FIXME' is found in the file

	:lineList: file as list of strings
	:returns: all error messages

	"""
	pass


	returnList=[]
	for lineNumber in range(len(lineList)):
		try:
			if re.search("FIXME", lineList[lineNumber]):
				raise errors.CodeIncompleteError(lineNumber+1,'FIXME')
		except errors.CodeIncompleteError as CIerr:
			returnList.append(CIerr.message)
	return returnList

def bugCheck(lineList):
	"""raises CodeIncompleteError if 'BUG' is found in the file

	:lineList: file as list of strings
	:returns: all error messages

	"""
	pass


	returnList=[]
	for lineNumber in range(len(lineList)):
		try:
			if re.search("BUG", lineList[lineNumber]):
				raise errors.CodeIncompleteError(lineNumber+1,'BUG')
		except errors.CodeIncompleteError as CIerr:
			returnList.append(CIerr.message)
	return returnList
