# $Id: spm.remove.last.words.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.remove.last.words"<-
function(string, words = 1)
{
  temp <- spm.unpaste(string, sep = " ")
  to.drop <- length(temp) - (0:(words - 1))
  paste(unlist(temp[ - to.drop]), collapse = " ")
}
