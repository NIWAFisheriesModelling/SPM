# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"spm.make.filename"<-
function(file,path="")
{
  if(path != "") {
    plc<-substring(path, nchar(path))
    if(!(plc== "\\" | plc=="/")) path <- paste(path, "/", sep = "")
  }
  filename<-paste(path, file, sep = "")
  return(filename)
}
