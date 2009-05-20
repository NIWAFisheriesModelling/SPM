R --vanilla < make_version.R
Rcmd build --binary spm
Rcmd build spm
cat ./spm/R/*.R > Splus_source.S

