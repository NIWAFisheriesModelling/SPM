//============================================================================
// Name        : CAgeingTestFixture.h
// Author      : S.Rasmussen
// Date        : 30/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST
#ifndef CAGEINGTESTFIXTURE_H_
#define CAGEINGTESTFIXTURE_H_

// Local Includes
#include "CBaseTestFixture.h"

//**********************************************************************
//
//
//**********************************************************************
class CAgeingTestFixture : public CBaseTestFixture {
public:
  // Functions
  CAgeingTestFixture();
  virtual                    ~CAgeingTestFixture();
};

#endif /* CAGEINGTESTFIXTURE_H_ */
#endif // UNITTEST
