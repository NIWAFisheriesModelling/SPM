//============================================================================
// Name        : CLogNormalPrior.Test.cpp
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

// Local Includes
#include "../Factory/CPriorFactory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( LogNormalPrior ) {
  // Get prior
  CPrior *pPrior = CPriorFactory::buildPrior(PARAM_LOGNORMAL, false);

  // Add parameters
  pPrior->addParameter(PARAM_LABEL, "prior");
  pPrior->addParameter(PARAM_MU, "3");
  pPrior->addParameter(PARAM_CV, "5");

  // Validate and build
  pPrior->validate();

  // Check results
  BOOST_CHECK_EQUAL(pPrior->getResult(1.0), 0.043178942974616268);
  BOOST_CHECK_EQUAL(pPrior->getResult(2.0), 0.92290644861305016);
  BOOST_CHECK_EQUAL(pPrior->getResult(3.0), 1.505874355920795);
  BOOST_CHECK_EQUAL(pPrior->getResult(4.0), 1.9500982814472527);
  BOOST_CHECK_EQUAL(pPrior->getResult(5.0), 2.3121580779587432);
  BOOST_CHECK_EQUAL(pPrior->getResult(6.0), 2.6193272903585973);
  BOOST_CHECK_EQUAL(pPrior->getResult(7.0), 2.8869949329193436);
  BOOST_CHECK_EQUAL(pPrior->getResult(8.0), 3.1247544414772239);
  BOOST_CHECK_EQUAL(pPrior->getResult(9.0), 3.3390158089789455);

  // clear memory
  delete pPrior;
}
#endif /* TEST */
