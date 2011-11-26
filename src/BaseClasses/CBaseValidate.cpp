//============================================================================
// Name        : CBaseValidate.cpp
// Author      : S.Rasmussen
// Date        : 28/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBaseValidate.h"

//**********************************************************************
// CBaseValidate::CBaseValidate()
// Default Constructor
//**********************************************************************
CBaseValidate::CBaseValidate() {

  // Default sLabel
  sLabel  = "";

  // Register Variable
  pParameterList->registerAllowed(PARAM_LABEL);
  pParameterList->registerAllowed(PARAM_TYPE);
}

//**********************************************************************
// void CBaseValidate::validate()
// Validate
//**********************************************************************
void CBaseValidate::validate() {
  try {
    // Populate our variable
    sLabel  = pParameterList->getString(PARAM_LABEL);

    // Validate known parameters against bad ones
    pParameterList->checkInvalidParameters();

  } catch(string &Ex) {
    Ex = "CBaseValidate.validate(" + getLabel() + ")->" + Ex; // No label defined yet.
    throw Ex;
  }
}

//**********************************************************************
// CBaseValidate::~CBaseValidate()
// Destructor
//**********************************************************************
CBaseValidate::~CBaseValidate() {
}
