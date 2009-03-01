//============================================================================
// Name        : CNormalPreferenceFunction.Test.cpp
// Author      : S.Rasmussen
// Date        : 19/02/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CPreferenceFunctionFactory.h"
#include "../../TestFixtures/CLayer_Fixture.h"


//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NormalPreferenceFunction_DoubleLayer, CLayer_Fixture ) {

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_NORMAL, false));

  pPreference->addParameter(PARAM_LABEL, "normal");
  pPreference->addParameter(PARAM_ALPHA, "2.6");
  pPreference->addParameter(PARAM_MU, "4.0");
  pPreference->addParameter(PARAM_SIGMA, "12.7");
  pPreference->addParameter(PARAM_LAYER, "double_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.90432904762795996);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 1), 0.95628985183238169);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 2), 0.9888886374148611);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 3), 1.0);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 4), 0.9888886374148611);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.20008922132721632);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 1), 0.1513241918490256);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 2), 0.1119148729132336);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 3), 0.080939780454092253);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 4), 0.057244136911386245);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.90432904762795996);
  BOOST_CHECK_EQUAL(pPreference->getResult(1, 0, 0, 1), 0.95628985183238169);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 2, 0, 2), 0.9888886374148611);
  BOOST_CHECK_EQUAL(pPreference->getResult(3, 0, 0, 3), 1.0);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 4, 0, 4), 0.9888886374148611);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.20008922132721632);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 1, 3, 1), 0.1513241918490256);
  BOOST_CHECK_EQUAL(pPreference->getResult(2, 0, 3, 2), 0.1119148729132336);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 3, 3, 3), 0.080939780454092253);
  BOOST_CHECK_EQUAL(pPreference->getResult(4, 0, 3, 4), 0.057244136911386245);

  delete pPreference;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NormalPreferenceFunction_DistanceLayer, CLayer_Fixture ) {

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_NORMAL, false));

  pPreference->addParameter(PARAM_LABEL, "normal");
  pPreference->addParameter(PARAM_ALPHA, "1.0");
  pPreference->addParameter(PARAM_MU, "8.9");
  pPreference->addParameter(PARAM_SIGMA, "11.2");
  pPreference->addParameter(PARAM_LAYER, "distance_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.64552404020250753);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 1), 0.70831907568050456);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 2), 0.76868051031375506);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 3), 0.8250176054826841);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 4), 0.87575167651593899);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.8250176054826841);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 1), 0.83367221316986062);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 2), 0.85650708836363743);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 3), 0.8870459284254637);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 4), 0.91938868195811152);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.64552404020250753);
  BOOST_CHECK_EQUAL(pPreference->getResult(1, 0, 0, 1), 0.7337072662727443);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 2, 0, 2), 0.64552404020250753);
  BOOST_CHECK_EQUAL(pPreference->getResult(3, 0, 0, 3), 0.8870459284254637);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 4, 0, 4), 0.64552404020250753);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.8250176054826841);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 1, 3, 1), 0.8250176054826841);
  BOOST_CHECK_EQUAL(pPreference->getResult(2, 0, 3, 2), 0.78240214062551983);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 3, 3, 3), 0.8250176054826841);
  BOOST_CHECK_EQUAL(pPreference->getResult(4, 0, 3, 4), 0.88153549280571031);

  delete pPreference;
}
#endif
