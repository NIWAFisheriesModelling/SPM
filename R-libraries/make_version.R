# Get SPM Version
VERSION<-system("spm -v",intern=TRUE)
VERSION<-substring(VERSION,1,regexpr(" ",VERSION)-1)
version.number<-substring(VERSION,1,regexpr("-",VERSION)-1)
version.date<-substring(VERSION,regexpr("-",VERSION)+1)

# Build DESCRIPTION file
filename<-"spm/DESCRIPTION"
cat("Package: spm\nTitle: SPM extract package\nVersion: ",file=filename)
cat(version.number,file=filename,append=TRUE)
cat("\nDate: ",file=filename,append=TRUE)
cat(version.date,file=filename,append=TRUE)
cat("\n",file=filename,append=TRUE)
cat("Author: A. Dunn\n",file=filename,append=TRUE)
cat("Description: A set of R functions for extracting from SPM configuration files.\n",file=filename,append=TRUE)
cat("Maintainer: A Dunn <a.dunn@niwa.co.nz>\n",file=filename,append=TRUE)
cat("License: CPL v1.0. See the SPM User Manual for license details.\n",file=filename,append=TRUE)
cat("URL: http://www.niwa.co.nz\n",file=filename,append=TRUE)
cat("Copyright: National Institute of Water & Atmospheric Research (NIWA), New Zealand Ministry of Fisheries (MFish).\n",file=filename,append=TRUE)

# Make a man page for the library
#filename<-"spm/man/spm-package.Rd"
#promptPackage("spm",filename=filename,final=T)

# Create R function to return version number
filename<-"spm/R/spm.binary.version.R"
cat("\"spm.binary.version\"<-\n",file=filename)
cat("function() {\n",file=filename,append=T)
cat(paste("return(\"",VERSION,"\")\n",sep=""),file=filename,append=T)
cat("}\n",file=filename,append=T)

# Write a .html file to report version number for the Wiki
cat(paste("Version",VERSION),file="spm.html")

# Exit
q()

