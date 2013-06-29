#!/usr/bin/env python
'''rules.cc
' 
' Checks codefiles for formal mistakes
'
' Copyright (C) 2013 Fabian Neuschmitd. All Rights Reserved.
' Written by Fabian Neuschmidt (fabian.neuschmidt@googlemail.com)
'
' This program is free software: you can redistribute it and/or modify it under
' the terms of the GNU General Public License as published by the Free Software
' Foundation, either version 3 of the License, or (at your option) any later
' version.
'''

#Static imports
import argparse		#processing of arguments
import os			#get path
import re			#regular expressions
import sys,inspect		#get script location
import pkgutil			#dynamic import

def parseArgs():
	""" parsing of arguments and configuration of help output 
	
	:returns: passed arguments in dictionary structure

	"""
	parser = argparse.ArgumentParser(description='process and help') 
	parser.add_argument('-d', nargs='+', metavar='DIR', help="Directories or files to be checked") #DONE
	parser.add_argument('-dd', nargs='+', metavar='DIR', help="Directories and sub directories to be checked ") #DONE
	parser.add_argument('-c', nargs='+', metavar='FILE', help="Rulefiles to be used") #DONE
	parser.add_argument('-f', nargs='+', metavar='EXT', help="filetypes to be checkes") #DONE
	parser.add_argument('-b', nargs='+', metavar='EXT', help = "filetypes to be ignored") #DONE 
	parser.add_argument('-a', action='store_true', help= "check for all errors") #TODO
	parser.add_argument('-e', nargs='+', metavar='ERR', help="check errors with given error codes") #TODO
	parser.add_argument('-i', nargs='+', metavar='ERR', help="show information about given error code") #TODO
	parser.add_argument('-r', action='store_true', help="FILENAME is to be interpreted as regular expression") #DONE
	parser.add_argument('-v', action='store_true', help="enable verbosity") #TODO
	return vars(parser.parse_args())

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
					print("WARNING:", dir, "is not a valid file or directory and will be ignored!") #TODO hervorheben?
			except PermissionError:
				print("WARNING:", dir, "is not accessible and will be ignored!") #TODO hervorheben?

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
			print("WARNING:", dir, "is not accessible and will be ignored!") #TODO hervorheben?

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
					print("WARNING", dir, "is not a valid directory and will be ignored!") #TODO hervorheben?
			except PermissionError:
				print("WARNING:", dir, "is not accessible and will be ignored!") #TODO hervorheben?

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
	# useless if '-f' is specified, because '-f' has a higher priority
	elif fileTypeBans:
		for i in range(len(filePaths)-1,-1,-1):
			for fTB in fileTypeBans:
				if re.search(fTB+'$',filePaths[i]):
					del filePaths[i]

	#return list with absolute file paths
	return sorted(filePaths)

def collectRules(ruleFileNames=[], ruleFileNamesAreRegular=False, verbosity=False):
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
	if verbosity: print("rulesDirectory:", rulesDirectory)
	if rulesDirectory not in sys.path:
		sys.path.insert(0, rulesDirectory)
	#import modules according to -c and -r
	for importer, packageName, _ in pkgutil.iter_modules([rulesDirectory]):
		if ruleFileNames:
			if ruleFileNamesAreRegular:
				match=False
				for regularRuleFileNameExpression in ruleFileNames:
					if re.search(regularRuleFileNameExpression, packageName): # if package_name fits the regular Expression
						match=True
				if match==True:
					if packageName not in sys.modules:
						module = importer.find_module(packageName).load_module(packageName)
						if verbosity: print("Module loaded:", module)
			else:
				for ruleFileName in ruleFileNames:
					if packageName == ruleFileName or packageName == ruleFileName.split('.')[0]: #with or without '.xxx' ending
						if packageName not in sys.modules:
							module = importer.find_module(packageName).load_module(packageName)
							if verbosity: print("Module loaded:", module)
		else:
			if packageName not in sys.modules:
				module = importer.find_module(packageName).load_module(packageName)
				if verbosity: print("Module loaded:", module)





#	for ruleFile in os.listdir(rulesDirectory):
#		if ruleFile != '__pycache__':
#			ruleFile=ruleFile[:-3]
#			print(ruleFile)
#			import ruleFile
#			exp=ruleFile+"."+ruleFile+"()"
#			print("EXP:", exp)
#			exec(exp)
argVars=parseArgs()
#print(argVars)
#print(collectFilePaths(argVars['d'],argVars['dd'],argVars['f'],argVars['b'],argVars['v']))
collectRules(argVars['c'],argVars['r'], argVars['v'])
