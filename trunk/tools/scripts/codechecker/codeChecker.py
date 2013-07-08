#!/usr/bin/env python3
'''codeChecker.py
 
Checks code files for formal mistakes

Copyright (C) 2013 Fabian Neuschmidt. All Rights Reserved.
Written by Fabian Neuschmidt (fabian.neuschmidt@googlemail.com)

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
'''

#Static imports
import argparse		#processing of arguments
import os			#get path
import re			#regular expressions
import sys,inspect		#get script location
import pkgutil			#dynamic import
import printColor
import errors

def parseArgs():
	""" parsing of arguments and configuration of help output
	
	:returns: passed arguments in dictionary structure

	"""
	#python files in rules/
	ruleChoices=[packageName for importer, packageName, _ in \
	pkgutil.iter_modules([os.path.realpath(os.path.abspath(os.path.join(os.path.split(inspect.getfile( inspect.currentframe() ))[0],"rules")))])]
	#classes defined in errors.py
	errorChoices=[errorType for errorType,errorClass in inspect.getmembers(errors) if inspect.isclass(errorClass)and errorType!='Error']

	#configuration of help and arguments
	parser = argparse.ArgumentParser(
			formatter_class=argparse.RawDescriptionHelpFormatter,
			description=__doc__,
			epilog='''\
	\rAll these Options are optional, though one of the arguments following arguments must be given:
	\r-d, -dd, -i

	\rPossible choices for rulefiles (-c):
	\r{}
	\rPossible choices for errortypes (-e/-i):
	\r{}
	'''.format(ruleChoices, errorChoices))
	parser.add_argument('-d', nargs='+', metavar='DIR', help="Directories or files to be checked") #DONE
	parser.add_argument('-dd', nargs='+', metavar='DIR', help="Directories and sub directories to be checked ") #DONE
	parser.add_argument('-c', nargs='+', metavar='FILE', help="Rulefiles to be used") #DONE
	parser.add_argument('-f', nargs='+', metavar='EXT', help="filetypes to be checkes") #DONE
	parser.add_argument('-b', nargs='+', metavar='EXT', help = "filetypes to be ignored") #DONE 
	parser.add_argument('-a', action='store_true', help= "check for all errors") #DONE
	parser.add_argument('-e', nargs='+', metavar='ERR', choices=errorChoices, help="check errors with given error codes") #DONE
	parser.add_argument('-i', nargs='+', metavar='ERR', choices=errorChoices, help="show information about given error code") #TODO
	parser.add_argument('-r', action='store_true', help="FILENAME is to be interpreted as regular expression") #DONE
	parser.add_argument('-v', action='store_true', help="enable verbosity") #DONE
	localArgVars = vars(parser.parse_args())
	if localArgVars['d']==None and localArgVars['dd']==None and localArgVars['i']==None: localArgVars = vars(parser.parse_args('-h'.split()))
	if localArgVars['v']: printColor.printNotification("parsed args: "+str(localArgVars))
	return localArgVars

def collectFilePaths(singleLevelDirs=[],multiLevelDirs=[],fileTypePicks=[],fileTypeBans=[],verbosity=False):
	""" returns a list of absolute filenames of all files that should be checked

	:singleLevelDirs[]: Files or Directories that should be checked
	:multiLevelDirs[]: Directories that should be recursively checked  
	:fileTypePicks[]: Filetypes to list
	:fileTypeBans[]: Filetypes not to list
	:verbosity: verbosity level (bool)
	:returns: list of absolute filenames that match the above criteria

	"""
	mypath=os.getcwd()
	filePaths=[]
	
	# collect all files from singleLevelDirs
	if singleLevelDirs:
		for dir in singleLevelDirs:
			try:
				if not dir[0] == "/":
					dir = os.path.join(mypath,dir)
				if os.path.isfile(dir):
					filePaths.append(dir)
				elif os.path.isdir(dir):
					filePaths.extend([os.path.join(dir,f) for f in os.listdir(dir) if os.path.isfile(os.path.join(dir,f))])
				else:
					printColor.printWarning(dir+" is not a valid file or directory and will be ignored!")
			except PermissionError:
				printColor.printWarning(dir+ 'is not accessible and will be ignored')

	# recursive function used to collect filenames from subdirectories
	def recursiveCollect(dir):
		"""recursively collects filenames from directories and all their subdirectories

		:dir: parent directory 
		:returns: list of absolute filenames

		"""
		tempFilePathList = []
		try:
			for f in os.listdir(dir):
				if os.path.isfile(os.path.join(dir,f)):
					tempFilePathList.append(os.path.join(dir,f))
				elif os.path.isdir(os.path.join(dir,f)):
					tempFilePathList.extend(recursiveCollect(os.path.join(dir,f)))
		except PermissionError:
			printColor.printWarning(dir+"is not accessible and will be ignored!")
		return tempFilePathList

	# collect all files from multiLevelDirs
	if multiLevelDirs:
		for dir in multiLevelDirs:
			try:
				if not dir[0]=="/":
					dir = os.path.join(mypath,dir)
				if os.path.isdir(dir):
					filePaths.extend(recursiveCollect(dir))
				else:
					printColor.printWarning(dir+"is not a valid directory and will be ignored!")
			except PermissionError:
				printColor.printWarning(dir+"is not accessible and will be ignored!") 

	#remove duplicates:
	filePaths = list(set(filePaths))

	# if '-f' is specified, only check files with given endings
	if fileTypePicks:
		for i in range(len(filePaths)-1,-1,-1): #backwards to not saw off the branch we're sitting on
			match = 0
			for fTP in fileTypePicks:
				if re.search(fTP+'$',filePaths[i]): #true if filePath ends with fileTypePick
					match = 1
			if match == 0:
				del filePaths[i]

	# if '-b' is specified, ignore files with given endings

	if fileTypeBans:
		if fileTypePicks: fileTypeBans=list(set(fileTypeBans).difference(set(fileTypePicks))) # remove all fileTypeBans that are also fileTypePicks
		for i in range(len(filePaths)-1,-1,-1):
			banFilePath=False						# needed if more than one ban to prevent index errors
			for fTB in fileTypeBans:
				if re.search(fTB+'$',filePaths[i]):
					banFilePath=True
			if banFilePath==True:
				del filePaths[i]

	#return list with absolute file paths
	if verbosity: printColor.printNotification("collected following Files: "+str(filePaths))
	return sorted(filePaths)

def collectRules(useAllRules=False, ruleFileNames=[], ruleFileNamesAreRegular=False, errorTypes=[], verbosity=False):
	"""imports rules from rules/ and returns list of importet rules

	:ruleFileNames: rule files to be used
	:ruleFileNamesAreRegular: rule file names are regular expressions (bool)
	:verbosity: enables verbose output
	:returns: list of importet rules

	"""	
	#rule list
	ruleList=[]
	
	#rules folder, ALWAYS FOUND!
	rulesDirectory = os.path.realpath(os.path.abspath(os.path.join(os.path.split(inspect.getfile( inspect.currentframe() ))[0],"rules")))
	if verbosity: printColor.printNotification("rulesDirectory: "+rulesDirectory)
	if rulesDirectory not in sys.path:
		sys.path.insert(0, rulesDirectory)
	
	# collect Rules according to -a, -c, -r and -e parameters:
	for importer, packageName, _ in pkgutil.iter_modules([rulesDirectory]): # all modules in rules/
		module = importer.find_module(packageName).load_module(packageName)
		for functionName,function in inspect.getmembers(module): 
			if inspect.isfunction(function):								# all functions of module
				if (useAllRules or ((not ruleFileNames) and (not errorTypes))):										# if -a, others don't matter
					ruleList.append(function)
					if verbosity: printColor.printNotification("Collected Function: "+packageName+"."+functionName)
				else:												# not -a
					if ruleFileNames:									# if -c
						if ruleFileNamesAreRegular:							# if -c and -r
							match=False
							for regularRuleFileNameExpression in ruleFileNames:
								if re.search(regularRuleFileNameExpression, packageName):
									match=True
							if match==True:
								ruleList.append(function)
								if verbosity: printColor.printNotification("Collected Function: "+packageName+"."+functionName)
						else:												# if -c and not -r
							for ruleFileName in ruleFileNames:
								if ruleFileName == packageName:
									ruleList.append(function)
									if verbosity: printColor.printNotification("Collected Function: "+packageName+"."+functionName)
					if errorTypes:										# if -e
						for errorType in errorTypes:
							if re.search(errorType, function.__doc__):
								ruleList.append(function)
								if verbosity: printColor.printNotification("Collected Function: "+packageName+"."+functionName)

	# clean, print and return ruleList
	ruleList = list(set(ruleList))
	if verbosity: printColor.printNotification("ruleList: "+str(ruleList))
	return ruleList

def informAboutErrorTypes(errorList):
	"""prints error information, not yet "in a nice way"

	:errorList: List of errors to inform about
	:returns: None

	"""
	if errorList:
		for errorType in errorList:
			printColor.printInformation(errorType,eval("errors."+errorType+".__doc__"))
		if errorType: printColor.printInformation('','') # for a nice blue line at the bottom ;)

#MAIN ROUTINE
argVars=parseArgs()
informAboutErrorTypes(argVars['i'])
filePathList = collectFilePaths(argVars['d'],argVars['dd'],argVars['f'],argVars['b'],argVars['v'])
ruleFunctionList = collectRules(argVars['a'], argVars['c'],argVars['r'], argVars['e'], argVars['v'])

for filePath in filePathList:
	errorList=[]
	failedRoutines=[]
#	print('{}\r'.format(filePath), end='') # temporarily, not logged!
	try:
		with open(filePath, "r") as file:
			lineList = file.readlines()
			lineList=[line[:-1] for line in lineList] # cut off trailing '\n'
			for function in ruleFunctionList:
				try:
					errorList.extend(function(lineList)) # add function output to list
				except TypeError as err:
					failedRoutines.append(function.__name__)
			if not errorList:
				printColor.printOkFileColor(filePath) # printed if functions returned no errors
			else:
				printColor.printErrorFileColor(filePath)
				printColor.printErrors(errorList)
			if failedRoutines: [printColor.printWarning("test routine '{}' seems to have failed for this file!".format(routine)) for routine in failedRoutines]
	except UnicodeDecodeError as UDerr:
		printColor.printWarningFileColor(filePath)
		printColor.printWarning("Unable to read this file: {}".format(UDerr))
