//============================================================================
// Name        : CRandomNumberGenerator.Test.cpp
// Author      : S.Rasmussen
// Date        : 19/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description : Unit Tests for Random Number Generator
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "CRandomNumberGenerator.h"
#include "../CConfiguration.h"
#include "../TestFixtures/CWorld_Fixture.h"


//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RandomNumber_Reset, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();

  // Test
  pGenerator->Reset(2468);

  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.45965513936243951);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.13950349437072873);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.51783327478915453);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.12138748820871115);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.48201335011981428);

  pGenerator->Reset(2468);

  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.45965513936243951);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.13950349437072873);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.51783327478915453);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.12138748820871115);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.48201335011981428);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RandomNumber_GenerateUniform, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();

  // Test
  pGenerator->Reset(123);

  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 6.5644644239917405);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 6.6370034142397341);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 4.7590130904689429);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 5.3852720698341727);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 4.4981464017182589);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 6.5398933460935957);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 5.9257849665358666);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 6.6642613585107036);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 6.6656634704209861);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 5.6609233034774658);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 5.3616684266366068);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform(3.5, 7.9), 6.9321221458725635);

}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RandomNumber_GenerateUniform01, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();

  // Test
  pGenerator->Reset(31337);

  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.72185210674069822);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.81047213799320161);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.96644080197438598);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.32601338555105031);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.28904907335527241);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.29844888462685049);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.17134623066522181);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.2544191365595907);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.37161758821457624);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.061489183222874999);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.98030700697563589);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RandomNumber_GenerateNormal, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();

  // Test
  pGenerator->Reset(123);

  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -0.61940019542828928);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 1.618776687971744);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 5.2545068045315713);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -8.441452535514653);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 1.7492572787620508);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -8.6744887776345472);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 11.568123356065565);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -0.64113237484573116);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -0.80694027757984887);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -2.7300957578196856);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -2.6333897675514244);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 2.5821298737350658);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RandomNumber_GenerateLogNormal, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();
  CConfiguration *pConfig = CConfiguration::Instance();

  // Test
  BOOST_CHECK_EQUAL(pConfig->getRandomSeed(), 123);

  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.10687266483654928);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 8.1506486836276402);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.049065322500023142);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.35379471852562877);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 1.0845094610470529);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.64567353340450262);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.018784713414446545);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.053298607650668767);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.14091413875742836);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 1.7591108850796946);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.25752772312688654);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.10115061626022878);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RandomNumber_GenerateBinomial, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();

  // Test
  pGenerator->Reset(123);

  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.0, 1000), 0.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.1, 1000), 80.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.2, 1000), 214.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.3, 1000), 302.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.4, 1000), 405.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.5, 1000), 488.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.6, 1000), 587.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.7, 1000), 706.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.8, 1000), 803.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(0.9, 1000), 896.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(1.0, 1000), 1000.0);
}

#endif
