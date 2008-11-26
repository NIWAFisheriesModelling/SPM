# $Id: spm.remove.first.words.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.remove.first.words"<-
function(string, words = 1)
{
  paste(spm.unpaste(string, sep = " ")[ - (1:words)], collapse = " ")
}
