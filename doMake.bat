cls
rem Revert Version.h
svn revert src/Version.h

rem Make SPM
cmake -G "MinGW Makefiles"
IF "%1"=="" (mingw32-make all) ELSE (mingw32-make %1)

rem Revert Version.h
rm -f src/Version.h.old
svn revert src/Version.h

rem Strip and place in local directories
strip spm.exe

rem Unit tests
spm_unittests.exe --report_level=short

