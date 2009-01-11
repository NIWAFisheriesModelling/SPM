//============================================================================
// Name        : CThresholdDirectedProcess.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CThresholdDirectedProcess.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CThresholdDirectedProcess::CThresholdDirectedProcess()
// Default Constructor
//**********************************************************************
CThresholdDirectedProcess::CThresholdDirectedProcess(CThresholdDirectedProcess *Process)
: CDirectedProcess(Process) {
  // Variables
  dN       = -1.0;
  dLambda  = -1.0;

  // Register estimables
  registerEstimable(PARAM_N, &dN);
  registerEstimable(PARAM_LAMBDA, &dLambda);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_N);
  pParameterList->registerAllowed(PARAM_LAMBDA);

  // Copy Part of the Constructor
  if (Process != 0) {
    dN       = Process->getN();
    dLambda  = Process->getLambda();
  }
}

//**********************************************************************
// void CThresholdDirectedProcess::validate()
// Validate
//**********************************************************************
void CThresholdDirectedProcess::validate() {
  try {
    // Base Validation
    CDirectedProcess::validate();

    // Assign local variables
    dN        = pParameterList->getDouble(PARAM_N);
    dLambda   = pParameterList->getDouble(PARAM_LAMBDA);

  } catch (string Ex) {
    Ex = "CThresholdDirectedProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CThresholdDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CThresholdDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMISE
  try {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    if (dLayerValue > dN)
      dRet = 1.0/(pow(dLayerValue/dN,dLambda));
    else
      dRet = 1.0;

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CThresholdDirectedProcess.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  //return (dAlpha * dRet);
  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CThresholdDirectedProcess::~CThresholdDirectedProcess()
// Default De-Constructor
//**********************************************************************
CThresholdDirectedProcess::~CThresholdDirectedProcess() {
}
