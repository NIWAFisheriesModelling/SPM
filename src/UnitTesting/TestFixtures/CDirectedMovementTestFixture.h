//============================================================================
// Name        : CDirectedMovementTestFixture.h
// Author      : S.Rasmussen
// Date        : 21/07/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST
#ifndef CDIRECTEDMOVEMENTTESTFIXTURE_H_
#define CDIRECTEDMOVEMENTTESTFIXTURE_H_

// Local headers
#include "CBaseTestFixture.h"

//**********************************************************************
//
//
//**********************************************************************
class CDirectedMovementTestFixture : public CBaseTestFixture {
public:
  // Functions
  CDirectedMovementTestFixture();
  virtual                     ~CDirectedMovementTestFixture();
};

#endif /* CDIRECTEDMOVEMENTTESTFIXTURE_H_ */
#endif /* UNITTEST */
