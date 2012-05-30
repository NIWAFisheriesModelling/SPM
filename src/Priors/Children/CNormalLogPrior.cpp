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
#include "../../Helpers/CError.h"

//**********************************************************************
// CNormalLogPrior::CNormalLogPrior()
// Default Constructor
//**********************************************************************
CNormalLogPrior::CNormalLogPrior() {
  // Register parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
}

//**********************************************************************
// void CNormalLogPrior::validate()
// validate
//**********************************************************************
void CNormalLogPrior::validate() {
  try {

    // Assign parameters
    dMu     = pParameterList->getDouble(PARAM_MU);
    dSigma  = pParameterList->getDouble(PARAM_SIGMA);

    // Validate parent
    CPrior::validate();

    // Local validation
    if (dSigma <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA, PARAM_ZERO);

  } catch (string &Ex) {
    Ex = "CNormalLogPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalLogPrior::getResult(double Param)
// get Result
//**********************************************************************
double CNormalLogPrior::getResult(double Param) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet = 0.0;
    dRet = log(Param) + 0.5 * pow((log(Param)-dMu)/dSigma, 2);
    return dRet;

#ifndef OPTIMIZE
  } catch (string &Ex) {
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
