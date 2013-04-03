"extract.initialisationphase" <-
function(lines){
  if(missing(lines)) stop("ERROR: Missing argument lines")
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  col.labs<-spm.string.to.vector.of.words(lines[3+index.start])
  values<-spm.string.to.vector.of.words(lines[(4+index.start):(index.end-1)])
  values<-as.data.frame(matrix(values,ncol=length(col.labs),byrow=TRUE))
  names(values)<-col.labs
  values$category<-as.character(values$category)
  values$row<-as.numeric(as.character(values$row))
  values$column<-as.numeric(as.character(values$column))
  values[,4:ncol(values)]<-apply(values[,4:ncol(values)],2,function(x) as.numeric(as.character(x)))
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$report.type<-substring(lines[index.start+1],14)
  res$phase<-substring(lines[index.start+2],38)
  res$data<-values
  return(res)
}
