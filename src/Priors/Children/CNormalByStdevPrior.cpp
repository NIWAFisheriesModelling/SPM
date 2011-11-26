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
// CNormalByStdevPrior::CNormalByStdevPrior()
// Default Constructor
//**********************************************************************
CNormalByStdevPrior::CNormalByStdevPrior() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
}

//**********************************************************************
// void CNormalByStdevPrior::validate()
// validate
//**********************************************************************
void CNormalByStdevPrior::validate() {
  try {
    // Base
    CPrior::validate();

    // Assign parameters
    dMu     = pParameterList->getDouble(PARAM_MU);
    dSigma  = pParameterList->getDouble(PARAM_SIGMA);

  } catch (string &Ex) {
    Ex = "CNormalByStdevPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalByStdevPrior::getResult(double Param)
// get Result
//**********************************************************************
double CNormalByStdevPrior::getResult(double Param) {
#ifndef OPTIMIZE
  try {
#endif

    return 0.5 * ((Param-dMu)/dSigma) * ((Param-dMu)/dSigma);

#ifndef OPTIMIZE
  } catch (string &Ex) {
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
