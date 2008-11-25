//============================================================================
// Name        : CNormalLogPrior.cpp
// Author      : A.Dunn
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNormalLogPrior.h"

//**********************************************************************
// CNormalLogPrior::CNormalLogPrior(CNormalLogPrior *Prior = 0)
// Default Constructor
//**********************************************************************
CNormalLogPrior::CNormalLogPrior(CNormalLogPrior *Prior)
: CPrior(Prior) {

  // Vars
  dMu     = 0.0;
  dSigma  = 0.0;

  // Copy Construct
  if (Prior != 0) {
    dMu     = Prior->getMu();
    dSigma  = Prior->getSigma();
  }
}

//**********************************************************************
// void CNormalLogPrior::validate()
// validate
//**********************************************************************
void CNormalLogPrior::validate() {
  try {

  } catch (string Ex) {
    Ex = "CNormalLogPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalLogPrior::getResult(double Param)
// get Result
//**********************************************************************
double CNormalLogPrior::getResult(double Param) {
#ifndef OPTIMISE
  try {
#endif

    double dRet = 0.0;
    dRet = log(Param) + 0.5 * pow((log(Param)-dMu)/dSigma, 2);
    return dRet;

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CNormalLogPrior.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CNormalLogPrior::~CNormalLogPrior()
// Default De-Constructor
//**********************************************************************
CNormalLogPrior::~CNormalLogPrior() {
}
