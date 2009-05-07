"spm.inR"<-
function()
{
  if(!exists("version")) return(F)
  else if(is.null(version$language)) return(F)
  else return(version$language == "R")
}
