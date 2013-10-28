#!/usr/bin/env python3
import re

def filter(queue,name,lineList):
	"""returns error if 'BUG' is found in the file

	:lineList: file as list of strings
	:returns: all error messages in a list

	"""

	errorMessages=[name]

	pattern = re.compile(r"\bBUG\b")
	for lineNumberMinusOne, line in enumerate(lineList):
		if pattern.search(line):
#		if re.search(r"\bBUG\b", line):
			errorMessages.append('"BUG" found in Line {}'.format(lineNumberMinusOne+1))
#	return errorMessages
	queue.put(errorMessages)