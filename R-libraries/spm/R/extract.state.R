# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.state" <-
function(file,path=""){
  if(missing(path)) path<-""
  filename<-spm.make.filename(path=path,file=file)
  res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  return(res)
}

