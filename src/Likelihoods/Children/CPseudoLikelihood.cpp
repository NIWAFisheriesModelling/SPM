//============================================================================
// Name        : CPseudoLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPseudoLikelihood.h"

//**********************************************************************
// CPseudoLikelihood::CPseudoLikelihood()
// Default Constructor
//**********************************************************************
CPseudoLikelihood::CPseudoLikelihood() {
}

//**********************************************************************
// double CPseudoLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate our Likelihood
//**********************************************************************
double CPseudoLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  try {
    throw string("Cannot use Pseudo-Likelihood during simulation");

  } catch (string Ex) {
    Ex = "CPseudoLikelihood.simulateObserved()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPseudoLikelihood::~CPseudoLikelihood()
// Destructor
//**********************************************************************
CPseudoLikelihood::~CPseudoLikelihood() {
}
