//============================================================================
// Name        : TestMovementProcessUniform.cpp
// Author      : S.Rasmussen
// Date        : 17/07/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Includes
#include "TestFixtures/CUniformMovementTestFixture.h"
#include "../Processes/Movement/CUniformMovementProcess.h"

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_Basic, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Missing label
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_GoodLabel, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Missing method
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_GoodMethod, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Missing proportion
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_BadMethod, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("some_bad_method_type"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Unknown Method
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_GoodProportion, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Missing Categories
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_BadProportion, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(1.1));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Invalid proportion
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_GoodCategories, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Missing Selectivities
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_GoodSelectivities, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_BadCategorySelectivityCount, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("mature"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Category != Size as Selectivity Vector
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_DuplicateCategories, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Duplicate Category
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_Layer, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.setLayerName("some_not_real_layer"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // layer_name not supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Validate_Penalty, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.setPenalty("some_not_real_penalty"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Penalty Not Supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Build_Basic, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Build
  BOOST_REQUIRE_THROW(clMove.build(), string); // Validation has not been run
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Build_GoodCategory, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Build_BadCategory, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("some_not_real_category"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_THROW(clMove.build(), string); // Unknown Category
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Build_BadSelectivity, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.9));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("some_not_real_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_THROW(clMove.build(), string); // Unknown Selectivity
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Execute_Square_TopLeft, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Initial Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 100.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 75);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Execute_Square_TopMiddle, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Initial Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 100.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 62.5);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Execute_Square_TopRight, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Initial Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 100.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 75.0);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Execute_Square_Middle, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("square_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Initial Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 100.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 50);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 12.5);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Execute_Hex_TopLeft, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("hex_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Initial Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 120));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Execute_Hex_TopMiddle, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("hex_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Initial Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 120.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 80);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Execute_Hex_TopRight, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("hex_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Initial Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 120.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 90.0);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( UniformMovementProcess_Execute_Hex_Middle, CUniformMovementTestFixture ) {
  // Var
  CUniformMovementProcess  clMove       = CUniformMovementProcess();

  // Validate & Build
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("uniform_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.setMethod("hex_uniform"));
  BOOST_REQUIRE_NO_THROW(clMove.setProportion(0.5));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Initial Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 120.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 60);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 10);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 0);
}

#endif
