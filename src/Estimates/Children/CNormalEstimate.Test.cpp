////============================================================================
//// Name        : CNormalPrior.Test.cpp
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
//BOOST_AUTO_TEST_CASE( NormalPrior ) {
//  // Get prior
//  CPrior *pPrior = CPriorFactory::buildPrior(PARAM_NORMAL, false);
//
//  // Add parameters
//  pPrior->addParameter(PARAM_LABEL, "prior");
//  pPrior->addParameter(PARAM_MU, "1");
//  pPrior->addParameter(PARAM_CV, "2");
//
//  // Validate and build
//  pPrior->validate();
//
//  // Check results
//  BOOST_CHECK_EQUAL(pPrior->getResult(1.0), 0.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(2.0), 0.125);
//  BOOST_CHECK_EQUAL(pPrior->getResult(3.0), 0.5);
//  BOOST_CHECK_EQUAL(pPrior->getResult(4.0), 1.125);
//  BOOST_CHECK_EQUAL(pPrior->getResult(5.0), 2.0);
//  BOOST_CHECK_EQUAL(pPrior->getResult(6.0), 3.125);
//  BOOST_CHECK_EQUAL(pPrior->getResult(7.0), 4.5);
//  BOOST_CHECK_EQUAL(pPrior->getResult(8.0), 6.125);
//  BOOST_CHECK_EQUAL(pPrior->getResult(9.0), 8.0);
//
//  // clear memory
//  delete pPrior;
//}
//#endif /* TEST */
