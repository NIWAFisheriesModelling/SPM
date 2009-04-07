# $Id: spm.string.to.vector.of.words.R,v 1.3 2007/11/12 21:01:38 adunn Exp $
"spm.string.to.vector.of.words"<-
function(string,sep=",")
{
  temp <- spm.unpaste(string, sep = sep)
  return(temp[temp != ""])
}
