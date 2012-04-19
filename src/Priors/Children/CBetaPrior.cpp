//============================================================================
// Name        : CBetaPrior.cpp
// Author      : A.Dunn
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CBetaPrior.h"

//**********************************************************************
// CBetaPrior::CBetaPrior(CBetaPrior *Prior)
// Default Constructor
//**********************************************************************
CBetaPrior::CBetaPrior() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
  pParameterList->registerAllowed(PARAM_A);
  pParameterList->registerAllowed(PARAM_B);
}

//**********************************************************************
// void CBetaPrior::validate()
// validate
//**********************************************************************
void CBetaPrior::validate() {
  try {
    // Base
    CPrior::validate();

    // Assign our parameters
    dMu     = pParameterList->getDouble(PARAM_MU);
    dSigma  = pParameterList->getDouble(PARAM_SIGMA);
    dA      = pParameterList->getDouble(PARAM_A);
    dB      = pParameterList->getDouble(PARAM_B);

  } catch (string &Ex) {
    Ex = "CBetaPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CBetaPrior::getResult(double Param)
// get Result
//**********************************************************************
double CBetaPrior::getResult(double Param) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet = 0.0;

    dV = (dMu - dA) / (dB - dA);
    dT = (((dMu - dA) * (dB - dMu)) / (dSigma * dSigma)) - 1.0;
    dM = dT * dV;
    dN = dT * (1.0 - dV);
    dRet = ((1.0 - dM) * log(Param - dA)) + ((1.0 - dN) * log(dB - Param));

    return dRet;

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CBetaPrior.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CBetaPrior::~CBetaPrior()
// Default De-Constructor
//**********************************************************************
CBetaPrior::~CBetaPrior() {
}
