R --vanilla < run-roxygen.R
R --vanilla < SPM_make_version.R

Rcmd build --force spm
Rcmd INSTALL --build spm

rem copy spm_*.zip \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
rem copy spm_*.tar.gz \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
rem copy spm.html \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
del spm.html

R --vanilla < spmTest_make_version.R
Rcmd build --force spmTest
Rcmd INSTALL --build spmTest

rem copy spmTest_*.zip \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
rem copy spmTest_*.tar.gz \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
rem copy spmTest.html \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
del spmTest.html

R --vanilla < update_packages.R


