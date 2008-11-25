//============================================================================
// Name        : CEventMortalityTestFixture.h
// Author      : S.Rasmussen
// Date        : 4/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST
#ifndef CEVENTMORTALITYTESTFIXTURE_H_
#define CEVENTMORTALITYTESTFIXTURE_H_

// Local Headers
#include "CBaseTestFixture.h"

//**********************************************************************
//
//
//**********************************************************************
class CEventMortalityTestFixture: public CBaseTestFixture {
public:
  // Functions
  CEventMortalityTestFixture();
  virtual                    ~CEventMortalityTestFixture();

protected:
  // Functions
  void                       setupCustomLayers();
};

#endif /* CEVENTMORTALITYTESTFIXTURE_H_ */
#endif // UNITTEST
