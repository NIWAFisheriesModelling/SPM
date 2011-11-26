//============================================================================
// Name        : CNormalPrior.cpp
// Author      : A.Dunn
// Date        : 13/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNormalPrior.h"

//**********************************************************************
// CNormalPrior::CNormalPrior()
// Default Constructor
//**********************************************************************
CNormalPrior::CNormalPrior() {
  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_CV);
}

//**********************************************************************
// void CNormalPrior::validate()
// validate
//**********************************************************************
void CNormalPrior::validate() {
  try {
    // Base
    CPrior::validate();

    // Assign parameters
    dMu   = pParameterList->getDouble(PARAM_MU);
    dCv   = pParameterList->getDouble(PARAM_CV);

  } catch (string &Ex) {
    Ex = "CNormalPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalPrior::getResult(double Param)
// get Result
//**********************************************************************
double CNormalPrior::getResult(double Param) {
#ifndef OPTIMIZE
  try {
#endif

    return 0.5 * ((Param-dMu)/(dCv*dMu)) * ((Param-dMu)/(dCv*dMu));

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CNormalPrior.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CNormalPrior::~CNormalPrior()
// Default De-Constructor
//**********************************************************************
CNormalPrior::~CNormalPrior() {
}
