"extract.ageingerrro" <-
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
  res$type<-substring(lines[index.start+2],20)
  col.labs<-spm.string.to.vector.of.words(lines[3+index.start],sep=",")
  values<-spm.string.to.vector.of.words(lines[(4+index.start):(index.end-1)],sep=",")
  values<-as.data.frame(matrix(values,ncol=length(col.labs),byrow=FALSE))
  names(values)<-col.labs
  values$ages<-as.numeric(as.character(values$ages))
  values<-apply(values,2,as.numeric)
  res$data<-values
  return(res)
}