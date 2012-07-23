"extract.observation" <-
function(lines){
  if(missing(lines)) stop("ERROR: Missing argument lines")
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$report.type<-substring(lines[index.start+1],14)
  res$observation.label<-substring(lines[index.start+2],20)
  variables<-spm.string.to.vector.of.words(lines[index.start+3],sep=",")
  if((index.end-index.start)>4) {
    data<-spm.string.to.vector.of.words(lines[(index.start+4):(index.end-1)],sep=",")
    data<-matrix(data,ncol=6,byrow=TRUE)
    data<-as.data.frame(data)
    names(data)<-variables
    data<-data.frame("area"=data[,1], observed=data[,2], expected=data[,3], residual=data[,4], errorvalue=data[,5], score=data[,6])
    data$area<-as.character(data$area)
    data$observed<-as.numeric(as.character(data$observed))
    data$expected<-as.numeric(as.character(data$expected))
    data$residual<-as.numeric(as.character(data$residual))
    data$errorvalue<-as.numeric(as.character( data$errorvalue))
    data$score<-as.numeric(as.character(data$score))
    res$data<-data
  } else {
    res$data<-"No data"
  }
  return(res)
}

