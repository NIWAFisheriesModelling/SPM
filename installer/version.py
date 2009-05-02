import os
import string
command = "spm -v > version.txt"
version=os.system(command)
INFILE = open('version.txt','r')
FILE = open('version.nsi', 'w')
FILE.write("!define PRODUCT_VERSION \"")

for line in INFILE:
  find = string.find(line,' ')
  FILE.write(line[0:find])
FILE.write("\"")
INFILE.close()
os.unlink('version.txt')
