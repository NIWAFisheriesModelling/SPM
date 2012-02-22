R --vanilla < make_version.R
Rcmd build --force spm
Rcmd INSTALL --build spm

copy spm_* \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
copy spm.html \\niwa.local\groups\Wellington\NIWAFisheries\R\ /Y
del spm.html
R --vanilla < update_packages.R


