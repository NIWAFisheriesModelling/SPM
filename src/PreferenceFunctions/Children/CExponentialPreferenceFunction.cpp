//============================================================================
// Name        : CExponentialPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CExponentialPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CExponentialPreferenceFunction::CExponentialPreferenceFunction()
// Default Constructor
//**********************************************************************
CExponentialPreferenceFunction::CExponentialPreferenceFunction(CExponentialPreferenceFunction *Process)
: CPreferenceFunction(Process) {

  // Vars
  dLambda     = -1.0;

  // Register Estimable
  registerEstimable(PARAM_LAMBDA, &dLambda);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_LAMBDA);

  // Copy Construct
  if (Process != 0) {
    dLambda = Process->getLambda();
  }
}

//**********************************************************************
// void CExponentialPreferenceFunction::validate()
// Validate
//**********************************************************************
void CExponentialPreferenceFunction::validate() {
  try {
    // Base
    CPreferenceFunction::validate();

    // Assign Variables
    dLambda = pParameterList->getDouble(PARAM_LAMBDA);

  } catch (string Ex) {
    Ex = "CExponentialPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CExponentialPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CExponentialPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
#ifndef OPTIMISE
  try {
#endif

    return CMath::zeroFun(pow(exp(-dLambda * pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex)),dAlpha),ZERO);

#ifndef OPTIMISE
  } catch (string Ex) {
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
