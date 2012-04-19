//============================================================================
// Name        : CThresholdPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CThresholdPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CThresholdPreferenceFunction::CThresholdPreferenceFunction()
// Default Constructor
//**********************************************************************
CThresholdPreferenceFunction::CThresholdPreferenceFunction() {
  // Register estimables
  registerEstimable(PARAM_N, &dN);
  registerEstimable(PARAM_LAMBDA, &dLambda);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_N);
  pParameterList->registerAllowed(PARAM_LAMBDA);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
}

//**********************************************************************
// void CThresholdPreferenceFunction::validate()
// Validate
//**********************************************************************
void CThresholdPreferenceFunction::validate() {
  try {
    // Base Validation
    CPreferenceFunction::validate();

    // Assign local variables
    dN        = pParameterList->getDouble(PARAM_N);
    dLambda   = pParameterList->getDouble(PARAM_LAMBDA);

  } catch (string &Ex) {
    Ex = "CThresholdPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CThresholdPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CThresholdPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    if (dLayerValue > dN)
      dRet = 1.0/(pow(dLayerValue/dN,dLambda));
    else
      dRet = 1.0;

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CThresholdPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CThresholdPreferenceFunction::~CThresholdPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CThresholdPreferenceFunction::~CThresholdPreferenceFunction() {
}
