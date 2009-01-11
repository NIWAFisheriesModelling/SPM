//============================================================================
// Name        : CBaseExecutableObject.cpp
// Author      : S.Rasmussen
// Date        : 31/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CBaseExecutableObject.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CBaseExecutableObject::CBaseExecutableObject()
// Default Constructor
//**********************************************************************
CBaseExecutableObject::CBaseExecutableObject(CBaseExecutableObject *Object)
: CBaseBuildableObject(Object) {

  // Assign Our Variables
  pWorld               = CWorld::Instance();
  pBase                = 0;
  iWorldWidth          = -1;
  iWorldHeight         = -1;
}

//**********************************************************************
// void CBaseExecutableObject::validate()
// Validate
//**********************************************************************
void CBaseExecutableObject::validate() {
  try {
    // Assign
    iWorldWidth          = pWorld->getWidth();
    iWorldHeight         = pWorld->getHeight();

    // Validate
    if (sLabel == "")
      CError::errorMissing(PARAM_LABEL);

  } catch (string Ex) {
    Ex = "CBaseExecutableObject.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CBaseExecutableObject::~CBaseExecutableObject()
// Default De-Constructor
//**********************************************************************
CBaseExecutableObject::~CBaseExecutableObject() {
  // Clear Pts
  pBase  = 0;
}
