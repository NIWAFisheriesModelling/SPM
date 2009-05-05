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
  throw string("CLogNormalWithQLikelihood.simulateObserved() not yet implemented");
}

//**********************************************************************
// CLogNormalWithQLikelihood::~CLogNormalWithQLikelihood()
// Destructor
//**********************************************************************
CLogNormalWithQLikelihood::~CLogNormalWithQLikelihood() {
}
