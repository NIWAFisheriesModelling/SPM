//============================================================================
// Name        : CExponentialDirectedProcess.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CExponentialDirectedProcess.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CExponentialDirectedProcess::CExponentialDirectedProcess()
// Default Constructor
//**********************************************************************
CExponentialDirectedProcess::CExponentialDirectedProcess(CExponentialDirectedProcess *Process)
: CDirectedProcess(Process) {

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
// void CExponentialDirectedProcess::validate()
// Validate
//**********************************************************************
void CExponentialDirectedProcess::validate() {
  try {
    // Base
    CDirectedProcess::validate();

    // Assign Variables
    dLambda = pParameterList->getDouble(PARAM_LAMBDA);

  } catch (string Ex) {
    Ex = "CExponentialDirectedProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CExponentialDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CExponentialDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
#ifndef OPTIMISE
  try {
#endif

    return CMath::zeroFun(pow(exp(-dLambda * pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex)),dAlpha),ZERO);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CExponentialDirectedProcess.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}
//**********************************************************************
// CExponentialDirectedProcess::~CExponentialDirectedProcess()
// Default De-Constructor
//**********************************************************************
CExponentialDirectedProcess::~CExponentialDirectedProcess() {
}
