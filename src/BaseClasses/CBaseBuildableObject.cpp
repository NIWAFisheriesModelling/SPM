//============================================================================
// Name        : CBaseBuildableObject.cpp
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CBaseBuildableObject.h"

//**********************************************************************
// CBaseBuildableObject::CBaseBuildableObject()
// Default Constructor
//**********************************************************************
CBaseBuildableObject::CBaseBuildableObject(CBaseBuildableObject *Object)
: CBaseObject(Object) {
}

//**********************************************************************
// void CBaseBuildableObject::rebuild()
//
//**********************************************************************
void CBaseBuildableObject::rebuild() { }

//**********************************************************************
// CBaseBuildableObject::~CBaseBuildableObject()
// Default De-Constructor
//**********************************************************************
CBaseBuildableObject::~CBaseBuildableObject() {
}
