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
  BOOST_CHECK_CLOSE( 1.687807099701715, scores[0], 1e-9);
  BOOST_CHECK_CLOSE( 3.522307801439243, scores[1], 1e-9);
  BOOST_CHECK_CLOSE( 7.503894929001944, scores[2], 1e-9);
  BOOST_CHECK_CLOSE(13.002265158969662, scores[3], 1e-9);
  BOOST_CHECK_CLOSE(20.091017458126572, scores[4], 1e-9);
  BOOST_CHECK_CLOSE( 3.939720847325895, scores[5], 1e-9);
  BOOST_CHECK_CLOSE( 5.256187812442846, scores[6], 1e-9);
}

#endif /* TEST */
