//============================================================================
// Name        : CLogNormalLikelihood.Test.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CLikelihoodFactory.h"
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(LogNormalWithQLikelihood ) {
  CRandomNumberGenerator::Instance()->Reset(31373u);

  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_BIOMASS, PARAM_LOGNORMAL);

  // Generate data
  vector<string> keys;
  vector<double> scores;
  vector<double> observed;
  vector<double> expected;
  vector<double> errorValue;
  vector<double> processError;
  double delta = 1e-05;

  for (int i = 0; i < 4; ++i) {
    keys.push_back("A");
    observed.push_back(0.25);
    expected.push_back(0.25);
    errorValue.push_back(0.0001);
    processError.push_back(0);
  }
  for (int i = 0; i < 4; ++i) {
    keys.push_back("B");
    observed.push_back(0.25);
    expected.push_back(0.25);
    errorValue.push_back(0.50);
    processError.push_back(0);
  }

  // run the likelihood
  pLikelihood->getResult(scores, expected, observed, errorValue, processError, delta);

  // Check results
  BOOST_CHECK_CLOSE(-9.2103403762649183, scores[0], 1e-9);
  BOOST_CHECK_CLOSE(-9.2103403762649183, scores[1], 1e-9);
  BOOST_CHECK_CLOSE(-9.2103403762649183, scores[2], 1e-9);
  BOOST_CHECK_CLOSE(-9.2103403762649183, scores[3], 1e-9);
  BOOST_CHECK_CLOSE(-0.7220770494654815, scores[4], 1e-9);
  BOOST_CHECK_CLOSE(-0.7220770494654815, scores[5], 1e-9);
  BOOST_CHECK_CLOSE(-0.7220770494654815, scores[6], 1e-9);

  // Get results
  pLikelihood->simulateObserved(keys, observed, expected, errorValue, processError, delta);

  // Check results
  BOOST_CHECK_CLOSE(observed[0], 0.24999766961330266, 1e-9);
  BOOST_CHECK_CLOSE(observed[1], 0.25006064988144566, 1e-9);
  BOOST_CHECK_CLOSE(observed[2], 0.24997236788346203, 1e-9);
  BOOST_CHECK_CLOSE(observed[3], 0.24996931262178954, 1e-9);
  BOOST_CHECK_CLOSE(observed[4], 0.08611631029079405, 1e-9);
  BOOST_CHECK_CLOSE(observed[5], 0.20207465671160255, 1e-9);
  BOOST_CHECK_CLOSE(observed[6], 0.20525088157834170, 1e-9);
  BOOST_CHECK_CLOSE(observed[7], 0.50655815141926175, 1e-9);

  // clear memory
  delete pLikelihood;
}

#endif /* TEST */
