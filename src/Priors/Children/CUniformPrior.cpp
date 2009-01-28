//============================================================================
// Name        : CUniformPrior.cpp
// Author      : S.Rasmussen
// Date        : 10/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CUniformPrior.h"

//**********************************************************************
// CUniformPrior::CUniformPrior()
// Default Constructor
//**********************************************************************
CUniformPrior::CUniformPrior() {
  // Register allowed parameter
  pParameterList->registerAllowed(PARAM_C);
}

//**********************************************************************
// void CUniformPrior::validate()
// validate
//**********************************************************************
void CUniformPrior::validate() {
  try {
    // Base
    CPrior::validate();

    // Assign param
    dC    = pParameterList->getDouble(PARAM_C);

  } catch (string Ex) {
    Ex = "CUniformPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CUniformPrior::getResult(double Param)
// get the result from our prior
//**********************************************************************
double CUniformPrior::getResult(double Param) {
  return dC; // TODO: Validate this is accurate?
}

//**********************************************************************
// CUniformPrior::~CUniformPrior()
// Default De-Constructor
//**********************************************************************
CUniformPrior::~CUniformPrior() {
}
