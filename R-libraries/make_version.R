# make a man page for the library
#library(spm)
promptPackage("spm",filename="spm/man/spm-package.Rd",final=T)
# Create appropriate version number function
filename<-"spm/R/spm.binary.version.R"
cat("\"spm.binary.version\"<-\n",file="spm/R/spm.binary.version.R")
cat("function() {\n",file=filename,append=T)
cat(paste("return(\"",system("spm -v",intern=TRUE),"\")\n",sep=""),file=filename,append=T)
cat("}\n",file=filename,append=T)
#exit
q()

