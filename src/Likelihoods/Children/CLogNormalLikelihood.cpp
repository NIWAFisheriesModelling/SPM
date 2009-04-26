//============================================================================
// Name        : CLogNormalLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CLogNormalLikelihood.h"

//**********************************************************************
// CLogNormalLikelihood::CLogNormalLikelihood()
// Default Constructor
//**********************************************************************
CLogNormalLikelihood::CLogNormalLikelihood() {

}

//**********************************************************************
// double CLogNormalLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our error value based on process error
//**********************************************************************
double CLogNormalLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for c.v. process error
  if(processError > 0)
    return (sqrt(errorValue*errorValue + processError*processError));

  return errorValue;
}

//**********************************************************************
// double CLogNormalLikelihood::getResult(double expected, double observed, double errorValue,
//                                                                  double processError, double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
double CLogNormalLikelihood::getResult(double expected, double observed, double errorValue,
                                                                      double processError, double delta) {
  throw string("CLogNormalLikelihood.getResult() not yet implmented");
}

//**********************************************************************
// double CLogNormalLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate an observed value from our expected
//**********************************************************************
double CLogNormalLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  throw string("CLogNormalLikelihood.simulateObserved() not yet implemented");
}

//**********************************************************************
// CLogNormalLikelihood::~CLogNormalLikelihood()
// Destructor
//**********************************************************************
CLogNormalLikelihood::~CLogNormalLikelihood() {
}
