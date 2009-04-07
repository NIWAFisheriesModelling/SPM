# $Id: spm.string.to.vector.of.numbers.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.string.to.vector.of.numbers"<-
function(string,sep=",")
{
  as.numeric(spm.string.to.vector.of.words(string,sep))
}
