# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"calc.abundance" <-
function(data,categories=NULL,ages=NULL,total=T) {
  if(!is.null(categories)) data<-data[data$Category %in% categories,]
  index<-paste(data$Row,data$Col)
  data<-data[,regexpr("Age",names(data))>0]
  Ages<-substring(names(data),5)
  Ages<-as.numeric(substring(Ages,1,nchar(Ages)-1))
  if(!is.null(ages)) {
    data<-data[,Ages %in% ages]
    Ages<-Ages[Ages %in% ages]
  }
  data<-aggregate(data,by=list("index"=index),sum)
  index<-unpaste(data$index,sep=" ")
  Row<-as.numeric(index[[1]])
  Col<-as.numeric(index[[2]])
  if(length(Ages)==1) {
    data$Total<-data[,-1]
  }
  data$Total<-apply(data[,-1],1,sum)
  data$Row<-Row+1
  data$Col<-Col+1
  row.names(data)<-1:nrow(data)
  if(total) return(data[,names(data) %in% c("Row","Col","Total")])
  else return(data)
}
