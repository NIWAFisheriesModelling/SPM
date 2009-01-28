//============================================================================
// Name        : CNormalPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNormalPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CNormalPreferenceFunction::CNormalPreferenceFunction()
// Default Constructor
//**********************************************************************
CNormalPreferenceFunction::CNormalPreferenceFunction() {
  // Register Estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
}

//**********************************************************************
// void CNormalPreferenceFunction::validate()
// Validate
//**********************************************************************
void CNormalPreferenceFunction::validate() {
  try {
    // Base Validation
    CPreferenceFunction::validate();

    // Assign our variables
    dMu       = pParameterList->getDouble(PARAM_MU);
    dSigma    = pParameterList->getDouble(PARAM_SIGMA);

  } catch (string Ex) {
    Ex = "CNormalPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CNormalPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMISE
  try {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    dRet = pow(2.0,-((dLayerValue-dMu)/dSigma * (dLayerValue-dMu)/dSigma));

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CNormalPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  //return (dAlpha * dRet);
  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CNormalPreferenceFunction::~CNormalPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CNormalPreferenceFunction::~CNormalPreferenceFunction() {
}
