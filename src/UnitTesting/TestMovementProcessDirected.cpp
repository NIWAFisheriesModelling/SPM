//============================================================================
// Name        : TestMovementProcessDirected.cpp
// Author      : S.Rasmussen
// Date        : 21/07/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Includes
#include "TestFixtures/CDirectedMovementTestFixture.h"
#include "../Processes/Movement/CDirectedMovementProcess.h"

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Validate_Basic, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Missing label
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Validate_GoodLabel, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Missing directed_processes
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Validate_GoodDirectedProcess, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Missing categories
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Validate_GoodCategories, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Validate_Selectivity, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // Selectivities not supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Validate_Layer, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  // Empty Validation.
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.setLayerName("double_layer"));
  BOOST_REQUIRE_THROW(clMove.validate(), string); // layer_name not supported
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Build_Basic, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_THROW(clMove.build(), string); // validation has not been run before building
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Build_GoodDirectedProcess, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Build_BadDirectedProcess, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("some_not_real_process"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_THROW(clMove.build(), string); // Unknown Process
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Build_GoodCategory, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Build_BadCategory, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("some_not_real_category"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_THROW(clMove.build(), string); // Unknown Category
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Execute_SinglePopulation, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 900.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 100);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Execute_DualPopulation, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 900.0));

  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 900.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 200);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Execute_SinglePopulationDistance, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed_distance"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 900.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 3.057948561036028e-09);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 61.163007899204217);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 122.32601579840843);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 61.163007899204217);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 86.497555286587357);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 136.76464337097727);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 122.32601579840843);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 136.76464337097727);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 172.99511057317471);

  double dTotal = 0;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      dTotal += pWorld->getBaseSquare(i, j)->getValue(spawningIndex, 0);

  BOOST_CHECK_EQUAL(dTotal, 900);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DirectedMovementProcess_Execute_DualPopulationDistance, CDirectedMovementTestFixture ) {
  // Var
  CDirectedMovementProcess  clMove       = CDirectedMovementProcess();

  //
  BOOST_REQUIRE_NO_THROW(clMove.setLabel("directed_movement"));
  BOOST_REQUIRE_NO_THROW(clMove.addDirectedProcess("constant_directed_distance"));
  BOOST_REQUIRE_NO_THROW(clMove.addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(clMove.validate()); // OK!
  BOOST_REQUIRE_NO_THROW(clMove.build()); // OK!

  // Setup Population
  CWorldSquare *pSquare = 0;
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 900.0));

  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
    BOOST_REQUIRE_NO_THROW(pSquare->addValue(spawningIndex, 0, 900.0));

  BOOST_REQUIRE_NO_THROW(clMove.execute());
  BOOST_REQUIRE_NO_THROW(pWorld->mergeDifferenceGrid());

  // Check Top Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 163.60724031349287);
  // Check Top Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 207.49777227731477);
  // Check Top Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(0, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 285.93325610884341);

  // Check Middle Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 164.63731211430184);
  // Check Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 159.66493747564263);
  // Check Middle Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(1, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 240.23894758607489);

  // Check Bottom Left
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 0));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 195.49339798746371);
  // Check Bottom Middle
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 1));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 136.76464337463574);
  // Check Bottom Right
  BOOST_REQUIRE_NO_THROW(pSquare = pWorld->getBaseSquare(2, 2));
  BOOST_CHECK_EQUAL(pSquare->getValue(spawningIndex, 0), 246.16249276222999);

  // Get Total Population and Verify it
  double dTotal = 0;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      dTotal += pWorld->getBaseSquare(i, j)->getValue(spawningIndex, 0);

  BOOST_CHECK_EQUAL(true, isSame(dTotal, 1800));
}

#endif
