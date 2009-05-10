//============================================================================
// Name        : CBinomialApproxLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBinomialApproxLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CBinomialApproxLikelihood::CBinomialApproxLikelihood()
// Default Constructor
//**********************************************************************
CBinomialApproxLikelihood::CBinomialApproxLikelihood() {
}

//**********************************************************************
// double CBinomialApproxLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our error value based on process error
//**********************************************************************
double CBinomialApproxLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for N process error
  if( (errorValue > 0.0) && (processError > 0.0) )
    return (1.0/(1.0/errorValue + 1.0/processError));

  return errorValue;
}

//**********************************************************************
// double CBinomialApproxLikelihood::getResult(double expected, double observed, double errorValue,
//                                                                    double processError, double delta)
// Get the result from our likelihood
//**********************************************************************
double CBinomialApproxLikelihood::getResult(double expected, double observed, double errorValue,
                                                                double processError, double delta) {
  //Add in process error if defined
  errorValue = adjustErrorValue(processError, errorValue);

  double dStdError = sqrt((CMath::zeroFun(expected,delta) * CMath::zeroFun(1.0-expected,delta))/errorValue);
  double dTemp = log(dStdError) + 0.5 * pow((observed - expected)/dStdError,2.0);

  return dTemp;
}

//**********************************************************************
// double CBinomialApproxLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate observed value from our observation
//**********************************************************************
double CBinomialApproxLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  // Should never happen ...
  if(expected < 0.0)
    return 0.0;

 //Add in process error if defined
  errorValue = adjustErrorValue(processError, errorValue);

  //Get random number
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();
  double result = pRandom->getRandomBinomial(expected, errorValue);

  return result;
}

//**********************************************************************
// CBinomialApproxLikelihood::~CBinomialApproxLikelihood()
// Destructor
//**********************************************************************
CBinomialApproxLikelihood::~CBinomialApproxLikelihood() {
}
