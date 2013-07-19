//============================================================================
// Name        : CBHRecruitmentProcess.Test.cpp
// Author      : S.Rasmussen A.Dunn
// Date        : 19/07/2013
// Copyright   : Copyright NIWA Science ©2013 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../TestFixtures/C1x1_Initialisation_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/Doublelayer.h"
#include "../../TestFixtures/ConfigurationFiles/DerivedQuantities/DerivedQuantity.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/BHRecruitment.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( BHRecruitmentProcess, C1x1_Initialisation_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(bh_recruitment);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(derived_quantity_ssb);
  addToConfiguration(numeric_one);
  addToConfiguration(constant);
  addToTimeStep("ageing bh_recruitment maturation mortality");
  loadAndRunEnvironment();

  // Check our Results
  CWorldSquare *pSquare = getSquare();

  BOOST_CHECK_CLOSE(pSquare->getAbundance(), 647.3987, 1e-4);

  // Immature only should've been recruited
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), 53.98835, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), 31.87160, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), 17.90088, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 4),  6.93986, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 5),  2.41795, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 6),  0.803326, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 7),  0.262228, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 8),  0.0851371, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 9),  0.00000, 1e-4);

  // mature only
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), 20.23246, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), 31.87160, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), 47.76675, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), 49.41438, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), 45.94104, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), 40.72833, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), 35.47606, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), 30.73450, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 9),144.60581, 1e-4);

}

#endif /* TEST */
