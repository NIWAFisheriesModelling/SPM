# $Id: spm.version.R,v 1.6 2007/11/26 20:40:31 adunn Exp $
"spm.version"<-
function()
{
  cat(paste("spm R package for use with spm ",spm.binary.version(),"\n",sep=""))
}
