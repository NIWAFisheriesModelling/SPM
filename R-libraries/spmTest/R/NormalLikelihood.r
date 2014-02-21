normalLikelihood<-function(observed,expected,errorValue,processError=0,delta=1e-11) {
  errorValue<-sqrt(processError^2 + errorValue^2)
  dSigma <- errorValue*expected
  dScore <- (observed-expected) / spm.zeroFun(errorValue * expected,delta)
  res <- log(dSigma) + 0.5 * (dScore^2)
  return(res)
}
