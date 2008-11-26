# $Id: spm.inR.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.inR"<-
function()
{
  if(!exists("version")) return(F)
  else if(is.null(version$language)) return(F)
  else return(version$language == "R")
}
