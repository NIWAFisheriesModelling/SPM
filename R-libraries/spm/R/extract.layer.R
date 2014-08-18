"extract.layer" <-
function(lines){
  if(missing(lines)) stop("ERROR: Missing argument lines")
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  if(substring(lines[5+index.start],1,8)=="from_row") {
    variables<-spm.string.to.vector.of.words(lines[5+index.start])
    values<-spm.string.to.vector.of.words(lines[(6+index.start):(index.end-1)])
    nrows<-length((6+index.start):(index.end-1))
    values<-as.data.frame(matrix(values,nrow=nrows,byrow=TRUE))
    names(values)<-variables
  } else {
    values<-spm.string.to.vector.of.words(lines[(5+index.start):(index.end-1)])
    nrows<-length((5+index.start):(index.end-1))
    values<-matrix(values,nrow=nrows,byrow=TRUE)
  }
  res <- list()
  res$layer<-substring(lines[index.start+2],8)
  res$year<-substring(lines[index.start+3],7)
  res$"time_step"<-substring(lines[index.start+4],12)
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$report.type<-substring(lines[index.start+1],14)
  res$data<-values
  return(res)
}



