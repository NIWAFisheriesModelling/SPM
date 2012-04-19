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
  pPrior->addParameter(PARAM_SIGMA, "1");
  pPrior->addParameter(PARAM_A, "0");
  pPrior->addParameter(PARAM_B, "10");

  // Validate and build
  pPrior->validate();

  // Check results
  BOOST_CHECK_CLOSE(pPrior->getResult(1.0), -24.169470350698415, 1e-9);
  BOOST_CHECK_CLOSE(pPrior->getResult(2.0), -30.498475944637590, 1e-9);
  BOOST_CHECK_CLOSE(pPrior->getResult(3.0), -33.489746814957655, 1e-9);
  BOOST_CHECK_CLOSE(pPrior->getResult(4.0), -34.958592133827402, 1e-9);
  BOOST_CHECK_CLOSE(pPrior->getResult(5.0), -35.407634073550206, 1e-9);
  BOOST_CHECK_CLOSE(pPrior->getResult(6.0), -34.958592133827402, 1e-9);
  BOOST_CHECK_CLOSE(pPrior->getResult(7.0), -33.489746814957655, 1e-9);
  BOOST_CHECK_CLOSE(pPrior->getResult(8.0), -30.498475944637590, 1e-9);
  BOOST_CHECK_CLOSE(pPrior->getResult(9.0), -24.169470350698415, 1e-9);

  // clear memory
  delete pPrior;
}

#endif /* TEST */
