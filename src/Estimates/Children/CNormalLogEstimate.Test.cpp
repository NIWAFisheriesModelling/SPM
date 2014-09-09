////============================================================================
//// Name        : CNormalLogPrior.Test.cpp
//// Author      : S.Rasmussen
//// Date        : 23/04/2009
//// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
//// Description :
//// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
////============================================================================
//#ifdef TEST
//
//// Global Includes
//#include <boost/test/unit_test.hpp>
//#include <string>
//
//// Local Includes
//#include "../Factory/CPriorFactory.h"
//
////**********************************************************************
////
////
////**********************************************************************
//BOOST_AUTO_TEST_CASE( NormalLogPrior ) {
//  // Get prior
//  CPrior *pPrior = CPriorFactory::buildPrior(PARAM_NORMAL_LOG, false);
//
//  // Add parameters
//  pPrior->addParameter(PARAM_LABEL, "prior");
//  pPrior->addParameter(PARAM_MU, "1");
//  pPrior->addParameter(PARAM_SIGMA, "2");
//
//  // Validate and build
//  pPrior->validate();
//
//  // Check results
//  BOOST_CHECK_EQUAL(pPrior->getResult(1.0), 0.125);
//  BOOST_CHECK_EQUAL(pPrior->getResult(2.0), 0.70491701215973412);
//  BOOST_CHECK_EQUAL(pPrior->getResult(3.0), 1.099827836602655);
//  BOOST_CHECK_EQUAL(pPrior->getResult(4.0), 1.4049472777990186);
//  BOOST_CHECK_EQUAL(pPrior->getResult(5.0), 1.6558647335731045);
//  BOOST_CHECK_EQUAL(pPrior->getResult(6.0), 1.8701198513670914);
//  BOOST_CHECK_EQUAL(pPrior->getResult(7.0), 2.0577534003160438);
//  BOOST_CHECK_EQUAL(pPrior->getResult(8.0), 2.2250907969178533);
//  BOOST_CHECK_EQUAL(pPrior->getResult(9.0), 2.3763929134084556);
//
//  // clear memory
//  delete pPrior;
//}
//#endif /* TEST */
