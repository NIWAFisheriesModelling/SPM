//============================================================================
// Name        : TestPopulationProcessCategoryTransition.cpp
// Author      : S.Rasmussen
// Date        : 4/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Includes
#include "TestFixtures/CCategoryTransitionTestFixture.h"
#include "../Processes/Population/CCategoryTransitionProcess.h"

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_Basic, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // No Label
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_GoodLabel, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // No From
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_GoodFrom, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // No To
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_GoodTo, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // No Proportion
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_GoodProportion, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // No Selectivity
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_BadProportion, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(1.2));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // Proportion is > 1.0
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_GoodSelectivity, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant"));
  BOOST_REQUIRE_NO_THROW(clCategory.validate()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_DuplicateSelectivity, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant"));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // Must Have 1 Selectivity
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_MultipleSelectivity, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant"));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("knige_edge"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // Must have 1 Selectivity
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_Layer, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant"));
  BOOST_REQUIRE_NO_THROW(clCategory.setLayerName("some_not_real_layer"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // Layer Not Supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_Category, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant"));
  BOOST_REQUIRE_NO_THROW(clCategory.addCategory("mature"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // Category Not Supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Validate_Penalty, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant"));
  BOOST_REQUIRE_NO_THROW(clCategory.setPenalty("penalty"));
  BOOST_REQUIRE_THROW(clCategory.validate(), string); // Penalty Not Supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Build_Basic, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_THROW(clCategory.build(), string); // Validation not run
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Build_GoodFrom, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clCategory.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clCategory.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Build_BadFrom, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("some_not_real_category"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clCategory.validate()); // Ok!
  BOOST_REQUIRE_THROW(clCategory.build(), string); // Unknown Category (From)
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Build_GoodTo, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clCategory.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clCategory.build()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Build_BadTo, CCategoryTransitionTestFixture ) {
  // Var
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category_transition"));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("mature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("some_not_real_category"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clCategory.validate()); // Ok!
  BOOST_REQUIRE_THROW(clCategory.build(), string); // Unknown Category (To)
}

//**********************************************************************
// BOOST_FIXTURE_TEST_CASE( CategoryTransition, CTestFixture )
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( CategoryProcess_Build_Execute, CCategoryTransitionTestFixture ) {
  // Variables
  CWorldSquare                *pSquare    = 0;
  CCategoryTransitionProcess  clCategory  = CCategoryTransitionProcess();

  BOOST_REQUIRE_NO_THROW(clCategory.setLabel("category"));
  BOOST_REQUIRE_NO_THROW(clCategory.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clCategory.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clCategory.setFrom("immature"));
  BOOST_REQUIRE_NO_THROW(clCategory.setTo("mature"));

  BOOST_REQUIRE_NO_THROW(clCategory.validate());
  BOOST_REQUIRE_NO_THROW(clCategory.build());

  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_REQUIRE_EQUAL(pSquare->getEnabled(), true);

  // Add Some Fish
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(immatureIndex, 0, 100));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(immatureIndex, 1, 50));

  // Execute and Validate
  BOOST_REQUIRE_NO_THROW(clCategory.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());
  BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 0), 50);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 0), 50);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 1), 25);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 1), 25);

  BOOST_REQUIRE_NO_THROW(clCategory.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());
  BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 0), 25);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 0), 75);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 1), 12.5);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 1), 37.5);

  BOOST_REQUIRE_NO_THROW(clCategory.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());
  BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 0), 12.5);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 0), 87.5);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 1), 6.25);
  BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 1), 43.75);
}

#endif // UNITTEST
