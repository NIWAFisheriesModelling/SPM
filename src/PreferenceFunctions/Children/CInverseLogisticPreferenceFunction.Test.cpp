//============================================================================
// Name        : CInverseLogisticPreferenceFunction.Test.cpp
// Author      : S.Rasmussen
// Date        : 19/02/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
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
BOOST_FIXTURE_TEST_CASE( InverseLogisticPreferenceFunction_DoubleLayer, CLayer_Fixture ) {

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_INVERSE_LOGISTIC, false));

  pPreference->addParameter(PARAM_LABEL, "inverse_logistic");
  pPreference->addParameter(PARAM_ALPHA, "2.6");
  pPreference->addParameter(PARAM_A50, "4.0");
  pPreference->addParameter(PARAM_ATO95, "12.7");
  pPreference->addParameter(PARAM_LAYER_NAME, "double_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.34918969856531312);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 1), 0.28121239557595651);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 2), 0.21910286858446729);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 3), 0.16493848884661177);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 4), 0.1199101614633967);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.00061754965277943425);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 1), 0.00034880620601662499);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 2), 0.00019578533846505952);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 3), 0.00010933998947373815);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 4), 6.0814586625724475e-005);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.34918969856531312);
  BOOST_CHECK_EQUAL(pPreference->getResult(1, 0, 0, 1), 0.28121239557595651);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 2, 0, 2), 0.21910286858446729);
  BOOST_CHECK_EQUAL(pPreference->getResult(3, 0, 0, 3), 0.16493848884661177);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 4, 0, 4), 0.1199101614633967);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.00061754965277943425);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 1, 3, 1), 0.00034880620601662499);
  BOOST_CHECK_EQUAL(pPreference->getResult(2, 0, 3, 2), 0.00019578533846505952);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 3, 3, 3), 0.00010933998947373815);
  BOOST_CHECK_EQUAL(pPreference->getResult(4, 0, 3, 4), 6.0814586625724475e-005);

  delete pPreference;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( InverseLogisticPreferenceFunction_DistanceLayer, CLayer_Fixture ) {

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_INVERSE_LOGISTIC, false));

  pPreference->addParameter(PARAM_LABEL, "inverse_logistic");
  pPreference->addParameter(PARAM_ALPHA, "1.6");
  pPreference->addParameter(PARAM_A50, "2.4");
  pPreference->addParameter(PARAM_ATO95, "9.6");
  pPreference->addParameter(PARAM_LAYER_NAME, "distance_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.53464229595248391);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 1), 0.44838001732486438);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 2), 0.36280275877413631);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 3), 0.28279836647613676);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 4), 0.21239303515463828);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.28279836647613676);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 1), 0.27063528601585579);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 2), 0.23882331665411477);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 3), 0.19706672286914456);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 4), 0.15397738538668065);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 0.53464229595248391);
  BOOST_CHECK_EQUAL(pPreference->getResult(1, 0, 0, 1), 0.41256257374072258);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 2, 0, 2), 0.53464229595248391);
  BOOST_CHECK_EQUAL(pPreference->getResult(3, 0, 0, 3), 0.19706672286914456);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 4, 0, 4), 0.53464229595248391);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.28279836647613676);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 1, 3, 1), 0.28279836647613676);
  BOOST_CHECK_EQUAL(pPreference->getResult(2, 0, 3, 2), 0.34324285009655131);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 3, 3, 3), 0.28279836647613676);
  BOOST_CHECK_EQUAL(pPreference->getResult(4, 0, 3, 4), 0.20452654595672901);

  delete pPreference;
}
#endif
