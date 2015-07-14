#******************************************************************
# PYTHON script to update spm.zip
# ******************************************************************

import string
import datetime
import os

##################################################################
# Define paths
##################################################################

BASE     = 'C:\\Projects\\General\\SPM\\'
BUILD    = BASE + 'build\\'
RELEASE  = BASE + 'build\\Release\\'
BIN      = BASE + ''
RLIB     = BASE + 'R-libraries\\'
DOC      = BASE + 'doc\\manual\\'
EXAMPLES = BASE + 'examples\\'
SRC      = BASE + 'src\\'

##################################################################
print('\n1. Cleanup and create directories')
os.chdir(BASE)
#os.system('rd /S /Q \"' +  RELEASE + '\"')
os.system('md \"' +  RELEASE + '\"')
os.system('md \"' +  RELEASE + 'R-library\"')
os.system('md \"' +  RELEASE + 'Examples\"')
os.system('md \"' +  RELEASE + 'source\"')
os.system('md \"' +  RELEASE + 'Linux\"')

##################################################################
print('\n\n2. Update with the latest version')
os.chdir(BASE)
os.system('cp -r -f ' + BIN  + 'spm.exe '           + RELEASE + 'spm.exe')
os.system('cp -r -f ' + BIN  + 'spm_unittests.exe ' + RELEASE + 'spm_unittests.exe')
os.system('cp -r -f ' + RLIB + 'spm_1.1.zip '       + RELEASE + 'R-library\\spm_1.1.zip')
os.system('cp -r -f ' + RLIB + 'spm_1.1.tar.gz '    + RELEASE + 'R-library\\spm_1.1.tar.gz')
os.system('cp -r -f ' + DOC  + 'spm.pdf '           + RELEASE + 'spm.pdf')

##################################################################
print('\n\n3. Get the linux 64-bit version from MateVM')
os.chdir(RELEASE)
# Pull from VMMate
# Do this manually the first time to store the RSA fingerprint
os.system('scp -batch -pw statistic alistair@MateVM:projects/general/SPM/spm Linux/')
os.system('scp -batch -pw statistic alistair@MateVM:projects/general/SPM/spm_unittests Linux/')
# Put to odin
os.system('scp -batch -pw Fox20003 Linux/spm dunn@odin.niwa.co.nz:bin/')

##################################################################
os.chdir(BASE)
print('\n\n4a. Copy the examples directory to the release directory')
cmd = 'svn export ' + EXAMPLES + ' ' + RELEASE + 'Examples --force'
os.system(cmd)

##################################################################
os.chdir(BASE)
print('\n\n4b. Copy the src directory to the release directory')
cmd = 'svn export ' + SRC + ' ' + RELEASE + 'source --force'
os.system(cmd)

##################################################################
print('\n\n5. Compress and update the *.zip file')
os.chdir(RELEASE)
os.system('rm -rf spm.zip')
os.system('zip -r -u -D -T ../../spm.zip *')

##################################################################
print('\n\n6. And copy the resulting file onto the FTP site')
os.chdir(BASE)
os.system('ftp -s:build\\ftp.dat')
os.chdir(BASE)
#os.system('rd /S /Q \"' +  RELEASE + '\"')

