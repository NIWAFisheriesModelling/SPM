//============================================================================
// Name        : CUniformLogPrior.cpp
// Author      : A.Dunn
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CUniformLogPrior.h"

//**********************************************************************
// CUniformLogPrior::CUniformLogPrior(CUniformLogPrior *Prior = 0)
// Default Constructor
//**********************************************************************
CUniformLogPrior::CUniformLogPrior(CUniformLogPrior *Prior)
: CPrior(Prior) {

  // Vars
  dC      = 0.0;

  // Copy Construct
  if (Prior != 0) {
    dC = Prior->getC();
  }
}

//**********************************************************************
// void CUniformLogPrior::validate()
// validate
//**********************************************************************
void CUniformLogPrior::validate() {
  try {

  } catch (string Ex) {
    Ex = "CUniformLogPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CUniformLogPrior::getResult(double Param)
// get Result
//**********************************************************************
double CUniformLogPrior::getResult(double Param) {
#ifndef OPTIMISE
  try {
#endif

    double dRet = log(Param);
    return dRet;

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CUniformLogPrior.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CUniformLogPrior::~CUniformLogPrior()
// Default De-Constructor
//**********************************************************************
CUniformLogPrior::~CUniformLogPrior() {
}
