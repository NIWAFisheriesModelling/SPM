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
COPY spm.exe /Y c:\Windows\batch\spm.exe
rem COPY spm_unoptimised.exe /Y c:\Windows\batch\spm_unoptimised.exe

rem Update the Textpad syntax file
COPY /Y doc\manual\SPM.syn "C:\Program Files\TextPad 5\Samples\SPM.syn"

rem make manual
cd doc
cd manual
call build.bat > build.log
cd ..
cd ..

rem make R libraries
cd R-libraries
call build.bat > build.log

rem Install R library locally
Rcmd INSTALL spm_1.00.tar.gz
cd ..

rem Install S library locally
cd "c:\Program Files\sp2000\Library\SPM\
"c:\Program Files\sp2000\cmd\Splus" /BATCH input.s
cd "c:\Projects\General\SPM\"

rem Make the installer
rm -f Setup*.exe
cd installer
call makeInstall.bat > makeInstall.log
cd ..

rem remove spm from batch directory
del c:\Windows\batch\spm.exe

rem Unit tests
spm -v
spm_unittests.exe --report_level=short
