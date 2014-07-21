#!/bin/bash
# Remember to compile on virtual machine 'wellopensuse131'
# ssh wellopensuse131
svn update
svn revert src/Version.h
cmake -G "Unix Makefiles"
make all
rm -f src/Version.h.old
svn revert src/Version.h
strip spm
strip spm_unittests
strip spm_unoptimised
