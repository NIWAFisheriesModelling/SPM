//============================================================================
// Name        : CDoubleNormalSelectivity.cpp
// Author      : A. Dunn
// Date        : 7/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "CDoubleNormalSelectivity.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CDoubleNormalSelectivity::CDoubleNormalSelectivity()
// Default constructor
//**********************************************************************
CDoubleNormalSelectivity::CDoubleNormalSelectivity() {
  // Register estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA_L, &dSigmaL);
  registerEstimable(PARAM_SIGMA_R, &dSigmaR);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA_L);
  pParameterList->registerAllowed(PARAM_SIGMA_R);
}

//**********************************************************************
// void CDoubleNormalSelectivity::validate()
// validate
//**********************************************************************
void CDoubleNormalSelectivity::validate() {
  try {
    // Base
    CSelectivity::validate();

    // Populate our variables
    dMu     = pParameterList->getDouble(PARAM_MU);
    dSigmaL = pParameterList->getDouble(PARAM_SIGMA_L);
    dSigmaR = pParameterList->getDouble(PARAM_SIGMA_R);

  } catch (string Ex) {
    Ex = "CDoublenormalSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDoubleNormalSelectivity::calculateResult(int Age)
// calculate the results for our Vector
//**********************************************************************
double CDoubleNormalSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif
    double dRet = 0.0;
    // Do our double normal Function
    if (Age < dMu)
      dRet = pow(2.0,-((Age-dMu)/dSigmaL * (Age-dMu)/dSigmaL));
    else
      dRet = pow(2.0,-((Age-dMu)/dSigmaR * (Age-dMu)/dSigmaR));

    return dRet;

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CDoubleNormalSelectivity.calculateResult()->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CDoubleNormalSelectivity::~CDoubleNormalSelectivity()
// Default De-Constructor
//**********************************************************************
CDoubleNormalSelectivity::~CDoubleNormalSelectivity() {
}
