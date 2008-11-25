//============================================================================
// Name        : CTestPopulationProcessEventMortality.cpp
// Author      : S.Rasmussen
// Date        : 4/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Includes
#include "TestFixtures/CEventMortalityTestFixture.h"
#include "../Processes/Population/CEventMortalityProcess.h"

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Set_BadYear, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clMortality.addYears(1950), string); // Invalid year
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_Basic, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // No Label
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_GoodLabel, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Missing Layers
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_GoodUMax, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Missing Layers
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_GoodLayers, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Missing Years
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_GoodYears, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Missing Selectivities
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_TooManyYears, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2001));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Number of Years != Nu. Layers
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_GoodSelectvity, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Nu. Categories != Nu. Selectivities
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_GoodCategory, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate());
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_DuplicateCategory, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Validate_BadLayer, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setLayerName("double_layer"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_Basic, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  BOOST_REQUIRE_THROW(clMortality.build(), string); // Not Validated
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_GoodLayer, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_BadLayer, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("some_not_real_layer"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_THROW(clMortality.build(), string); // Unknown Layer
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_GoodSelectivity, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_BadSelectivity, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("some_not_real_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_THROW(clMortality.build(), string); // Unknown Selectivity
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_GoodCategory, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_BadCategory, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("some_not_real_category"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_THROW(clMortality.build(), string); // Unknown Category
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_GoodPenalty, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setPenalty("penalty"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortalityProcess_Build_BadPenalty, CEventMortalityTestFixture ) {
  // Var
  CEventMortalityProcess  clMortality       = CEventMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(100.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(2000));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setPenalty("some_not_real_penalty"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_THROW(clMortality.build(), string); // Unknown Penalty
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortality_Execute_ConstantSelectivity, CEventMortalityTestFixture ) {
  // Variables
  CWorldSquare            *pSquare      = 0;
  CEventMortalityProcess  clMortality   = CEventMortalityProcess();

  BOOST_REQUIRE_NO_THROW(pRuntime->setCurrentYear(0));
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(10.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(1990));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!

  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j) {
      BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(i, j));
      BOOST_REQUIRE_EQUAL(pSquare->getEnabled(), true);
      BOOST_REQUIRE_NO_THROW(pSquare->addValue(immatureIndex, 0, 100));
      BOOST_REQUIRE_NO_THROW(pSquare->addValue(matureIndex, 0, 100));
    }

  BOOST_REQUIRE_NO_THROW(clMortality.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j) {
      BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(i, j));
      BOOST_REQUIRE_EQUAL(pSquare->getEnabled(), true);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 0), 100);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 0), (i+j));
    }
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( EventMortality_Execute_DoubleNormalSelectivity, CEventMortalityTestFixture ) {
  // Variables
  CWorldSquare            *pSquare      = 0;
  CEventMortalityProcess  clMortality   = CEventMortalityProcess();

  BOOST_REQUIRE_NO_THROW(pRuntime->setCurrentYear(0));
  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("event_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.setUMax(10.0));
  BOOST_REQUIRE_NO_THROW(clMortality.addLayers("double_layer_2000"));
  BOOST_REQUIRE_NO_THROW(clMortality.addYears(1990));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("double_normal_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!

  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j) {
      BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(i, j));
      BOOST_REQUIRE_EQUAL(pSquare->getEnabled(), true);
      BOOST_REQUIRE_NO_THROW(pSquare->addValue(immatureIndex, 0, 100));
      BOOST_REQUIRE_NO_THROW(pSquare->addValue(matureIndex, 0, 100));
    }

  BOOST_REQUIRE_NO_THROW(clMortality.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j) {
      BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(i, j));
      BOOST_REQUIRE_EQUAL(pSquare->getEnabled(), true);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 0), 100);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 0), 98.046875);
    }
}

#endif // UNITTEST
