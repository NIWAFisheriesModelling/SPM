"spm.string.to.vector.of.words"<-
function(string,sep=",")
{
  temp <- spm.unpaste(string, sep = sep)
  return(temp[temp != ""])
}
