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
BOOST_FIXTURE_TEST_CASE( RandomNumber_GenerateUniform, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();
  CConfiguration *pConfig = CConfiguration::Instance();

  // Test
  BOOST_CHECK_EQUAL(pConfig->getRandomSeed(), 123);

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
  CConfiguration *pConfig = CConfiguration::Instance();

  // Test
  BOOST_CHECK_EQUAL(pConfig->getRandomSeed(), 123);

  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.98076420044526458);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.41092436783947051);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.68482973426580429);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.57969429739750922);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.48093190742656589);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.13995076320134103);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.39211751730181277);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.40101755410432816);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.34317801473662257);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.62731700390577316);
  BOOST_CHECK_EQUAL(pGenerator->getRandomUniform_01(), 0.72904970846138895);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RandomNumber_GenerateNormal, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();
  CConfiguration *pConfig = CConfiguration::Instance();

  // Test
  BOOST_CHECK_EQUAL(pConfig->getRandomSeed(), 123);

  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -0.31330559956841553);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 3.5912405280278485);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 0.79226839876334365);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -7.243959572549965);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 0.10835610365389936);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -1.0654758441942942);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 11.913570666227807);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 1.2178160715445951);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -6.5754007292690506);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -1.0461464151065121);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), -9.1687034134455914);
  BOOST_CHECK_EQUAL(pGenerator->getRandomNormal(3.5, 7.9), 2.8385048010851683);
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

  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.056986739458629788);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.092254073429861763);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.14808344972482101);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.15705869344763532);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.51840398369851959);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 7.7379507314534406);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.48085177355526598);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 0.63430964164408521);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 3.6966147320880083);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 1.3118644812022462);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 1.4833644388704961);
  BOOST_CHECK_EQUAL(pGenerator->getRandomLogNormal(3.5, 7.9), 2.0913776355859439);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( RandomNumber_GenerateBinomial, CWorld_Fixture ) {

  CRandomNumberGenerator *pGenerator = CRandomNumberGenerator::Instance();
  CConfiguration *pConfig = CConfiguration::Instance();

  // Test
  BOOST_CHECK_EQUAL(pConfig->getRandomSeed(), 123);

  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
  BOOST_CHECK_EQUAL(pGenerator->getRandomBinomial(3.5, 7.9), 1.0);
}

#endif
