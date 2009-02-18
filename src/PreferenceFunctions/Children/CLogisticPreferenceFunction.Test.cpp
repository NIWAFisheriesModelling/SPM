//============================================================================
// Name        : CLogisticPreferenceFunction.Test.cpp
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
BOOST_FIXTURE_TEST_CASE( LogisticPreferenceFunction_DoubleLayer, CLayer_Fixture ) {

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_LOGISTIC, false));

  pPreference->addParameter(PARAM_LABEL, "logistic");
  pPreference->addParameter(PARAM_ALPHA, "2.6");
  pPreference->addParameter(PARAM_A50, "4.0");
  pPreference->addParameter(PARAM_ATO95, "12.7");
  pPreference->addParameter(PARAM_LAYER_NAME, "double_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.05723809824626918);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 1), 0.084226801451533301);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 2), 0.1199101614633967);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 3), 0.16493848884661177);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 4), 0.21910286858446729);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.85541486173675529);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 1), 0.88283834628703539);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 2), 0.90545991184907004);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 3), 0.92397488056162902);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 4), 0.93903325274013449);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.05723809824626918);
  BOOST_CHECK_EQUAL(pPreference->getResult(1, 0, 0, 1), 0.084226801451533301);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 2, 0, 2), 0.1199101614633967);
  BOOST_CHECK_EQUAL(pPreference->getResult(3, 0, 0, 3), 0.16493848884661177);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 4, 0, 4), 0.21910286858446729);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.85541486173675529);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 1, 3, 1), 0.88283834628703539);
  BOOST_CHECK_EQUAL(pPreference->getResult(2, 0, 3, 2), 0.90545991184907004);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 3, 3, 3), 0.92397488056162902);
  BOOST_CHECK_EQUAL(pPreference->getResult(4, 0, 3, 4), 0.93903325274013449);

  delete pPreference;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( LogisticPreferenceFunction_DistanceLayer, CLayer_Fixture ) {

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_LOGISTIC, false));

  pPreference->addParameter(PARAM_LABEL, "logistic");
  pPreference->addParameter(PARAM_ALPHA, "4.6");
  pPreference->addParameter(PARAM_A50, "1.0");
  pPreference->addParameter(PARAM_ATO95, "17.3");
  pPreference->addParameter(PARAM_LAYER_NAME, "distance_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.027417588490564686);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 1), 0.041234622211652958);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 2), 0.059985276102401841);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 3), 0.084426920938485708);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 4), 0.11504726766560526);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.084426920938485708);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 1), 0.088968017596493656);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 2), 0.10221476965350236);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 3), 0.12343005942229236);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 4), 0.15195704728810067);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.027417588490564686);
  BOOST_CHECK_EQUAL(pPreference->getResult(1, 0, 0, 1), 0.048354918303600752);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 2, 0, 2), 0.027417588490564686);
  BOOST_CHECK_EQUAL(pPreference->getResult(3, 0, 0, 3), 0.12343005942229236);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 4, 0, 4), 0.027417588490564686);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.084426920938485708);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 1, 3, 1), 0.084426920938485708);
  BOOST_CHECK_EQUAL(pPreference->getResult(2, 0, 3, 2), 0.065218558276417898);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 3, 3, 3), 0.084426920938485708);
  BOOST_CHECK_EQUAL(pPreference->getResult(4, 0, 3, 4), 0.11925391228688367);

  delete pPreference;
}
#endif
