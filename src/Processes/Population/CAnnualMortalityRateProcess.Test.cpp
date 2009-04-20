//============================================================================
// Name        : CAnnualMortalityRateProcess.Test.cpp
// Author      : S.Rasmussen
// Date        : 21/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/AnnualMortalityRate.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/CategoryTransitionRate.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/LogisticProducing.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AnnualMortalityRateProcess, C1x1_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  loadAndRunEnvironment();

  // Check our Results
  CWorldSquare *pSquare = getSquare();

  BOOST_CHECK_EQUAL(pSquare->getPopulation(), 177874.61913836008);

  // Our Expected Results
  double immature[] = { 1000.0, 3000.0, 6000.0, 7000.0, 9750,
      9374.6396864256385, 8575.7310444490504, 7235.2503281738609, 5589.9419987755718, 13665.867666534466 };

  double mature[] = { 0.0, 0.0, 0.0, 0.0, 247.5,
      628.03764906892934, 1418.3267871019095, 2817.0091157876313, 4750.0436251387227, 96822.271236904286 };

  double spawning[] = { 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 };

  // Check Expected against model
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 0), immature[0]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 1), immature[1]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 2), immature[2]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 3), immature[3]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 4), immature[4]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 5), immature[5]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 6), immature[6]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 7), immature[7]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 8), immature[8]);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 9), immature[9]);

  BOOST_CHECK_EQUAL(pSquare->getValue(1, 0), mature[0]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 1), mature[1]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 2), mature[2]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 3), mature[3]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 4), mature[4]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 5), mature[5]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 6), mature[6]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 7), mature[7]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 8), mature[8]);
  BOOST_CHECK_EQUAL(pSquare->getValue(1, 9), mature[9]);

  BOOST_CHECK_EQUAL(pSquare->getValue(2, 0), spawning[0]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 1), spawning[1]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 2), spawning[2]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 3), spawning[3]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 4), spawning[4]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 5), spawning[5]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 6), spawning[6]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 7), spawning[7]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 8), spawning[8]);
  BOOST_CHECK_EQUAL(pSquare->getValue(2, 9), spawning[9]);
}

#endif
