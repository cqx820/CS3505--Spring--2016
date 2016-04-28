#!/usr/bin/python3

# Author: //TO DO - Teamname
# Date: 21 April 2016
# Purpose: This program splits an input text file into text files of the same
#          name with -<part number> appended with as many words per text file
#          as specified. The first argument must be the text file. Output files
#          will be in the same directory as the input file

import sys
import re

wordsPerFile = 200 # We will split the file to have this many words
deliminator = " " # Use this regex split words
fileNumber = 1 # Start with this number

readFile = "" # I will read into this variable"

def writeFile(fileName, fileContent):
    f = open(fileName, "w")
    f.write(fileContent)
    f.close

inputFile = open(sys.argv[1], 'r')
for line in inputFile:
    readFile += line
inputFile.close()

fileNameExtensionIndex = sys.argv[1].rfind(".")
fileNamePrefix = sys.argv[1][:fileNameExtensionIndex]
fileNameExtension = sys.argv[1][fileNameExtensionIndex:]

words = re.split(deliminator, readFile)
counter = 0
thisFile = ""
for word in words:
    thisFile += word + " "
    counter += 1
    if counter >= wordsPerFile:
        counter = 0
        fileName = fileNamePrefix + "-" + '{0:03d}'.format(fileNumber) + fileNameExtension
        writeFile(fileName, thisFile)
        fileNumber += 1
        thisFile = ""





