  //============================================================================
// Name        : TestPopulationProcessAgeing.cpp
// Author      : S.Rasmussen
// Date        : 3/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Includes
#include "TestFixtures/CAgeingTestFixture.h"
#include "../Processes/Population/CAgeingProcess.h"

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Validate_Basic, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clAge.validate(), string); // No Label
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Validate_GoodLabel, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_THROW(clAge.validate(), string); // No Categories
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Validate_GoodCategory, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();
  // Add Categories
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("immature"));
  BOOST_REQUIRE_NO_THROW(clAge.validate()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Validate_DuplicateCategory, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();
  // Add Categories
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("mature"));
  BOOST_REQUIRE_THROW(clAge.validate(), string); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Validate_Layer, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();
  // Add Layer Name
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clAge.setLayerName("some_not_real_Layer"));
  BOOST_REQUIRE_THROW(clAge.validate(), string); // Layer Not Implemented
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Validate_Penalty, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();
  // Clear Layer, Add Penalty
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clAge.setPenalty("penalty"));
  BOOST_REQUIRE_THROW(clAge.validate(), string); // Penalty not supported
}

//**********************************************************************
//**********************************************************************
  BOOST_FIXTURE_TEST_CASE( AgeingProcess_Validate_Selectivity, CAgeingTestFixture ) {
  // Try Selectivities
  CAgeingProcess clAge = CAgeingProcess();
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clAge.addSelectivity("constant"));
  BOOST_REQUIRE_THROW(clAge.validate(), string); // Selectivity Not Supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Build_Basic, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();

  // Add Enuff To Make it Validate
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_THROW(clAge.build(), string); // Validation Not Run
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Build_GoodCategory, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();

  // Add Enuff To Make it Validate
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clAge.validate()); // Ok!
  BOOST_REQUIRE_NO_THROW(clAge.build()); // Ok!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Build_BadCategory, CAgeingTestFixture ) {
  // Var
  CAgeingProcess  clAge       = CAgeingProcess();

  // Add Enuff To Make it Validate
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("ageing"));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("some_not_real_category"));
  BOOST_REQUIRE_NO_THROW(clAge.validate()); // Ok!
  BOOST_REQUIRE_THROW(clAge.build(), string); // Invalid Category
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AgeingProcess_Execute, CAgeingTestFixture ) {

  // Variables
  CWorldSquare    *pSquare        = 0;
  CAgeingProcess  clAge           = CAgeingProcess();

  BOOST_REQUIRE_NO_THROW(clAge.setDependsOnLayer(false));
  BOOST_REQUIRE_NO_THROW(clAge.setLabel("Age_Test"));
  BOOST_REQUIRE_NO_THROW(clAge.setLayerMax(0));
  BOOST_REQUIRE_NO_THROW(clAge.setLayerMin(0));
  BOOST_REQUIRE_NO_THROW(clAge.addCategory("mature"));

  BOOST_REQUIRE_NO_THROW(clAge.validate());
  BOOST_REQUIRE_NO_THROW(clAge.build());

  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_REQUIRE_EQUAL(pSquare->getEnabled(), true);

  BOOST_REQUIRE_NO_THROW(immatureIndex = pConfig->getCategoryIndexForName("immature"));
  BOOST_REQUIRE_NO_THROW(matureIndex = pConfig->getCategoryIndexForName("mature"));
  BOOST_REQUIRE_NO_THROW(spawningIndex = pConfig->getCategoryIndexForName("spawning"));

  BOOST_REQUIRE_NO_THROW(pSquare->addValue(matureIndex, 0, 100)); // Add 100 Fish @ Age 1;

  // Execute and Validate
  for (int i = 0; i < 10; ++i) {
    BOOST_REQUIRE_NO_THROW(clAge.execute());
    BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

    BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, i), 0);
    BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, i+1), 100);
    BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, i+2), 0);

    BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, i), 0);
    BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, i+1), 0);
    BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, i+2), 0);

    BOOST_REQUIRE_EQUAL(pSquare->getValue(spawningIndex, i), 0);
    BOOST_REQUIRE_EQUAL(pSquare->getValue(spawningIndex, i+1), 0);
    BOOST_REQUIRE_EQUAL(pSquare->getValue(spawningIndex, i+2), 0);
  }
}

#endif
