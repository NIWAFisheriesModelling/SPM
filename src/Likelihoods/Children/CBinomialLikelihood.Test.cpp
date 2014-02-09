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

  vector<double> scores;
  vector<double> expected;
  vector<double> observed;
  vector<double> errorValue;
  vector<double> processError;
  vector<double> delta;

  /**
   * Test Case 1
   */
  expected.push_back(0.1);
  observed.push_back(0.2);
  errorValue.push_back(0.005);
  processError.push_back(0.1);
  delta.push_back(0.1);

  /**
   * Test Case 2
   */
  expected.push_back(0.1);
  observed.push_back(0.2);
  errorValue.push_back(0.005);
  processError.push_back(0.1);
  delta.push_back(0.1);

  /**
   * run the likelihood
   */
  pLikelihood->getResult(scores, expected, observed, errorValue, processError, delta);
  delete pLikelihood;

  /**
   * check results
   *
   */
  BOOST_CHECK_EQUAL(0.1, scores[0]); // Test Case 1
  BOOST_CHECK_EQUAL(0.1, scores[1]); // Test Case 2
}

#endif /* TEST */
