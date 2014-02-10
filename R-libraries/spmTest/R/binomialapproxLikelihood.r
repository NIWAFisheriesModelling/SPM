binomialapproxLikelihood<-function(observed,expected,errorValue,processError=0,delta=1e-11) {
  # double dErrorValue  = adjustErrorValue(processError[i], errorValue[i]);
  # double dStdError    = sqrt((CMath::zeroFun(expected[i],delta) * CMath::zeroFun(1.0-expected[i],delta))/dErrorValue);
  # double dScore       = log(dStdError) + 0.5 * pow((observed[i] - expected[i])/dStdError,2.0);
  errorValue<- ifelse(processError>0,(1.0/(1.0/errorValue + 1.0/processError)),errorValue)
  stdError    = sqrt((spm.zeroFun(expected,delta) * spm.zeroFun(1.0-expected,delta))/errorValue)
  res<- log(stdError) + 0.5 * (((observed - expected)/stdError)^2)
  return(res)
}
