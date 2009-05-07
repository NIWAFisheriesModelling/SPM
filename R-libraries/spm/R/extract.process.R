"extract.process" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$report.type<-substring(lines[index.start+1],14)
  res$data<-NA
  return(res)
}

