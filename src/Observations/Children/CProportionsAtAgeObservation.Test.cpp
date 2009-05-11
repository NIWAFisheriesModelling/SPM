//============================================================================
// Name        : CProportionsAtAgeObservation.Test.cpp
// Author      : S.Rasmussen
// Date        : 28/04/2009
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
#include "../../TestFixtures/ConfigurationFiles/Observations/ProportionsAtAge.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ProportionsAtAgeObservation, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_at_age_observation);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment());

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("proportions_at_age_observation");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 18.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1000);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.1);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.06214466926819362);
  BOOST_CHECK_EQUAL(pComparison->dScore, 641.56839922930146);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1000);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.2);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.062176851694000113);
  BOOST_CHECK_EQUAL(pComparison->dScore, 1418.7864887457254);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1000);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.7);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.87567847903780627);
  BOOST_CHECK_EQUAL(pComparison->dScore, 3982.8802342154063);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.20);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.062144669268193627);
  BOOST_CHECK_EQUAL(pComparison->dScore, 1745.8026036358419);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.30);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.06217685169400012);
  BOOST_CHECK_EQUAL(pComparison->dScore, 2762.8577761482907);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.5);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.87567847903780638);
  BOOST_CHECK_EQUAL(pComparison->dScore, 3321.9291084679871);

  pComparison = vComparisons[6];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1300);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.30);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.062144669268193627);
  BOOST_CHECK_EQUAL(pComparison->dScore, 3024.2326461635048);

  pComparison = vComparisons[7];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1300);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.40);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.06217685169400012);
  BOOST_CHECK_EQUAL(pComparison->dScore, 4180.4786992530635);

  pComparison = vComparisons[8];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1300);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.30);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.87567847903780638);
  BOOST_CHECK_EQUAL(pComparison->dScore, 1992.4744063438211);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare *pSquare = getSquare(i,j);

      BOOST_CHECK_EQUAL(pSquare->getPopulation(), 19763.846570928898);

      // Our Expected Results
      double immature[] = { 111.11111111111111, 333.33333333333337, 666.66666666666674, 777.77777777777783, 1083.3333333333333,
          1041.6266318250709, 952.85900493878341, 803.91670313042891, 621.10466653061906, 1518.4297407260515 };

      double mature[] = { 0.0, 0.0, 0.0, 0.0, 27.5,
          69.781961007658808, 157.59186523354549, 313.00101286529247, 527.78262501541349, 10758.030137433811 };

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
  }
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ProportionsAtAgeObservation_Simulate, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_at_age_observation);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  loadAndRunEnvironment("-s");

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("proportions_at_age_observation");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 18.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1000);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.065000000000000002);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.06214466926819362);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1000);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.065000000000000002);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.062176851694000113);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1000);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.87);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.87567847903780627);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.055833333333333332);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.062144669268193627);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.066666666666666666);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.06217685169400012);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.87749999999999995);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.87567847903780638);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[6];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1300);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.062307692307692307);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.062144669268193627);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[7];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1300);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.061538461538461542);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.06217685169400012);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[8];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1300);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.87615384615384617);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.87567847903780638);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare *pSquare = getSquare(i,j);

      BOOST_CHECK_EQUAL(pSquare->getPopulation(), 19763.846570928898);

      // Our Expected Results
      double immature[] = { 111.11111111111111, 333.33333333333337, 666.66666666666674, 777.77777777777783, 1083.3333333333333,
          1041.6266318250709, 952.85900493878341, 803.91670313042891, 621.10466653061906, 1518.4297407260515 };

      double mature[] = { 0.0, 0.0, 0.0, 0.0, 27.5,
          69.781961007658808, 157.59186523354549, 313.00101286529247, 527.78262501541349, 10758.030137433811 };

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
  }
}
#endif /* TEST */
