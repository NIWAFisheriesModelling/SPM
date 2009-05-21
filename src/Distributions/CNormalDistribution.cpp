//============================================================================
// Name        : CNormalDistribution.cpp
// Author      : S.Rasmussen
// Date        : 7/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNormalDistribution.h"

// Singleton Variable
CNormalDistribution* CNormalDistribution::clInstance = 0;

//**********************************************************************
// CNormalDistribution::CNormalDistribution()
// Default Constructor
//**********************************************************************
CNormalDistribution::CNormalDistribution() {


}

//**********************************************************************
// CNormalDistribution* CNormalDistribution::Instance()
// Instance Method - Singleton
//**********************************************************************
CNormalDistribution* CNormalDistribution::Instance() {
  if (clInstance == 0)
    clInstance = new CNormalDistribution();

  return clInstance;
}

//**********************************************************************
// void CNormalDistribution::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CNormalDistribution::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// double CNormalDistribution::getCDF(double x, double mu, double sigma)
// Get a a value from the normal CDF
//**********************************************************************
double CNormalDistribution::getCDF(double x, double mu, double sigma) {

  if (sigma <= 0) {
    if (x < mu)
      return 0;
    else if (x>=mu)
      return 1;
  }

  normal s(mu, sigma);
  return cdf(s, x);

}

//**********************************************************************
// void CNormalDistribution::validate()
// Validate
//**********************************************************************
void CNormalDistribution::validate() {
  try {

  } catch (string Ex) {
    Ex = "CNormalDistribution.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNormalDistribution::build()
// Build
//**********************************************************************
void CNormalDistribution::build() {
  try {

  } catch (string Ex) {
    Ex = "CNormalDistribution.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNormalDistribution::~CNormalDistribution()
// Destructor
//**********************************************************************
CNormalDistribution::~CNormalDistribution() {
}
