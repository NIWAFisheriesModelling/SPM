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
// CUniformLogPrior::CUniformLogPrior()
// Default Constructor
//**********************************************************************
CUniformLogPrior::CUniformLogPrior() {
  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_C);
}

//**********************************************************************
// void CUniformLogPrior::validate()
// validate
//**********************************************************************
void CUniformLogPrior::validate() {
  try {
    // Base
    CPrior::validate();

    // Assign var
    dC  = pParameterList->getDouble(PARAM_C);

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
#ifndef OPTIMIZE
  try {
#endif

    double dRet = log(Param);
    return dRet;

#ifndef OPTIMIZE
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
