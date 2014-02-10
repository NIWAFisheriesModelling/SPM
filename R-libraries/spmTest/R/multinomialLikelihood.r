multinomialLikelihood<-function(observed,expected,errorValue,processError=0,delta=1e-11) {
  errorValue<- ifelse(processError>0,(1.0/(1.0/errorValue + 1.0/processError)),errorValue)
  lfact<-function(n) lgamma(n+1)
  res<- lfact(errorValue * observed) - errorValue * observed * log(spm.zeroFun(expected,delta))
  return(res)
}
