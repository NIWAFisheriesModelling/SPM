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
// CUniformPrior::CUniformPrior(CUniformPrior *Prior = 0)
// Default Constructor
//**********************************************************************
CUniformPrior::CUniformPrior(CUniformPrior *Prior)
: CPrior(Prior) {

  // Vars
  dC      = 0.0;

  // Copy Construct
  if (Prior != 0) {
    dC  = Prior->getC();
  }
}

//**********************************************************************
// void CUniformPrior::validate()
// validate
//**********************************************************************
void CUniformPrior::validate() {
  try {

  } catch (string Ex) {
    Ex = "CUniformPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CUniformPrior::~CUniformPrior()
// Default De-Constructor
//**********************************************************************
CUniformPrior::~CUniformPrior() {
}
