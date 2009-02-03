//============================================================================
// Name        : CThresholdBiomassPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CThresholdBiomassPreferenceFunction.h"

//**********************************************************************
// CThresholdBiomassPreferenceFunction::CThresholdBiomassPreferenceFunction(
//            CThresholdBiomassPreferenceFunction *Process)
// Default Constructor
//**********************************************************************
CThresholdBiomassPreferenceFunction::CThresholdBiomassPreferenceFunction() {
  // Register Estmables
  registerEstimable(PARAM_SIZE_WEIGHT, &dSizeWeight);
  registerEstimable(PARAM_BIOMASS, &dBiomass);
  registerEstimable(PARAM_LAMBDA, &dLambda);

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHT);
  pParameterList->registerAllowed(PARAM_BIOMASS);
  pParameterList->registerAllowed(PARAM_LAMBDA);
}

//**********************************************************************
// void CThresholdBiomassPreferenceFunction::validate()
// Validate our preference function
//**********************************************************************
void CThresholdBiomassPreferenceFunction::validate() {
  try {
    // Base validation
    CPreferenceFunction::validate();

    // Populate our variables
    dSizeWeight = pParameterList->getDouble(PARAM_SIZE_WEIGHT);
    dBiomass    = pParameterList->getDouble(PARAM_BIOMASS);
    dLambda     = pParameterList->getDouble(PARAM_LAMBDA);

    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

  } catch (string Ex) {
    Ex = "CThresholdBiomassPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CThresholdBiomassPreferenceFunction::getResult(int RIndex, int CIndex, int
//    TRIndex, int TCIndex)
// Get the result from this preference function
//**********************************************************************
double CThresholdBiomassPreferenceFunction::getResult(int RIndex, int CIndex, int
    TRIndex, int TCIndex) {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CThresholdBiomassPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// CThresholdBiomassPreferenceFunction::~CThresholdBiomassPreferenceFunction()
// Destructor
//**********************************************************************
CThresholdBiomassPreferenceFunction::~CThresholdBiomassPreferenceFunction() {
}
