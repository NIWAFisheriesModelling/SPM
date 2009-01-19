//============================================================================
// Name        : CSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CSelectivity.h"

//**********************************************************************
// CSelectivity::CSelectivity(CSelectivity *Selectivity = 0);
// Default Constructor
//**********************************************************************
CSelectivity::CSelectivity(CSelectivity *Selectivity)
: CBaseExecutableObject(Selectivity) {
}

//**********************************************************************
// void CSelectivity::validate()
// Validate
//**********************************************************************
void CSelectivity::validate() {
  try {
    // Base
    CBaseExecutableObject::validate();

  } catch (string Ex) {
    Ex = "CSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSelectivity::~CSelectivity()
// Default De-Constructor
//**********************************************************************
CSelectivity::~CSelectivity() {
}
