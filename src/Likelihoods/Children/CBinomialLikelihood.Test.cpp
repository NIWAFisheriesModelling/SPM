//============================================================================
// Name        : CBinomialLikelihood.Test.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CLikelihoodFactory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( BinomialLikelihood ) {
  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_BY_CATEGORY, PARAM_BINOMIAL);


  // Check results
  BOOST_CHECK_EQUAL(pLikelihood->getResult(0.97524381095273815, 0.1, 0.01,0.0, 1e-11), -0.016652905166183531);

  // clear memory
  delete pLikelihood;
}

#endif /* TEST */
