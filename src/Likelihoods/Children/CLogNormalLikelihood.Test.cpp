//============================================================================
// Name        : CLogNormalLikelihood.Test.cpp
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
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(LogNormalLikelihood ) {
  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_AT_AGE, PARAM_LOGNORMAL);

  // Check results
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99947558889177623);
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99976020659670273);
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 1.0002227168955811);
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99848153407070017);
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99977680165763549);

  // clear memory
  delete pLikelihood;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( LogNormalLikelihood_1x1, C1x1_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment);
  addToTimeStep("ageing constant_recruitment");
  loadAndRunEnvironment();

  // Check our Results

  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_AT_AGE, PARAM_LOGNORMAL);

  // Check results
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99845193414953692);
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 1.0010263962677095);
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99947282571698015);
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99945174404156234);
//  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.9992072565815735);

  // clear memory
  delete pLikelihood;

  // Check Population
  CWorldSquare *pSquare = getSquare();

  BOOST_CHECK_EQUAL(pSquare->getPopulation(), 1500.0);

  // Immature only should've aged
  for (int i = 0; i < 9; ++i)
    BOOST_CHECK_EQUAL(pSquare->getValue(0, i), 100.0);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 9), 600.0);

  // No population should've been recruited here
  for (int i = 1; i < 3; ++i)
    for (int j = 0; j < 10; ++j)
      BOOST_CHECK_EQUAL(pSquare->getValue(i, j), 0.0);
}

#endif /* TEST */
