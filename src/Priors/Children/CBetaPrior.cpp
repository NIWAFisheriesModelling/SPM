//============================================================================
// Name        : CBetaPrior.cpp
// Author      : A.Dunn
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CBetaPrior.h"

//**********************************************************************
// CBetaPrior::CBetaPrior(CBetaPrior *Prior)
// Default Constructor
//**********************************************************************
CBetaPrior::CBetaPrior(CBetaPrior *Prior)
: CPrior(Prior) {

  // Variables
  dMu       = 0.0;
  dSigma    = 0.0;
  dA        = 0.0;
  dB        = 0.0;

  // Copy Construct
  if (Prior != 0) {
    dMu     = Prior->getMu();
    dSigma  = Prior->getSigma();
    dA      = Prior->getA();
    dB      = Prior->getB();
  }

}

//**********************************************************************
// void CBetaPrior::validate()
// validate
//**********************************************************************
void CBetaPrior::validate() {
  try {

  } catch (string Ex) {
    Ex = "CBetaPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CBetaPrior::getResult(double Param)
// get Result
//**********************************************************************
double CBetaPrior::getResult(double Param) {
#ifndef OPTIMISE
  try {
#endif

    double dRet = 0.0;

    dV = (dMu - dA) / (dB - dA);
    dT = (((dMu - dA) * (dB - dMu)) / (dSigma * dSigma)) - 1;
    dM = dT * dV;
    dN = dT * (1 - dV);
    dRet = (1-dM) * log(Param-dA) + (1-dN) * log(dB - Param);
    return dRet;

#ifndef OPTIMISE
  } catch (string Ex) {
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