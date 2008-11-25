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
#include "../Layers/CNumericLayer.h"

//**********************************************************************
// CThresholdDirectedProcess::CThresholdDirectedProcess()
// Default Constructor
//**********************************************************************
CThresholdDirectedProcess::CThresholdDirectedProcess(CThresholdDirectedProcess *Process)
: CDirectedProcess(Process) {
  // Variables
  dN       = -1.0;
  dLambda  = -1.0;
  sType    = PARAM_THRESHOLD;

  registerEstimable(PARAM_N, &dN);
  registerEstimable(PARAM_LAMBDA, &dLambda);

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

    // Local Validation
    if (isSame(dN, -1.0))
      errorMissing(PARAM_N);
    if (isSame(dLambda, -1.0))
      errorMissing(PARAM_LAMBDA);

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
  return zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CThresholdDirectedProcess::~CThresholdDirectedProcess()
// Default De-Constructor
//**********************************************************************
CThresholdDirectedProcess::~CThresholdDirectedProcess() {
}
