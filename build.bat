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
strip spm_unittests.exe
strip spm_unoptimised.exe

rem make manual
cd doc
cd manual
call build.bat > build.log
cd ..
cd ..

rem make R libraries
cd R-libraries
call build.bat > build.log
cd ..

rem Make the installer
rm -f Setup*.exe
cd installer
call makeInstall.bat > makeInstall.log
cd ..

rem Make a zip file and copy to server
rem rm -f spm.zip
rem cd build
rem call makeZIP.bat > makeZIP.log
rem cd ..

rem Unit tests
spm_unittests.exe --report_level=short

rem Copy to the server
copy spm.exe \\niwa.local\groups\Wellington\NIWAFisheries\bin\ /Y
copy Setup_SPM.exe \\niwa.local\groups\Wellington\NIWAFisheries\bin\ /Y
rem copy spm.zip \\niwa.local\groups\Wellington\NIWAFisheries\bin\ /Y
copy doc\manual\SPM.pdf \\niwa.local\groups\Wellington\NIWAFisheries\bin\ /Y
