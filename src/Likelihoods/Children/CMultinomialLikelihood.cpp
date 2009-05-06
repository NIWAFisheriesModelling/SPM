//============================================================================
// Name        : CMultinomialLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CMultinomialLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CMultinomialLikelihood::CMultinomialLikelihood()
// Default Constructor
//**********************************************************************
CMultinomialLikelihood::CMultinomialLikelihood() {
}

//**********************************************************************
// double CMultinomialLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust error value based on process error
//**********************************************************************
double CMultinomialLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for N process error
  if( (errorValue > 0.0) && (processError > 0.0) )
    return (1.0/(1.0/errorValue + 1.0/processError));

  return errorValue;
}
//**********************************************************************
// double CMultinomialLikelihood::getResult(double expected, double observed, double errorValue,
//                                                              double processError, double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
double CMultinomialLikelihood::getResult(double expected, double observed, double errorValue,
                                                                double processError, double delta) {

  errorValue = adjustErrorValue(processError, errorValue);

  double dTemp = CMath::lnFactorial(errorValue * observed)
                 - errorValue * observed * log(CMath::zeroFun(expected,delta));
  return dTemp;
}

//**********************************************************************
// double CMultinomialLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate observed value for our observation
//**********************************************************************
double CMultinomialLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  return expected;
}

//**********************************************************************
// CMultinomialLikelihood::~CMultinomialLikelihood()
// Destructor
//**********************************************************************
CMultinomialLikelihood::~CMultinomialLikelihood() {
}
