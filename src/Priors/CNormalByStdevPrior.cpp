//============================================================================
// Name        : CNormalByStdevPrior.cpp
// Author      : A.Dunn
// Date        : 13/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNormalByStdevPrior.h"

//**********************************************************************
// CNormalByStdevPrior::CNormalByStdevPrior(CNormalByStdevPrior *Prior = 0)
// Default Constructor
//**********************************************************************
CNormalByStdevPrior::CNormalByStdevPrior(CNormalByStdevPrior *Prior)
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
// void CNormalByStdevPrior::validate()
// validate
//**********************************************************************
void CNormalByStdevPrior::validate() {
  try {

  } catch (string Ex) {
    Ex = "CNormalByStdevPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalByStdevPrior::getResult(double Param)
// get Result
//**********************************************************************
double CNormalByStdevPrior::getResult(double Param) {
#ifndef OPTIMISE
  try {
#endif

    return 0.5 * ((Param-dMu)/dSigma) * ((Param-dMu)/dSigma);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CNormalByStdevPrior.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CNormalByStdevPrior::~CNormalByStdevPrior()
// Default De-Constructor
//**********************************************************************
CNormalByStdevPrior::~CNormalByStdevPrior() {
}
