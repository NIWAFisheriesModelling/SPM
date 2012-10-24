//============================================================================
// Name        : CDerivedLayerFactory.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Headers
#include "CDerivedLayerFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DerivedLayer) {

  CDerivedLayer *pBasic = 0;
  BOOST_REQUIRE_NO_THROW(pBasic = CDerivedLayerFactory::buildDerivedLayer(PARAM_ABUNDANCE, false));
  delete pBasic;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DerivedLayer_PARAM_INVALID) {
  // Try to Build Invalid Estimate
  BOOST_REQUIRE_THROW(CDerivedLayerFactory::buildDerivedLayer(PARAM_ZERO, false), string);
}

#endif
