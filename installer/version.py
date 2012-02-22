import os
import string
import linecache
command = "..\\spm -v > version.txt"
version=os.system(command)
INFILE = open('version.txt','rt')
FILE = open('version.nsi', 'w')
FILE.write("!define PRODUCT_VERSION \"")
line = linecache.getline('version.txt', 1)
find = line.find(' ')
FILE.write(line[0:find])
FILE.write("\"")
INFILE.close()
#os.unlink('version.txt')
