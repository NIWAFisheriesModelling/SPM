//============================================================================
// Name        : CLogisticSelectivity.Test.cpp
// Author      : S.Rasmussen
// Date        : 12/02/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CSelectivityFactory.h"
#include "../../TestFixtures/CWorld_Fixture.h"

//**********************************************************************
//
//
//**********************************************************************
// this test case will use struct F as fixture
BOOST_FIXTURE_TEST_CASE( LogisticSelectivity, CWorld_Fixture ) {

  CSelectivity *pSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_LOGISTIC, false));

  pSelectivity->addParameter(PARAM_LABEL, "selectivity");
  pSelectivity->addParameter(PARAM_A50, "8");
  pSelectivity->addParameter(PARAM_ATO95, "3");

  BOOST_REQUIRE_NO_THROW(pSelectivity->validate());
  BOOST_REQUIRE_NO_THROW(pSelectivity->build());

  BOOST_CHECK_EQUAL(pSelectivity->getResult(0), 0.0010370292068795884);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(1), 0.0027624309392265192);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(2), 0.0073374580706613941);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(3), 0.019342497699835048);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(4), 0.050000000000000003);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(5), 0.12314713802987559);

  BOOST_CHECK_EQUAL(pSelectivity->getResult(10), 0.94999999999999996);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(11), 0.98065750230016491);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(12), 0.99266254192933856);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(13), 0.99723756906077343);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(14), 0.99896297079312046);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(15), 0.99961111474753273);

  BOOST_CHECK_EQUAL(pSelectivity->getResult(19), 0.99999232669848526);

  BOOST_REQUIRE_THROW(pSelectivity->getResult(20), std::string);

  delete pSelectivity;
}
#endif
