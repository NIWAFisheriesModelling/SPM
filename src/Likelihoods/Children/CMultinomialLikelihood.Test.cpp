//============================================================================
// Name        : CMultinomialLikelihood.Test.cpp
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
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
BOOST_AUTO_TEST_CASE( MultinomialLikelihood ) {
  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_AT_AGE, PARAM_MULTINOMIAL);


  // Check results
  //BOOST_CHECK_EQUAL(pLikelihood->getResult(0.97524381095273815, 0.1, 0.01,0.0, 1e-11), 0.033298488461815871);

  // clear memory
  delete pLikelihood;
}

#endif /* TEST */
