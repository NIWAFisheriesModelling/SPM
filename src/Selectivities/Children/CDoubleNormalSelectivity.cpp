//============================================================================
// Name        : CDoubleNormalSelectivity.cpp
// Author      : A. Dunn
// Date        : 7/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CDoubleNormalSelectivity.h"

//**********************************************************************
// CDoubleNormalSelectivity::CDoubleNormalSelectivity(CDoubleNormalSelectivity *Selectivity = 0)
// Default constructor
//**********************************************************************
CDoubleNormalSelectivity::CDoubleNormalSelectivity(CDoubleNormalSelectivity *Selectivity)
: CSelectivity(Selectivity) {

  // Variables
  dMu          = -1.0;
  dSigmaL      = -1.0;
  dSigmaR      = -1.0;

  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA_L, &dSigmaL);
  registerEstimable(PARAM_SIGMA_R, &dSigmaR);

  // Copy Construct
  if (Selectivity != 0) {
    dMu     = Selectivity->getMu();
    dSigmaL = Selectivity->getSigmaL();
    dSigmaR = Selectivity->getSigmaR();
  }
}

//**********************************************************************
// void CDoubleNormalSelectivity::validate()
// validate
//**********************************************************************
void CDoubleNormalSelectivity::validate() {
  try {
    // Nothing To Do
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
#ifndef OPTIMISE
  try {
#endif
    double dRet = 0.0;
    // Do our double normal Function
    if (Age < dMu)
      dRet = pow(2.0,-((Age-dMu)/dSigmaL * (Age-dMu)/dSigmaL));
    else
      dRet = pow(2.0,-((Age-dMu)/dSigmaR * (Age-dMu)/dSigmaR));

    return dRet;

#ifndef OPTIMISE
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
