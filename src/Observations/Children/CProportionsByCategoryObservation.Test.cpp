//============================================================================
// Name        : CProportionsByCategoryObservation.Test.cpp
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
#include "../../TestFixtures/ConfigurationFiles/Observations/ProportionsByCategory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ProportionsByCategoryObservation, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_by_category_observation);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment());

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("proportions_by_category_observation");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 18.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1000);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.1);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.97524381095273815);
  BOOST_CHECK_EQUAL(pComparison->dScore, 3009.4052730807521);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1100);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.2);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.93721304526735716);
  BOOST_CHECK_EQUAL(pComparison->dScore, 1903.1747357951806);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.7);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.24892230690790682);
  BOOST_CHECK_EQUAL(pComparison->dScore, 541.81151594366395);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.20);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.97524381095273815);
  BOOST_CHECK_EQUAL(pComparison->dScore, 2959.8139773353869);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1300);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.30);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.93721304526735727);
  BOOST_CHECK_EQUAL(pComparison->dScore, 1753.7769759814867);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1400);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.5);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.24892230690790684);
  BOOST_CHECK_EQUAL(pComparison->dScore, 207.24447285897321);

  pComparison = vComparisons[6];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1300);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.30);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.97524381095273815);
  BOOST_CHECK_EQUAL(pComparison->dScore, 2585.1753362597537);

  pComparison = vComparisons[7];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1400);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.40);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.93721304526735727);
  BOOST_CHECK_EQUAL(pComparison->dScore, 1423.0510360841777);

  pComparison = vComparisons[8];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1500);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.30);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.24892230690790684);
  BOOST_CHECK_EQUAL(pComparison->dScore, 13.833972712752306);

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
BOOST_FIXTURE_TEST_CASE( ProportionsByCategoryObservation_Simulate, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_by_category_observation);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment("-s"));

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("proportions_by_category_observation");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 18.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1000);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.97899999999999998);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.97524381095273815);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1100);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.93545454545454543);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.93721304526735716);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areaa");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.24166666666666667);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.24892230690790682);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 1200);
  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.97583333333333333);
  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.97524381095273815);
  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

//  pComparison = vComparisons[4];
//  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
//  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 0.021);
//  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.93721304526735727);
//  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.93721304526735727);
//  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);
//
//  pComparison = vComparisons[5];
//  BOOST_CHECK_EQUAL(pComparison->sKey, "areab");
//  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 0.022);
//  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.24892230690790684);
//  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.24892230690790684);
//  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);
//
//  pComparison = vComparisons[6];
//  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
//  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 0.03);
//  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.97524381095273815);
//  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.97524381095273815);
//  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);
//
//  pComparison = vComparisons[7];
//  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
//  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 0.031);
//  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.93721304526735727);
//  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.93721304526735727);
//  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);
//
//  pComparison = vComparisons[8];
//  BOOST_CHECK_EQUAL(pComparison->sKey, "areac");
//  BOOST_CHECK_EQUAL(pComparison->dErrorValue, 0.032);
//  BOOST_CHECK_EQUAL(pComparison->dObservedValue, 0.24892230690790684);
//  BOOST_CHECK_EQUAL(pComparison->dExpectedValue, 0.24892230690790684);
//  BOOST_CHECK_EQUAL(pComparison->dScore, 0.0);

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
