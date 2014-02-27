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
#include "../../Helpers/CError.h"

//**********************************************************************
// CLogNormalPrior::CLogNormalPrior()
// Default Constructor
//**********************************************************************
CLogNormalPrior::CLogNormalPrior() {

  // Register estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_CV, &dCv);

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

    // Populate our variables
    dMu   = pParameterList->getDouble(PARAM_MU);
    dCv   = pParameterList->getDouble(PARAM_CV);

    // Validate parent
    CPrior::validate();

    // Local validation
    if (dMu <= 0.0)
      CError::errorLessThanEqualTo(PARAM_MU, PARAM_ZERO);
    if (dCv <= 0.0)
      CError::errorLessThanEqualTo(PARAM_CV, PARAM_ZERO);

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
