//============================================================================
// Name        : CLogNormalWithQLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CLogNormalWithQLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CLogNormalWithQLikelihood::CLogNormalWithQLikelihood()
// Default Constructor
//**********************************************************************
CLogNormalWithQLikelihood::CLogNormalWithQLikelihood() {
}

//**********************************************************************
// double CLogNormalWithQLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our ErrorValue based on Process Error
//**********************************************************************
double CLogNormalWithQLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for c.v. process error
  if(processError > 0.0)
    return (sqrt(errorValue*errorValue + processError*processError));

  return errorValue;
}

//**********************************************************************
// double CLogNormalWithQLikelihood::getResult(double expected, double observed, double errorValue,
//                                                                double processError, double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
double CLogNormalWithQLikelihood::getResult(double expected, double observed, double errorValue,
                                                                double processError, double delta) {

  //Add in process error if defined
  errorValue = adjustErrorValue(processError, errorValue);

  double dSigma = sqrt(log(1+ errorValue*errorValue));
  double dTemp = log(observed / CMath::zeroFun(expected,delta)) / dSigma + 0.5*dSigma;
  dTemp = log(dSigma) + 0.5 * dTemp * dTemp;

  return dTemp;
}

//**********************************************************************
// double CLogNormalWithQLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
//
//**********************************************************************
double CLogNormalWithQLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  double logvar = 0.0;
  double logmean = 0.0;
  double result = 0.0;

  // Should never happen ...
  if(expected <= 0.0) {
    return(0.0) ;
  }

 //Add in process error if defined
  errorValue = adjustErrorValue(processError, errorValue);

  logvar = sqrt(log(errorValue*errorValue + 1.0));
  logmean = log(expected) - (logvar*logvar)/2.0;
  //result = exp(rnorm(logmean, logvar)); -- need a random normal deviate here ---> need to link to randome functions in BOOST
  // Here we need a random normal number with mean = logmean and sigma = logvar.
  // The BOOST random number generator mersenne_twister
  // and use the distribution normal_distribution.hpp
  // note a random class is requires that is initialised with a defined seed.
  // this should also be used by DESolver for generating its random uniform numbers
  // next line delete once we have fixed up the above
  // Other likelihhods will require other distributions... but probably only the uniform.
  result = exp(logmean);
  return result;
}

//**********************************************************************
// CLogNormalWithQLikelihood::~CLogNormalWithQLikelihood()
// Destructor
//**********************************************************************
CLogNormalWithQLikelihood::~CLogNormalWithQLikelihood() {
}
