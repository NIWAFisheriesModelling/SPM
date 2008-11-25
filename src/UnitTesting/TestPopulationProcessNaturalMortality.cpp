//============================================================================
// Name        : CTestPopulationProcessNaturalMortality.cpp
// Author      : S.Rasmussen
// Date        : 6/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Includes
#include "TestFixtures/CNaturalMortalityTestFixture.h"
#include "../Processes/Population/CNaturalMortalityProcess.h"

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_Basic, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // No Label
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_GoodLabel, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Missing Categories
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_GoodCategory, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Missing M
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_GoodM, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Missing Selectivities
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_GoodSelectivities, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_DuplicateCategory, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Duplicate Category
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_MultipleCategory, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Category Size != Selectivity Size
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_MultipleSelectivity, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("knife_edge_selectivity"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Category Size != Selectivity Size
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Validate_BadPenalty, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.setPenalty("penalty"));
  BOOST_REQUIRE_THROW(clMortality.validate(), string); // Penalty Not Supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Build_Basic, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_THROW(clMortality.build(), string); // Validation has not been run.
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Build_GoodLayer, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Build_BadLayer, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.setLayerName("some_not_real_layer"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_THROW(clMortality.build(), string); // Unknown Layer
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Build_GoodSelectivity, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Build_BadSelectivity, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("some_not_real_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_THROW(clMortality.build(), string); // Unknown Selectivity
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Build_GoodCategory, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clMortality.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Build_BadCategory, CNaturalMortalityTestFixture ) {
  // Var
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("some_not_real_category"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clMortality.validate()); // Ok!
  BOOST_REQUIRE_THROW(clMortality.build(), string); // Unknown Category
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NaturalMortalityProcess_Execute, CNaturalMortalityTestFixture ) {
  // Variables
  CWorldSquare              *pSquare    = 0;
  CNaturalMortalityProcess  clMortality       = CNaturalMortalityProcess();

  BOOST_REQUIRE_NO_THROW(clMortality.setLabel("natural_mortality"));
  BOOST_REQUIRE_NO_THROW(clMortality.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMortality.setM(0.065));
  BOOST_REQUIRE_NO_THROW(clMortality.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMortality.setLayerName("double_layer"));
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
      BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 0), 93.706746337740341);
    }
}

#endif
