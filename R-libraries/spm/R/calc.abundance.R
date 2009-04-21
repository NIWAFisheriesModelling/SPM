"calc.abundance" <-
function(data,categories=NULL,ages=NULL,total=T) {
  if(!is.null(categories)) data<-data[data$category %in% categories,]
  index<-paste(data$col,data$row,sep="-")
  data<-data[,regexpr("age",names(data))>0]
  Ages<-substring(names(data),5)
  Ages<-as.numeric(substring(Ages,1,nchar(Ages)-1))
  if(!is.null(ages)) {
    data<-data[,Ages %in% ages]
    Ages<-Ages[Ages %in% ages]
  }
  data<-aggregate(data,by=list("index"=index),sum)
  index<-unpaste(data$index,sep="-")
  Col<-as.numeric(index[[1]])
  Row<-as.numeric(index[[2]])
  if(length(Ages)==1) {
    data$Total<-data[,-1]
  }
  data$total<-apply(data[,-1],1,sum)
  data$row<-Row
  data$column<-Col
  row.names(data)<-1:nrow(data)
  if(total) return(data[,names(data) %in% c("row","column","total")])
  else return(data)
}
