//============================================================================
// Name        : CBaseExecutableObject.h
// Author      : S.Rasmussen
// Date        : 31/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : This class is a base executable object. Objects that need
//              To have a Validate, Build, Execute need to inherit from this.
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBASEEXECUTABLEOBJECT_H_
#define CBASEEXECUTABLEOBJECT_H_

// Local Headers
#include "CBaseBuildableObject.h"
#include "../CWorld.h"
#include "../WorldSquares/CWorldSquare.h"

//**********************************************************************
//
//
//**********************************************************************
class CBaseExecutableObject : public CBaseBuildableObject {
public:
  // Functions
  CBaseExecutableObject(CBaseExecutableObject *Object = 0);
  virtual ~CBaseExecutableObject();
  virtual void               validate();
  virtual void               build() = 0;
  virtual void               execute() = 0;

protected:
  // Functions
  string                     convertDouble(double value);
  double                     lnGamma(double t);
  double                     lnFactorial(double t);
  double                     zeroFun(double x, double delta);

	// Variables
  CWorld                     *pWorld;
  CWorldSquare               *pBase;
	int                        iWorldWidth;
	int                        iWorldHeight;
	bool                       bVerbose;
};

#endif /*CBASEEXECUTABLEOBJECT_H_*/
