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
  throw string("BinomialApproxLikelihood.adjustErrorValue() not yet implemented");
}

//**********************************************************************
// double CBinomialApproxLikelihood::getResult(double expected, double observed, double errorValue,
//                                                                    double processError, double delta)
// Get the result from our likelihood
//**********************************************************************
double CBinomialApproxLikelihood::getResult(double expected, double observed, double errorValue,
                                                                double processError, double delta) {

  throw string("BinomialApproxLikelihood.getResult() Not yet implemented");
}

//**********************************************************************
// double CBinomialApproxLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate observed value from our observation
//**********************************************************************
double CBinomialApproxLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  throw string("CBinomialApproxLikelihood.simulateObserved() not yet implemented");
}

//**********************************************************************
// CBinomialApproxLikelihood::~CBinomialApproxLikelihood()
// Destructor
//**********************************************************************
CBinomialApproxLikelihood::~CBinomialApproxLikelihood() {
}
