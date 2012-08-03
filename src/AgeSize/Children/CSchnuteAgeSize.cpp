//============================================================================
// Name        : CSchnuteAgeSize.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSchnuteAgeSize.h"
#include "../../Helpers/CError.h"
#include "../../SizeWeight/CSizeWeight.h"

//**********************************************************************
// CSchnuteAgeSize::CSchnuteAgeSize()
// Default Constructor
//**********************************************************************
CSchnuteAgeSize::CSchnuteAgeSize() {

  // regsiter estimables
  registerEstimable(PARAM_Y1, &dY1);
  registerEstimable(PARAM_Y2, &dY2);
  registerEstimable(PARAM_TAU1, &dTau1);
  registerEstimable(PARAM_TAU2, &dTau2);
  registerEstimable(PARAM_A, &dA);
  registerEstimable(PARAM_B, &dB);
  //registerEstimable(PARAM_CV, &dCV);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_Y1);
  pParameterList->registerAllowed(PARAM_Y2);
  pParameterList->registerAllowed(PARAM_TAU1);
  pParameterList->registerAllowed(PARAM_TAU2);
  pParameterList->registerAllowed(PARAM_A);
  pParameterList->registerAllowed(PARAM_B);
  //pParameterList->registerAllowed(PARAM_CV);
  pParameterList->registerAllowed(PARAM_DISTRIBUTION);
  pParameterList->registerAllowed(PARAM_BY_LENGTH);
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHT);

}

//**********************************************************************
// voidCSchnuteAgeSize::validate()
// Validate the age-size relationship
//**********************************************************************
void CSchnuteAgeSize::validate() {
  try {

    // Get our variables
    dY1             = pParameterList->getDouble(PARAM_Y1);
    dY2             = pParameterList->getDouble(PARAM_Y2);
    dTau1           = pParameterList->getDouble(PARAM_TAU1);
    dTau2           = pParameterList->getDouble(PARAM_TAU2);
    dA              = pParameterList->getDouble(PARAM_A);
    dB              = pParameterList->getDouble(PARAM_B);
    //dCV             = pParameterList->getDouble(PARAM_CV,true,0);
    //sDistribution   = pParameterList->getString(PARAM_DISTRIBUTION, true, PARAM_NORMAL);
    bByLength       = pParameterList->getBool(PARAM_BY_LENGTH,true,1);

    // Validate parent
    CAgeSize::validate();

    // Local validation
    //if (dCV <= 0)
    //  CError::errorLessThanEqualTo(PARAM_CV, PARAM_ZERO);
    if (dA <= 0)
      CError::errorLessThanEqualTo(PARAM_A, PARAM_ZERO);
    if (dB < 1)
      CError::errorLessThanEqualTo(PARAM_B, PARAM_ONE);

    //if ( (sDistribution != PARAM_NORMAL) && (sDistribution != PARAM_LOGNORMAL) )
    //  CError::errorUnknown(PARAM_DISTRIBUTION, sDistribution);

  } catch (string &Ex) {
    Ex = "CSchnuteAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCSchnuteAgeSize::build()
// Validate the age-size relationship
//**********************************************************************
void CSchnuteAgeSize::build() {
  try {
    // Base
    CAgeSize::build();

    sSizeWeight = pParameterList->getString(PARAM_SIZE_WEIGHT);
    CSizeWeightManager *pSizeWeightManager = CSizeWeightManager::Instance();
    pSizeWeight = pSizeWeightManager->getSizeWeight(sSizeWeight);

    // Rebuild
    rebuild();

  } catch (string &Ex) {
    Ex = "CSchnuteAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCSchnuteAgeSize::rebuild()
// Validate the age-size relationship
//**********************************************************************
void CSchnuteAgeSize::rebuild() {
  try {
    // Base
    CAgeSize::rebuild();


  } catch (string &Ex) {
    Ex = "CSchnuteAgeSize.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CSchnuteAgeSize::getMeanSize(double &age)
// Apply age-size relationship
//**********************************************************************
double CSchnuteAgeSize::getMeanSize(double &age) {
  double dSize = 0;
  double dTemp = 0;

  try {

    if (dA != 0) {
      dTemp = (1 - exp( - dA * (age - dTau1))) / (1 - exp(- dA * (dTau2 - dTau1)));
    } else {
      dTemp = (age - dTau1) / (dTau2 - dTau1);
    }
    if (dB != 0) {
      dSize = pow((pow(dY1,dB) + (pow(dY2,dB) - pow(dY1,dB)) * dTemp), 1 / dB);
    } else {
      dSize = dY1 * exp(log( dY2/ dY1) * dTemp);
    }

  } catch (string &Ex) {
    Ex = "CSchnuteAgeSize.getMeanSize(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  if (dSize < 0)
    return 0;

  return dSize;
}

//**********************************************************************
// double CSchnuteAgeSize::getMeanWeight(double &age)
// Apply size-weight relationship
//**********************************************************************
double CSchnuteAgeSize::getMeanWeight(double &age) {
  double dWeight = 0;

  try {
    double dSize = this->getMeanSize( age );
    dWeight = getMeanWeightFromSize( dSize );

  } catch (string &Ex) {
    Ex = "CSchnuteAgeSize.getMeanWeight(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return dWeight;
}

//**********************************************************************
// double CSchnuteAgeSize::getMeanWeightFromSize(double &size)
// Apply size-weight relationship
//**********************************************************************
double CSchnuteAgeSize::getMeanWeightFromSize(double &size) {

double dWeight = 0;

  try {
    dWeight = pSizeWeight->getMeanWeight( size );

  } catch (string &Ex) {
    Ex = "CSchnuteAgeSize.getMeanWeightFromSize(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return dWeight;
}

//**********************************************************************
// CSchnuteAgeSize::~CSchnuteAgeSize()
// Destructor
//**********************************************************************
CSchnuteAgeSize::~CSchnuteAgeSize() {
}
