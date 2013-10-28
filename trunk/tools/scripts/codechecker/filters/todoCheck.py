#!/usr/bin/env python3
import re

def filter(queue,name,lineList):
	"""returns error if 'TODO' is found in the file

	:lineList: file as list of strings
	:returns: all error messages in a list

	"""

	errorMessages=[name]
	
	pattern = re.compile(r"\bTODO\b")	
	for lineNumberMinusOne, line in enumerate(lineList):
		if pattern.search(line):
#		if re.search(r"\bTODO\b", line):
			errorMessages.append('"TODO" found in Line {}'.format(lineNumberMinusOne+1))
#	return errorMessages
	queue.put(errorMessages)