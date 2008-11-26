# $Id: spm.unpaste.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.unpaste"<-
function(string, sep)
{
  if(spm.inR()) {
    return(unlist(strsplit(string, " ")))
  }
  if(spm.inS()) {
# this code written by Ralph Coburn
    write(string, "unpaste.temp.output")
    scan("unpaste.temp.output", w = "")
  }
  else {
# in S+
    unlist(unpaste(string, sep))
  }
}
