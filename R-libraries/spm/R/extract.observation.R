"extract.observation" <-
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
  variables<-spm.string.to.vector.of.words(lines[index.start+2],sep=",")
  data<-spm.string.to.vector.of.words(lines[(index.start+3):(index.end-1)],sep=",")
  data<<-data
  data<-matrix(data,ncol=5,byrow=FALSE)
  data<-data.frame("area"=data[,1], expected=data[,2], observed=data[,3], errorvalue=data[,4], score=data[,5])
  data$area<-as.character(data$area)
  data$expected<-as.numeric(as.character(data$expected))
  data$observed<-as.numeric(as.character(data$observed))
  data$errorvalue<-as.numeric(as.character( data$errorvalue))
  data$score<-as.numeric(as.character(data$score))
  res$data<-data
  return(res)
}
