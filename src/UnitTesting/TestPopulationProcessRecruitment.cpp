  //============================================================================
// Name        : TestPopulationProcessRecruitment.cpp
// Author      : S.Rasmussen
// Date        : 13/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Includes
#include "TestFixtures/CRecruitmentTestFixture.h"
#include "../Processes/Population/CRecruitmentProcess.h"

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_Basic, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Missing label
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_GoodLabel, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Missing Categories
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_GoodCategory, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Missing Proportions
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_NotCompleteProportions, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Missing Ages
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_GoodAges, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Missing R0
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_GoodR0, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Missing Method
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_GoodMethod, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Proportions Must = 1.0
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_GoodProportion, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_MultipleProportions, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Category Vector, Not Match Prop Vector
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_MultipleProportionsWithCategories, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Categories vector does not match ages vector
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_MultipleAgesWithCategories, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_BadMethod, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("some_not_real_method"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Unknown Method
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_LayerCategory, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addLayerCategory("double_layer"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Multiple layers not supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_Selectivity, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Selectivities not supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Validate_Penalty, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setPenalty("penalty"));
  BOOST_REQUIRE_THROW(clRecruitment.validate(), string); // Penalty not supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Build_Baisc, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clRecruitment.build(), string); // Validation has not being run yet
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Build_GoodLayer, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clRecruitment.build()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Build_BadLayer, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLayerName("some_not_real_layer"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
  BOOST_REQUIRE_THROW(clRecruitment.build(), string); // Unknown Layer
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Build_GoodCategory, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clRecruitment.build()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Build_BadCategory, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("some_not_real_category"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
  BOOST_REQUIRE_THROW(clRecruitment.build(), string); // Unknown Category
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Build_GoodAge, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(20));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clRecruitment.build()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Build_BadAgeTooHigh, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(21));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
  BOOST_REQUIRE_THROW(clRecruitment.build(), string); // Age too high
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Build_BadAgeTooLow, CRecruitmentTestFixture ) {
  // Var
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(-1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(50000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
  BOOST_REQUIRE_THROW(clRecruitment.build(), string); // Age too low
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RecruitmentProcess_Execute, CRecruitmentTestFixture ) {

  // Variables
  CWorldSquare         *pSquare    = 0;
  CConstantRecruitmentProcess  clRecruitment       = CConstantRecruitmentProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLabel("recruitment"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addCategory("immature"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addProportion(1.0));
  BOOST_REQUIRE_NO_THROW(clRecruitment.addAges(1));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setR0(90000));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setMethod("uniform"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.setLayerName("double_layer"));
  BOOST_REQUIRE_NO_THROW(clRecruitment.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clRecruitment.build()); // OK!

  BOOST_REQUIRE_NO_THROW(clRecruitment.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j) {
      BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(i, j));
      BOOST_REQUIRE_EQUAL(pSquare->getEnabled(), true);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 0), 0);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 0), 0);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 1), 10000);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 1), 0);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(spawningIndex, 1), 0);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(immatureIndex, 2), 0);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(matureIndex, 2), 0);
      BOOST_REQUIRE_EQUAL(pSquare->getValue(spawningIndex, 2), 0);
    }
}
#endif
