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

  vector<double> scores;
  vector<double> expected;
  vector<double> observed;
  vector<double> errorValue;
  vector<double> processError;
  double delta = 1e-05;

  // Test case 1
  expected.push_back(0.1);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 2
  expected.push_back(0.2);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 3
  expected.push_back(0.3);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 4
  expected.push_back(0.4);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 5
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 6
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(10);
  // Test case 7
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(15);

  // run the likelihood
  pLikelihood->getResult(scores, expected, observed, errorValue, processError, delta);
  delete pLikelihood;

  // Check results
  BOOST_CHECK_CLOSE(16.300417207752272, scores[0], 1e-9);
  BOOST_CHECK_CLOSE(12.834681304952547, scores[1], 1e-9);
  BOOST_CHECK_CLOSE(10.807355764411724, scores[2], 1e-9);
  BOOST_CHECK_CLOSE( 9.368945402152817, scores[3], 1e-9);
  BOOST_CHECK_CLOSE( 8.253227645581770, scores[4], 1e-9);
  BOOST_CHECK_CLOSE( 0.516444725003769, scores[5], 1e-9);
  BOOST_CHECK_CLOSE( 0.872226985105489, scores[6], 1e-9);
}

#endif /* TEST */
