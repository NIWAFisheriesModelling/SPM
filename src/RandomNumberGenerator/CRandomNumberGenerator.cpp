//============================================================================
// Name        : CRandomNumberGenerator.cpp
// Author      : S.Rasmussen
// Date        : 7/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <boost/random/uniform_real.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

// Local Headers
#include "CRandomNumberGenerator.h"

// Singleton Variable
CRandomNumberGenerator* CRandomNumberGenerator::clInstance = 0;

//**********************************************************************
// CRandomNumberGenerator::CRandomNumberGenerator()
// Default Constructor
//**********************************************************************
CRandomNumberGenerator::CRandomNumberGenerator() {

  // Set our Seed.
  clGenerator.seed(pConfig->getRandomSeed());
}

//**********************************************************************
// CRandomNumberGenerator* CRandomNumberGenerator::Instance()
// Instance Method - Singleton
//**********************************************************************
CRandomNumberGenerator* CRandomNumberGenerator::Instance() {
  if (clInstance == 0)
    clInstance = new CRandomNumberGenerator();

  return clInstance;
}

//**********************************************************************
// void CRandomNumberGenerator::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CRandomNumberGenerator::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomUniform(double min, double max)
// Get a uniform distributed random number
//**********************************************************************
double CRandomNumberGenerator::getRandomUniform(double min, double max) {

  // Build our Uniform Distribution Generator
  boost::uniform_real<> distUniform(min,max);
  boost::variate_generator<mt19937&, boost::uniform_real<> > gen(clGenerator, distUniform);

  return gen(); // Generated Number
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomNormal(double mean, double sigma)
// Get a normal distributed random number
//**********************************************************************
double CRandomNumberGenerator::getRandomNormal(double mean, double sigma) {

  // Build our Normal Distribution Generator
  boost::normal_distribution<> distNormal(mean,sigma);
  boost::variate_generator<mt19937&, boost::normal_distribution<> > gen(clGenerator, distNormal);

  return gen(); // Generated Number
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomLogNormal(double mean, double cv)
// Get a lognormal distributed random number, with mean and c.v.
//**********************************************************************
double CRandomNumberGenerator::getRandomLogNormal(double mean, double cv) {

  double dLogSigma = sqrt(log(cv*cv + 1.0));
  double dLogMean = log(mean) - (dLogSigma*dLogSigma)/2.0;

  double result = CRandomNumberGenerator::getRandomNormal(dLogMean, dLogSigma);

  return std::exp(result); // Generated Number
}

//**********************************************************************
// void CRandomNumberGenerator::validate()
// Validate RNG
//**********************************************************************
void CRandomNumberGenerator::validate() {
  try {

  } catch (string Ex) {
    Ex = "CRandomNumberGenerator.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CRandomNumberGenerator::build()
// Build our RNG
//**********************************************************************
void CRandomNumberGenerator::build() {
  try {

  } catch (string Ex) {
    Ex = "CRandomNumberGenerator.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CRandomNumberGenerator::~CRandomNumberGenerator()
// Destructor
//**********************************************************************
CRandomNumberGenerator::~CRandomNumberGenerator() {
}
