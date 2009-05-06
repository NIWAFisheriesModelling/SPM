# make a man page for the library
#library(spm)
promptPackage("spm",filename="spm/man/spm-package.Rd",final=T)
# Create appropriate version number function
filename<-"spm/R/spm.binary.version.R"
cat("\"spm.binary.version\"<-\n",file="spm/R/spm.binary.version.R")
cat("function() {\n",file=filename,append=T)
VERSION<-system("spm -v",intern=TRUE)
VERSION<-substring(VERSION,1,regexpr(" ",VERSION)-1)
cat(paste("return(\"",VERSION,"\")\n",sep=""),file=filename,append=T)
cat("}\n",file=filename,append=T)
#exit
q()

