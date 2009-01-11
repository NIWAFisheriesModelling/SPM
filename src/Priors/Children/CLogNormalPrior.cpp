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
// CLogNormalPrior::CLogNormalPrior(CLogNormalPrior *Prior = 0)
// Default Constructor
//**********************************************************************
CLogNormalPrior::CLogNormalPrior(CLogNormalPrior *Prior)
: CPrior(Prior) {

  // Variables
  dMu     = 0.0;
  dCv     = 0.0;

  // Copy Construct
  if (Prior != 0) {
    dMu = Prior->getMu();
    dCv = Prior->getCv();
  }
}

//**********************************************************************
// void CLogNormalPrior::validate()
// validate
//**********************************************************************
void CLogNormalPrior::validate() {
  try {

  } catch (string Ex) {
    Ex = "CLogNormalPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLogNormalPrior::getResult(double Param)
// get Result
//**********************************************************************
double CLogNormalPrior::getResult(double Param) {
#ifndef OPTIMISE
  try {
#endif

    double dRet = 0.0;
    dSigma = sqrt(log(1+dCv*dCv));
    dRet = log(Param) + 0.5 * pow(log(Param/dMu)/dSigma + dSigma*0.5, 2);
    return dRet;

#ifndef OPTIMISE
  } catch (string Ex) {
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
