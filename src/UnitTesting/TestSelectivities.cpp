//============================================================================
// Name        : CTestSelectivities.cpp
// Author      : S.Rasmussen
// Date        : 29/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "TestFixtures/CBaseTestFixture.h"
#include "../Selectivities/CConstantSelectivity.h"
#include "../Selectivities/CDoubleNormalSelectivity.h"
#include "../Selectivities/CKnifeEdgeSelectivity.h"
#include "../Selectivities/CLogisticProducingSelectivity.h"
#include "../Selectivities/CLogisticSelectivity.h"

// Namespaces
using namespace std;

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ConstantSelectivity, CBaseTestFixture ) {
  // Vars
  CConstantSelectivity clSelectivity = CConstantSelectivity();
  BOOST_REQUIRE_NO_THROW(clSelectivity.setLabel("constant"));

  BOOST_REQUIRE_NO_THROW(clSelectivity.validate());
  BOOST_REQUIRE_NO_THROW(clSelectivity.build());

  BOOST_REQUIRE_NO_THROW(clSelectivity.setC(1.0));
  for (int i = 0; i < 10; ++i)
    BOOST_CHECK_EQUAL(clSelectivity.getResult(i), 1.0);

  BOOST_REQUIRE_NO_THROW(clSelectivity.setC(3.5));
  for (int i = 0; i < 10; ++i)
    BOOST_CHECK_EQUAL(clSelectivity.getResult(i), 3.5);

  BOOST_REQUIRE_NO_THROW(clSelectivity.setC(7.9));
  for (int i = 0; i < 10; ++i)
    BOOST_CHECK_EQUAL(clSelectivity.getResult(i), 7.9);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DoublenormalSelectivity, CBaseTestFixture ) {
  // Vars
  CDoubleNormalSelectivity clSelectivity = CDoubleNormalSelectivity();
  BOOST_REQUIRE_NO_THROW(clSelectivity.setMu(5));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setSigmaL(1));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setSigmaR(10));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setLabel("Doublenormal"));

  BOOST_REQUIRE_NO_THROW(clSelectivity.validate());
  BOOST_REQUIRE_NO_THROW(clSelectivity.build());

  BOOST_CHECK_EQUAL(clSelectivity.getResult(0), 2.9802322387695312e-08);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(1), 1.52587890625e-05);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(2), 0.001953125);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(3), 0.0625);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(4), 0.5);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(5), 1);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(6), 0.993092495437035935);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( KnifeedgeSelectivity, CBaseTestFixture ) {
  // Vars
  CKnifeEdgeSelectivity clSelectivity = CKnifeEdgeSelectivity();
  BOOST_REQUIRE_NO_THROW(clSelectivity.setC(3.0));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setLabel("Knifeedge"));

  BOOST_REQUIRE_NO_THROW(clSelectivity.validate());
  BOOST_REQUIRE_NO_THROW(clSelectivity.build());

  BOOST_CHECK_EQUAL(clSelectivity.getResult(0), 0.0);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(1), 0.0);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(2), 0.0);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(3), 1.0);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(4), 1.0);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(5), 1.0);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(6), 1.0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( LogisticProductingSelectivity, CBaseTestFixture ) {
  // Vars
  CLogisticProducingSelectivity clSelectivity = CLogisticProducingSelectivity();
  BOOST_REQUIRE_NO_THROW(clSelectivity.setLabel("LogisticProducting"));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setL(1));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setH(20));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setA50(8));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setAto95(3));

  BOOST_REQUIRE_NO_THROW(clSelectivity.validate());
  BOOST_REQUIRE_NO_THROW(clSelectivity.build());

  BOOST_CHECK_EQUAL(clSelectivity.getResult(0), 0);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(1), 0.0010370292068795884);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(2), 0.0017271928818112837);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(3), 0.0045877003367851103);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(4), 0.012093777212385453);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(5), 0.031262191160784228);

  BOOST_CHECK_EQUAL(clSelectivity.getResult(10), 0.54824683581581568);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(11), 0.59398163205489984);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(12), 0.61315004600329848);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(13), 0.62065612287889804);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(14), 0.62351663033386895);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(15), 0.62459542710961446);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( LogisticSelectivity, CBaseTestFixture ) {
  // Vars
  CLogisticSelectivity clSelectivity = CLogisticSelectivity();
  BOOST_REQUIRE_NO_THROW(clSelectivity.setLabel("logistic"));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setA50(8));
  BOOST_REQUIRE_NO_THROW(clSelectivity.setAto95(3));

  BOOST_REQUIRE_NO_THROW(clSelectivity.validate());
  BOOST_REQUIRE_NO_THROW(clSelectivity.build());

  BOOST_CHECK_EQUAL(clSelectivity.getResult(0), 0.00038888525246728368);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(1), 0.0010370292068795884);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(2), 0.0027624309392265192);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(3), 0.0073374580706613941);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(4), 0.019342497699835048);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(5), 0.050000000000000003);

  BOOST_CHECK_EQUAL(clSelectivity.getResult(10), 0.87685286197012446);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(11), 0.94999999999999996);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(12), 0.98065750230016491);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(13), 0.99266254192933856);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(14), 0.99723756906077343);
  BOOST_CHECK_EQUAL(clSelectivity.getResult(15), 0.99896297079312046);
}
#endif
