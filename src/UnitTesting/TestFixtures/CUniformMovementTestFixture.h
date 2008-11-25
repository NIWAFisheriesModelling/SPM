//============================================================================
// Name        : CUniformMovementTestFixture.h
// Author      : S.Rasmussen
// Date        : 18/07/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST
#ifndef CUNIFORMMOVEMENTTESTFIXTURE_H_
#define CUNIFORMMOVEMENTTESTFIXTURE_H_

// Local Headers
#include "CBaseTestFixture.h"

//**********************************************************************
//
//
//**********************************************************************
class CUniformMovementTestFixture: public CBaseTestFixture {
public:
  // Functions
  CUniformMovementTestFixture();
  virtual                    ~CUniformMovementTestFixture();
};

#endif /* CUNIFORMMOVEMENTTESTFIXTURE_H_ */
#endif /* UNITTEST */
