# make a man page for the library
#library(spm)
PATH<-"c:/Projects/General/SPM/R-libraries/"
promptPackage("spm",filename=paste(PATH,"spm/man/spm-package.Rd",sep=""),final=T)
# Create appropriate version number function
filename<-paste(PATH,"spm/R/spm.binary.version.R",sep="")
cat("\"spm.binary.version\"<-\n",file=filename)
cat("function() {\n",file=filename,append=T)
cat(paste("return(\"",system("spm -v",intern=TRUE),"\")\n",sep=""),file=filename,append=T)
cat("}\n",file=filename,append=T)
#exit
q()

