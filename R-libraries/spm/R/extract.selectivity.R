"extract.selectivity" <-
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
  res$selectivity.label<-substring(lines[index.start+2],20)
  data<-spm.string.to.vector.of.words(lines[(index.start+3):(index.end-1)],sep=",")
  data<-matrix(data,ncol=2,byrow=TRUE)
  data<-data.frame("ages"=as.numeric(data[-1,1]),"values"=as.numeric(data[-1,2]))
  res$data<-data
  return(res)
}

