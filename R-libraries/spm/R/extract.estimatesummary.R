# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.estimatesummary" <-
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
  data<-spm.string.to.vector.of.words(lines[(index.start+2):(index.end-1)],sep=" ")
  data<-matrix(data,ncol=5,byrow=TRUE)
  data<-data[(nrow(data)/2+1):nrow(data),]
  data<-data.frame("parameter"=data[,1],"lower_bound"=as.numeric(data[,2]),"upper_bound"=as.numeric(data[,3]),
                   "prior"=data[,4],"value"=as.numeric(data[,5]))
  res$data<-data
  return(res)
}

