//============================================================================
// Name        : CLogisticPreferenceFunction.cpp
// Author      : A.Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CLogisticPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CLogisticPreferenceFunction::CLogisticPreferenceFunction()
// Default Constructor
//**********************************************************************
CLogisticPreferenceFunction::CLogisticPreferenceFunction() {
  // Register estimable parameters
  registerEstimable(PARAM_A50, &dA50);
  registerEstimable(PARAM_ATO95, &dAto95);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_A50);
  pParameterList->registerAllowed(PARAM_ATO95);
}

//**********************************************************************
// void CLogisticPreferenceFunction::validate()
// Validate
//**********************************************************************
void CLogisticPreferenceFunction::validate() {
  try {
    // Base
    CPreferenceFunction::validate();

    // Local
    dA50    = pParameterList->getDouble(PARAM_A50);
    dAto95  = pParameterList->getDouble(PARAM_ATO95);

  } catch (string &Ex) {
    Ex = "CLogisticPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLogisticPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CLogisticPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet= 0.0;

#ifndef OPTIMIZE
  try {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    double dTemp = (dA50-dLayerValue)/dAto95;

    if(dTemp > 5.0)
      dRet = 0.0;
    else if (dTemp < -5.0)
      dRet = 1.0;
    else
      dRet  = 1.0/(1.0+pow(19.0,dTemp));

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CLogisticPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}

//**********************************************************************
// CLogisticPreferenceFunction::~CLogisticPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CLogisticPreferenceFunction::~CLogisticPreferenceFunction() {
}
