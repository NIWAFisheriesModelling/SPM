//============================================================================
// Name        : CExponentialPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#include <iostream>

// Local Headers
#include "CExponentialPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CExponentialPreferenceFunction::CExponentialPreferenceFunction()
// Default Constructor
//**********************************************************************
CExponentialPreferenceFunction::CExponentialPreferenceFunction() {

  // Vars
  dLambda     = -1.0;

  // Register Estimable
  registerEstimable(PARAM_LAMBDA, &dLambda);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_LAMBDA);

}

//**********************************************************************
// void CExponentialPreferenceFunction::validate()
// Validate
//**********************************************************************
void CExponentialPreferenceFunction::validate() {
  try {

    // Assign Variables
    dLambda = pParameterList->getDouble(PARAM_LAMBDA);

    // Validate parent
    CPreferenceFunction::validate();

    //Local validation
    if (dLambda <= 0.0)
      CError::errorLessThanEqualTo(PARAM_LAMBDA, PARAM_ZERO);

  } catch (string &Ex) {
    Ex = "CExponentialPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CExponentialPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CExponentialPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
#ifndef OPTIMIZE
  try {
#endif

    return CMath::zeroFun(pow(exp(-dLambda * pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex)),dAlpha),ZERO);

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CExponentialPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}
//**********************************************************************
// CExponentialPreferenceFunction::~CExponentialPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CExponentialPreferenceFunction::~CExponentialPreferenceFunction() {
}
