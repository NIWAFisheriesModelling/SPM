binomialLikelihood<-function(observed,expected,errorValue,processError=0,delta=1e-11) {
  # double dErrorValue  = adjustErrorValue(processError[i], errorValue[i]);
  # double dScore       =  - CMath::lnFactorial(dErrorValue)
  #                        - CMath::lnFactorial(dErrorValue * (1.0 - observed[i]))
  #                        - CMath::lnFactorial(dErrorValue * observed[i])
  #                        + dErrorValue * observed[i] * log(CMath::zeroFun(expected[i], delta))
  #                        + dErrorValue * (1.0 - observed[i]) * log(CMath::zeroFun(1.0 - expected[i], delta));
  errorValue<- ifelse(processError>0,(1.0/(1.0/errorValue + 1.0/processError)),errorValue)
  lfact<-function(n) lgamma(n+1)
  res<- lfact(errorValue) - lfact(errorValue*(1-observed)) - lfact(errorValue*observed) + errorValue*observed*log(spm.zeroFun(expected,delta)) + errorValue*(1-observed)*log(spm.zeroFun(1-expected,delta))
  return(-res)
}
