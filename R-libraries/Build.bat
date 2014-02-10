R --vanilla < SPM_make_version.R
Rcmd build --force spm
Rcmd INSTALL --build spm

copy spm_*.zip \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
copy spm_*.tar.gz \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
copy spm.html \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
del spm.html

R --vanilla < spmTest_make_version.R
Rcmd build --force spmTest
Rcmd INSTALL --build spmTest

copy spmTest_*.zip \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
copy spmTest_*.tar.gz \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
copy spmTest.html \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
del spmTest.html

R --vanilla < update_packages.R


