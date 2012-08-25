svn revert src/Version.h
cmake -G "Unix Makefiles"
make all
rm -f src/Version.h.old
svn revert src/Version.h
strip spm
