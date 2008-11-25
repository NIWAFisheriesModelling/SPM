//============================================================================
// Name        : CBaseBuildableObject.h
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBASEBUILDABLEOBJECT_H_
#define CBASEBUILDABLEOBJECT_H_

// Local Headers
#include "CBaseObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CBaseBuildableObject : public CBaseObject {
public:
  // Functions
	CBaseBuildableObject(CBaseBuildableObject *Object = 0);
	virtual                    ~CBaseBuildableObject();
  virtual void               validate() = 0;
  virtual void               build() = 0;
  virtual void               rebuild();
};

#endif /*CBASEBUILDABLEOBJECT_H_*/
