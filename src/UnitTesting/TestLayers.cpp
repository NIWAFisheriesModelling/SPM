//============================================================================
// Name        : CTestLayers.cpp
// Author      : S.Rasmussen
// Date        : 27/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

#ifdef OPTIMISE
#error "OPTIMISE cannot be defined with UNITTEST"
#endif

// Defines
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE SPM_Unit_Tests

// Global Includes
#include <boost/test/included/unit_test.hpp>
#include <string>

// Local Includes
#include "TestFixtures/CBaseTestFixture.h"
#include "../CLayerManager.h"
#include "../CWorld.h"
#include "../Layers/CStringLayer.h"
#include "../Layers/NumericLayers/CAbundanceLayer.h"
#include "../Layers/NumericLayers/CDistanceLayer.h"
#include "../Layers/NumericLayers/CDoubleLayer.h"

// Namespaces
using namespace std;

//**********************************************************************
// BOOST_AUTO_TEST_CASE( StringLayerValues )
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( StringLayer, CBaseTestFixture ) {

  // Variables
  CStringLayer *pStringLayer  = 0;
  CWorld       *pWorld        = CWorld::Instance();

  // Check
  BOOST_REQUIRE_NO_THROW(pStringLayer = new CStringLayer());
  BOOST_REQUIRE_NO_THROW(pStringLayer->setLabel("string_layer"));
  BOOST_REQUIRE_GT(pStringLayer->getHeight(), 0);
  BOOST_REQUIRE_GT(pStringLayer->getWidth(), 0);
  BOOST_REQUIRE_EQUAL(pStringLayer->getHeight(), pWorld->getHeight());
  BOOST_REQUIRE_EQUAL(pStringLayer->getWidth(), pWorld->getWidth());
  BOOST_REQUIRE_THROW(pStringLayer->setValue(666, 1, "DATA"), string);
  BOOST_REQUIRE_THROW(pStringLayer->setValue(1, 666, "DATA"), string);

  // Try to use an Index when the function doesn't accept them (0 = Index Based)
  BOOST_REQUIRE_THROW(pStringLayer->setValue(0, 1, "DATA"), string);
  BOOST_REQUIRE_THROW(pStringLayer->setValue(1, 0, "DATA"), string);

  // Populate
  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j)
      BOOST_REQUIRE_NO_THROW(pStringLayer->setValue( (i+1), (j+1), "DATA"));

  // Verify
  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j)
      BOOST_REQUIRE_EQUAL(pStringLayer->getValue(i, j), "DATA");

  BOOST_REQUIRE_NO_THROW(pStringLayer->validate());
  BOOST_REQUIRE_NO_THROW(pStringLayer->build());
}

//**********************************************************************
// BOOST_AUTO_TEST_CASE( DoubleLayer )
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DoubleLayer, CBaseTestFixture ) {

  // Variables
  CDoubleLayer *pDoubleLayer  = 0;
  CWorld       *pWorld        = CWorld::Instance();

  // Check
  BOOST_REQUIRE_NO_THROW(pDoubleLayer = new CDoubleLayer());
  BOOST_REQUIRE_NO_THROW(pDoubleLayer->setLabel("double_layer"));
  BOOST_REQUIRE_GT(pDoubleLayer->getHeight(), 0);
  BOOST_REQUIRE_GT(pDoubleLayer->getWidth(), 0);
  BOOST_REQUIRE_EQUAL(pDoubleLayer->getHeight(), pWorld->getHeight());
  BOOST_REQUIRE_EQUAL(pDoubleLayer->getWidth(), pWorld->getWidth());
  BOOST_REQUIRE_THROW(pDoubleLayer->setValue(666, 1, 99), string);
  BOOST_REQUIRE_THROW(pDoubleLayer->setValue(1, 666, 99), string);

  // Try to use an Index when the function doesn't accept them (0 = Index Based)
  BOOST_REQUIRE_THROW(pDoubleLayer->setValue(0, 1, 99), string);
  BOOST_REQUIRE_THROW(pDoubleLayer->setValue(1, 0, 99), string);

  // Populate
  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j)
      BOOST_REQUIRE_NO_THROW(pDoubleLayer->setValue( (i+1), (j+1), 99));

  // Verify
  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j)
      BOOST_REQUIRE_EQUAL(pDoubleLayer->getValue(i, j, 0, 0), 99);

  BOOST_REQUIRE_NO_THROW(pDoubleLayer->validate());
  BOOST_REQUIRE_NO_THROW(pDoubleLayer->build());
}

//**********************************************************************
// BOOST_AUTO_TEST_CASE( AbundanceLayer )
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( AbundanceLayer, CBaseTestFixture ) {

  // Variables
  CAbundanceLayer *pAbundanceLayer  = 0;
  CWorld          *pWorld           = CWorld::Instance();

  // Check
  BOOST_REQUIRE_NO_THROW(pAbundanceLayer = new CAbundanceLayer());
  BOOST_REQUIRE_NO_THROW(pAbundanceLayer->setLabel("abundance_layer"));
  BOOST_REQUIRE_NO_THROW(pAbundanceLayer->addCategory("spawning"));
  BOOST_REQUIRE_NO_THROW(pAbundanceLayer->addSelectivity("constant_selectivity"));
  BOOST_REQUIRE_GT(pAbundanceLayer->getHeight(), 0);
  BOOST_REQUIRE_GT(pAbundanceLayer->getWidth(), 0);
  BOOST_REQUIRE_EQUAL(pAbundanceLayer->getHeight(), pWorld->getHeight());
  BOOST_REQUIRE_EQUAL(pAbundanceLayer->getWidth(), pWorld->getWidth());

  // Not allowed to Set Value on Abundance Layer
  BOOST_REQUIRE_THROW(pAbundanceLayer->setValue(1, 1, 99), string);

  BOOST_REQUIRE_NO_THROW(pAbundanceLayer->validate());
  BOOST_REQUIRE_NO_THROW(pAbundanceLayer->build());

  // Verify
  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j) {
      BOOST_REQUIRE_EQUAL(pAbundanceLayer->getValue(i, j, 0, 0), 0);
      BOOST_REQUIRE_NE(pAbundanceLayer->getValue(i, j, 0, 0), -1);
    }
}

//**********************************************************************
// BOOST_AUTO_TEST_CASE( DistanceLayer )
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DistanceLayer, CBaseTestFixture ) {

  // Variables
  CDistanceLayer  *pDistanceLayer  = 0;
  CWorld          *pWorld           = CWorld::Instance();

  // Check
  BOOST_REQUIRE_NO_THROW(pDistanceLayer = new CDistanceLayer());
  BOOST_REQUIRE_NO_THROW(pDistanceLayer->setLabel("distance_layer"));
  BOOST_REQUIRE_GT(pDistanceLayer->getHeight(), 0);
  BOOST_REQUIRE_GT(pDistanceLayer->getWidth(), 0);
  BOOST_REQUIRE_EQUAL(pDistanceLayer->getHeight(), pWorld->getHeight());
  BOOST_REQUIRE_EQUAL(pDistanceLayer->getWidth(), pWorld->getWidth());

  // Not allowed to Set Value on Abundance Layer
  BOOST_REQUIRE_THROW(pDistanceLayer->setValue(1, 1, 99), string);

  BOOST_REQUIRE_NO_THROW(pDistanceLayer->validate());
  BOOST_REQUIRE_NO_THROW(pDistanceLayer->build());

  // Verify
  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j)
      for (int k = 0; k < pWorld->getHeight(); ++k)
        for (int l = 0; l < pWorld->getWidth(); ++l) {
          //Workout Distance
          int X = i - k;
          int Y = j - l;
          double dValue = sqrt( (double)((X*X)+(Y*Y)) );
          //Check
          BOOST_REQUIRE_EQUAL(pDistanceLayer->getValue(i, j, k, l), dValue);
        }
}

#endif
