//============================================================================
// Name        : TestDirectedProcesses.cpp
// Author      : S.Rasmussen
// Date        : 20/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "TestFixtures/CBaseTestFixture.h"
#include "../DirectedProcesses/CConstantDirectedProcess.h"
#include "../DirectedProcesses/CDoubleNormalDirectedProcess.h"
#include "../DirectedProcesses/CExponentialDirectedProcess.h"
#include "../DirectedProcesses/CInverseLogisticDirectedProcess.h"
#include "../DirectedProcesses/CLogisticDirectedProcess.h"
#include "../DirectedProcesses/CNormalDirectedProcess.h"
#include "../DirectedProcesses/CThresholdDirectedProcess.h"

// Namespaces
using namespace std;

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ConstantDirectedProcess, CBaseTestFixture ) {

  // Vars
  CConstantPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CConstantPreferenceFunction*>(pDirectedProcessManager->getProcess("constant_directed"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 1.0);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 1.0);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 1.0);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 1.0);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ConstantDirectedProcess_DistanceLayer, CBaseTestFixture ) {

  // Vars
  CConstantPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CConstantPreferenceFunction*>(pDirectedProcessManager->getProcess("constant_directed_distance"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 5.0000000000000002e-11);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 2.0);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 5.0000000000000002e-11);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 1.4142135623730951);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 2.8284271247461903);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 5.0000000000000002e-11);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 1.0);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 2.0);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 5.0000000000000002e-11);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 5.0000000000000002e-11);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 5.0000000000000002e-11);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( DoubleNormalDirectedProcess, CBaseTestFixture ) {

  // Vars
  CDoubleNormalPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CDoubleNormalPreferenceFunction*>(pDirectedProcessManager->getProcess("double_normal_directed"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.000244140625);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 0.000244140625);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 0.000244140625);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.000244140625);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 0.000244140625);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 0.000244140625);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.000244140625);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 0.000244140625);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 0.000244140625);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.000244140625);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 0.000244140625);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 0.000244140625);

}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ExponentialDirectedProcess, CBaseTestFixture ) {

  // Vars
  CExponentialPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CExponentialPreferenceFunction*>(pDirectedProcessManager->getProcess("exponential_directed"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 3.0590232050182579e-07);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 3.0590232050182579e-07);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 3.0590232050182579e-07);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 3.0590232050182579e-07);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 3.0590232050182579e-07);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 3.0590232050182579e-07);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 3.0590232050182579e-07);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 3.0590232050182579e-07);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 3.0590232050182579e-07);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 3.0590232050182579e-07);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 3.0590232050182579e-07);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 3.0590232050182579e-07);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( InverseLogisticDirectedProcess, CBaseTestFixture ) {

  // Vars
  CInverseLogisticPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CInverseLogisticPreferenceFunction*>(pDirectedProcessManager->getProcess("inverse_logistic_directed"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.30911402641729402);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 0.30911402641729402);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 0.30911402641729402);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.30911402641729402);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 0.30911402641729402);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 0.30911402641729402);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.30911402641729402);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 0.30911402641729402);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 0.30911402641729402);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.30911402641729402);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 0.30911402641729402);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 0.30911402641729402);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( LogisticDirectedProcess, CBaseTestFixture ) {

  // Vars
  CLogisticPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CLogisticPreferenceFunction*>(pDirectedProcessManager->getProcess("logistic_directed"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.033966712196426191);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 0.033966712196426191);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 0.033966712196426191);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.033966712196426191);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 0.033966712196426191);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 0.033966712196426191);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.033966712196426191);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 0.033966712196426191);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 0.033966712196426191);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.033966712196426191);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 0.033966712196426191);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 0.033966712196426191);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NormalDirectedProcess, CBaseTestFixture ) {

  // Vars
  CNormalPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CNormalPreferenceFunction*>(pDirectedProcessManager->getProcess("normal_directed"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.01698023222696966);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 0.01698023222696966);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 0.01698023222696966);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.01698023222696966);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 0.01698023222696966);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 0.01698023222696966);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.01698023222696966);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 0.01698023222696966);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 0.01698023222696966);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 0.01698023222696966);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 0.01698023222696966);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 0.01698023222696966);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ThresholdDirectedProcess, CBaseTestFixture ) {

  // Vars
  CThresholdPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CThresholdPreferenceFunction*>(pDirectedProcessManager->getProcess("threshold_directed"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 1);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 1);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 1);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 1);
}

//**********************************************************************
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ThresholdDirectedProcess_Distance, CBaseTestFixture ) {

  // Vars
  CThresholdPreferenceFunction *pProcess = 0;
  pProcess = static_cast<CThresholdPreferenceFunction*>(pDirectedProcessManager->getProcess("threshold_directed_distance"));

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 0, 0, 0), 0.0007662178654104007);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 0, 0), 0.049037943386265576);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 0, 0), 1.1972154147037494e-05);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 0), 0.0007662178654104007);

  BOOST_CHECK_EQUAL(pProcess->getResult(0, 0, 0, 0), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(1, 1, 1, 1), 1);
  BOOST_CHECK_EQUAL(pProcess->getResult(2, 2, 2, 2), 1);
}

#endif
