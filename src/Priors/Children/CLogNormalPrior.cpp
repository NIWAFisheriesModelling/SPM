//============================================================================
// Name        : CLogNormalPrior.cpp
// Author      : A.Dunn
// Date        : 13/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CLogNormalPrior.h"

//**********************************************************************
// CLogNormalPrior::CLogNormalPrior()
// Default Constructor
//**********************************************************************
CLogNormalPrior::CLogNormalPrior() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_CV);
}

//**********************************************************************
// void CLogNormalPrior::validate()
// validate
//**********************************************************************
void CLogNormalPrior::validate() {
  try {
    // Base
    CPrior::validate();

    // Populate our variables
    dMu   = pParameterList->getDouble(PARAM_MU);
    dCv   = pParameterList->getDouble(PARAM_CV);

  } catch (string &Ex) {
    Ex = "CLogNormalPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLogNormalPrior::getResult(double Param)
// get Result
//**********************************************************************
double CLogNormalPrior::getResult(double Param) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet = 0.0;
    dSigma = sqrt(log(1+dCv*dCv));
    dRet = log(Param) + 0.5 * pow(log(Param/dMu)/dSigma + dSigma*0.5, 2);
    return dRet;

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CLogNormalPrior.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CLogNormalPrior::~CLogNormalPrior()
// Default De-Constructor
//**********************************************************************
CLogNormalPrior::~CLogNormalPrior() {
}
