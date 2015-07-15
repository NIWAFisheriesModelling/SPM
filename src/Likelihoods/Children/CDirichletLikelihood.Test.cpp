//============================================================================
// Name        : CDirichletLikelihood.Test.cpp
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CLikelihoodFactory.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( DirichletLikelihood ) {
  CRandomNumberGenerator::Instance()->Reset(31373u);

  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_AT_AGE, PARAM_DIRICHLET);

  vector<string> keys;
  vector<double> scores;
  vector<double> expected;
  vector<double> observed;
  vector<double> errorValue;
  vector<double> processError;
  double delta = 1e-05;

  // Test case 1
  keys.push_back("A");
  expected.push_back(0.1);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 2
  keys.push_back("A");
  expected.push_back(0.2);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 3
  keys.push_back("A");
  expected.push_back(0.3);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 4
  keys.push_back("A");
  expected.push_back(0.4);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 5
  keys.push_back("B");
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 6
  keys.push_back("B");
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(10);
  // Test case 7
  keys.push_back("C");
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(15);

  BOOST_CHECK_CLOSE(0.0, pLikelihood->getInitialScore(keys, processError, errorValue), 1e-9);

  // run the likelihood
  pLikelihood->getResult(scores, expected, observed, errorValue, processError, delta);

  // Check results
  BOOST_CHECK_CLOSE(821.66416193412965,        scores[0], 1e-9);
  BOOST_CHECK_CLOSE(-6.8325073893337439e-313, scores[1], 1e-9);
  BOOST_CHECK_CLOSE(1.6662278630265568e-315, scores[2], 1e-9);
  BOOST_CHECK_CLOSE(-2.5500804644024056e-313, scores[3], 1e-9);
  BOOST_CHECK_CLOSE( 50.000000000000114,       scores[4], 1e-9);
  BOOST_CHECK_CLOSE(-2.5500804644518122e-313, scores[5], 1e-9);
  BOOST_CHECK_CLOSE(1.6662278383232745e-315, scores[6], 1e-9);

  // Get results
  pLikelihood->simulateObserved(keys, observed, expected, errorValue, processError, delta);

  // Check results
  BOOST_CHECK_CLOSE(observed[0], 0.06310697719429153, 1e-9);
  BOOST_CHECK_CLOSE(observed[1], 0.15200180984615036, 1e-9);
  BOOST_CHECK_CLOSE(observed[2], 0.47011274483757398, 1e-9);
  BOOST_CHECK_CLOSE(observed[3], 0.31477846812198418, 1e-9);
  BOOST_CHECK_CLOSE(observed[4], 0.08244145967451670, 1e-9);
  BOOST_CHECK_CLOSE(observed[5], 0.91755854032548334, 1e-9);
  BOOST_CHECK_CLOSE(observed[6], 1.00000000000000000, 1e-9);


  // clean up memory
  delete pLikelihood;

}

#endif /* TEST */
