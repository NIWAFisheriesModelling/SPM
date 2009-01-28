//============================================================================
// Name        : CPriorFactory.Test.cpp
// Author      : S.Rasmussen
// Date        : 26/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Headers
#include "CPriorFactory.h"
#include "../Children/CBetaPrior.h"
#include "../Children/CLogNormalPrior.h"
#include "../Children/CNormalByStdevPrior.h"
#include "../Children/CNormalLogPrior.h"
#include "../Children/CNormalPrior.h"
#include "../Children/CUniformLogPrior.h"
#include "../Children/CUniformPrior.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( Build_BetaPrior) {
  CPrior *pPrior= 0;

  BOOST_REQUIRE_NO_THROW(pPrior = CPriorFactory::buildPrior(PARAM_BETA, false));

  CBetaPrior *pPtr = dynamic_cast<CBetaPrior*>(pPrior);
  BOOST_ASSERT(pPtr != 0);

  CLogNormalPrior *pPtr2 = dynamic_cast<CLogNormalPrior*>(pPrior);
  BOOST_ASSERT(pPtr2 == 0);

  delete pPrior;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( Build_LogNormalPrior) {
  CPrior *pPrior= 0;

  BOOST_REQUIRE_NO_THROW(pPrior = CPriorFactory::buildPrior(PARAM_LOG_NORMAL, false));

  CLogNormalPrior *pPtr = dynamic_cast<CLogNormalPrior*>(pPrior);
  BOOST_ASSERT(pPtr != 0);

  CBetaPrior *pPtr2 = dynamic_cast<CBetaPrior*>(pPrior);
  BOOST_ASSERT(pPtr2 == 0);

  delete pPrior;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( Build_LogNormalByStdevPrior) {
  CPrior *pPrior= 0;

  BOOST_REQUIRE_NO_THROW(pPrior = CPriorFactory::buildPrior(PARAM_NORMAL_BY_STDEV, false));

  CNormalByStdevPrior *pPtr = dynamic_cast<CNormalByStdevPrior*>(pPrior);
  BOOST_ASSERT(pPtr != 0);

  CLogNormalPrior *pPtr2 = dynamic_cast<CLogNormalPrior*>(pPrior);
  BOOST_ASSERT(pPtr2 == 0);

  delete pPrior;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( Build_NormalLogPrior) {
  CPrior *pPrior= 0;

  BOOST_REQUIRE_NO_THROW(pPrior = CPriorFactory::buildPrior(PARAM_NORMAL_LOG, false));

  CNormalLogPrior *pPtr = dynamic_cast<CNormalLogPrior*>(pPrior);
  BOOST_ASSERT(pPtr != 0);

  CNormalByStdevPrior *pPtr2 = dynamic_cast<CNormalByStdevPrior*>(pPrior);
  BOOST_ASSERT(pPtr2 == 0);

  delete pPrior;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( Build_NormalPrior) {
  CPrior *pPrior= 0;

  BOOST_REQUIRE_NO_THROW(pPrior = CPriorFactory::buildPrior(PARAM_NORMAL, false));

  CNormalPrior *pPtr = dynamic_cast<CNormalPrior*>(pPrior);
  BOOST_ASSERT(pPtr != 0);

  CNormalLogPrior *pPtr2 = dynamic_cast<CNormalLogPrior*>(pPrior);
  BOOST_ASSERT(pPtr2 == 0);

  delete pPrior;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( Build_UniformLogPrior) {
  CPrior *pPrior= 0;

  BOOST_REQUIRE_NO_THROW(pPrior = CPriorFactory::buildPrior(PARAM_UNIFORM_LOG, false));

  CUniformLogPrior *pPtr = dynamic_cast<CUniformLogPrior*>(pPrior);
  BOOST_ASSERT(pPtr != 0);

  CNormalPrior *pPtr2 = dynamic_cast<CNormalPrior*>(pPrior);
  BOOST_ASSERT(pPtr2 == 0);

  delete pPrior;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE( Build_UniformPrior) {
  CPrior *pPrior= 0;

  BOOST_REQUIRE_NO_THROW(pPrior = CPriorFactory::buildPrior(PARAM_UNIFORM, false));

  CUniformPrior *pPtr = dynamic_cast<CUniformPrior*>(pPrior);
  BOOST_ASSERT(pPtr != 0);

  CUniformLogPrior *pPtr2 = dynamic_cast<CUniformLogPrior*>(pPrior);
  BOOST_ASSERT(pPtr2 == 0);

  delete pPrior;
}

#endif
