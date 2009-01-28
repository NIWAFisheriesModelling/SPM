//============================================================================
// Name        : CPrior.cpp
// Author      : S.Rasmussen
// Date        : 10/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CPrior.h"

//**********************************************************************
// CPrior::CPrior()
// Default Constructor
//**********************************************************************
CPrior::CPrior() {
}

//**********************************************************************
// void CPrior::validate()
// Validate
//**********************************************************************
void CPrior::validate() {
  try {
    // Base
    CBaseValidate::validate();
  } catch (string Ex) {
    Ex = "CPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPrior::~CPrior()
// Default De-Constructor
//**********************************************************************
CPrior::~CPrior() {
}
