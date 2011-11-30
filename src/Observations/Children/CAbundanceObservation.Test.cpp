//============================================================================
// Name        : CAbundanceObservation.Test.cpp
// Author      : S.Rasmussen
// Date        : 27/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C3x3_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/AnnualMortalityRate.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/CategoryTransitionRate.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/LogisticProducing.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/Catchabilities/Catchability.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/StringLayer.h"
#include "../../TestFixtures/ConfigurationFiles/Observations/Abundance.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AbundanceObservation, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(abundance_observation);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  loadAndRunEnvironment();

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("abundance_observation");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 6.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.10, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 60.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 59.291539712786701, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, -2.2908024985886413, 1e-9);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.12, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 40.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 39.527693141857796, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, -2.1111820056961705, 1e-9);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.13, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 19.763846570928898, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, -2.0321732640789509, 1e-9);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaD");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.14, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 19.763846570928898, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, -1.9589737634997755, 1e-9);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaE");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.15, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 19.763846570928898, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, -1.890802286836925, 1e-9);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaF");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.16, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 19.763846570928898, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, -1.8270248374769187, 1e-9);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare *pSquare = getSquare(i,j);

      BOOST_CHECK_CLOSE(pSquare->getAbundance(), 19763.846570928898, 1e-9);

      // Our Expected Results
      double immature[] = { 111.11111111111111, 333.33333333333337, 666.66666666666674, 777.77777777777783, 1083.3333333333333,
          1041.6266318250709, 952.85900493878341, 803.91670313042891, 621.10466653061906, 1518.4297407260515 };

      double mature[] = { 0.0, 0.0, 0.0, 0.0, 27.5,
          69.781961007658808, 157.59186523354549, 313.00101286529247, 527.78262501541349, 10758.030137433811 };

      double spawning[] = { 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0 };

      // Check Expected against model
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
    }
  }
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AbundanceObservation_Simulation, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(abundance_observation_simulate);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  loadAndRunEnvironment("-s");

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("abundance_observation_simulate");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 6.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.10, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 56.344205271053205, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 59.291539712786701, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 0.0, 1e-9);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.12, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 43.585975219738799, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 39.527693141857796, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 0.0, 1e-9);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.13, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 18.992451438215792, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 19.763846570928898, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 0.0, 1e-9);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaD");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.14, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.150042264798603, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 19.763846570928898, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 0.0, 1e-9);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaE");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.15, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 15.217887307033308, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 19.763846570928898, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 0.0, 1e-9);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaF");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.16, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 27.559873204605019, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 19.763846570928898, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 0.0, 1e-9);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare *pSquare = getSquare(i,j);

      BOOST_CHECK_CLOSE(pSquare->getAbundance(), 19763.846570928898, 1e-9);

      // Our Expected Results
      double immature[] = { 111.11111111111111, 333.33333333333337, 666.66666666666674, 777.77777777777783, 1083.3333333333333,
          1041.6266318250709, 952.85900493878341, 803.91670313042891, 621.10466653061906, 1518.4297407260515 };

      double mature[] = { 0.0, 0.0, 0.0, 0.0, 27.5,
          69.781961007658808, 157.59186523354549, 313.00101286529247, 527.78262501541349, 10758.030137433811 };

      double spawning[] = { 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0 };

      // Check Expected against model
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
    }
  }
}

#endif /* TEST */
