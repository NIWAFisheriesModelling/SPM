lognormalLikelihood<-function(observed,expected,errorValue,processError=0,delta=1e-11) {
  errorValue<-sqrt(processError^2 + errorValue^2)
  sigma<-sqrt(log(1+errorValue^2))
  res<-log(sigma) + 0.5 * (((log(observed/spm.zeroFun(expected,delta)))/sigma + 0.5*sigma)^2)
  return(res)
}
