//============================================================================
// Name        : CBetaPrior.Test.cpp
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
BOOST_AUTO_TEST_CASE( BetaPrior ) {
  // Get prior
  CPrior *pPrior = CPriorFactory::buildPrior(PARAM_BETA, false);

  // Add parameters
  pPrior->addParameter(PARAM_LABEL, "prior");
  pPrior->addParameter(PARAM_MU, "5");
  pPrior->addParameter(PARAM_SIGMA, "8");
  pPrior->addParameter(PARAM_A, "0.1");
  pPrior->addParameter(PARAM_B, "0.009");

  // Validate and build
  pPrior->validate();

  // Check results
  // TODO: Add good parameters so we can finish unit tests
//  BOOST_CHECK_EQUAL(pPrior->getResult(1.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(2.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(3.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(4.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(5.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(6.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(7.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(8.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(9.0), 0.0);

  // clear memory
  delete pPrior;
}

#endif /* TEST */
