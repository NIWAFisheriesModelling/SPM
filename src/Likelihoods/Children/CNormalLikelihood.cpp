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
  if(processError > 0)
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

  throw string("CNormalLikelihood.getResult() not yet implemented");
}

//**********************************************************************
// double CNormalLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate observed value for our observation
//**********************************************************************
double CNormalLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  throw string("CNormalLikelihood.simulateObserved() not yet implemented");
}

//**********************************************************************
// CNormalLikelihood::~CNormalLikelihood()
// Destructor
//**********************************************************************
CNormalLikelihood::~CNormalLikelihood() {
}
