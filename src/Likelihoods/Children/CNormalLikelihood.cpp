//============================================================================
// Name        : CNormalLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CNormalLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CNormalLikelihood::CNormalLikelihood()
// Default Constructor
//**********************************************************************
CNormalLikelihood::CNormalLikelihood() {
}

//**********************************************************************
// double CNormalLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our error value based on process error.
//**********************************************************************
double CNormalLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for c.v. process error
  if(processError > 0.0)
    return (sqrt(errorValue*errorValue + processError*processError));

  return errorValue;
}

//**********************************************************************
// double CNormalLikelihood::getResult(double expected, double observed, double errorValue,
//                                                            double processError, double delta)
// Get result from likelihood for our observation
//**********************************************************************
double CNormalLikelihood::getResult(double expected, double observed, double errorValue,
                                                            double processError, double delta) {

  //Add in process error if defined
  errorValue = adjustErrorValue(processError, errorValue);

  double dSigma = errorValue*expected;
  double dTemp = (observed-expected) / CMath::zeroFun(errorValue*expected,delta);
  dTemp = log(dSigma) + 0.5 * (dTemp * dTemp);

  return dTemp;
}

//**********************************************************************
// double CNormalLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate observed value for our observation
//**********************************************************************
double CNormalLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  // Should never happen ...
  if(expected <= 0.0)
    return 0.0;

 //Add in process error if defined
  errorValue = adjustErrorValue(processError, errorValue);

  //Get random number
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();
  double result = pRandom->getRandomNormal(expected, (expected*errorValue));

  return result;
}

//**********************************************************************
// CNormalLikelihood::~CNormalLikelihood()
// Destructor
//**********************************************************************
CNormalLikelihood::~CNormalLikelihood() {
}
