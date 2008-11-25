//============================================================================
// Name        : CDoubleNormalDirectedProcess.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CDoubleNormalDirectedProcess.h"
#include "../Layers/CNumericLayer.h"

//**********************************************************************
// CDoubleNormalDirectedProcess::CDoubleNormalDirectedProcess()
// Default Constructor
//**********************************************************************
CDoubleNormalDirectedProcess::CDoubleNormalDirectedProcess(CDoubleNormalDirectedProcess *Process)
: CDirectedProcess(Process) {

  // Variables
  dSigmaL       = -1.0;
  dSigmaR       = -1.0;
  dMu           = -1.0;
  sType         = PARAM_DOUBLE_NORMAL;

  // Register our Estimables
  registerEstimable(PARAM_SIGMA_L, &dSigmaL);
  registerEstimable(PARAM_SIGMA_R, &dSigmaR);
  registerEstimable(PARAM_MU, &dMu);

  // Copy Construct
  if (Process != 0) {
    dSigmaL   = Process->getSigmaL();
    dSigmaR   = Process->getSigmaR();
    dMu       = Process->getMu();
  }
}

//**********************************************************************
// void CDoubleNormalDirectedProcess::validate()
// Validate
//**********************************************************************
void CDoubleNormalDirectedProcess::validate() {
  try {
    // Base
    CDirectedProcess::validate();

    // Local
    if (isSame(dMu, -1.0))
      errorMissing(PARAM_MU);

  } catch (string Ex) {
    Ex = "CDoubleNormalDirectedProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDoubleNormalDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CDoubleNormalDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
  dRet= 0.0;
#ifndef OPTIMISE
  try {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    if (dLayerValue < dMu)
      dRet = pow(2.0,-((dLayerValue-dMu)/dSigmaL * (dLayerValue-dMu)/dSigmaL));
    else
      dRet = pow(2.0,-((dLayerValue-dMu)/dSigmaR * (dLayerValue-dMu)/dSigmaR));

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CDoubleNormalDirectedProcess.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return zeroFun(pow(dRet,dAlpha),ZERO);
}

//**********************************************************************
// CDoubleNormalDirectedProcess::~CDoubleNormalDirectedProcess()
// Default De-Constructor
//**********************************************************************
CDoubleNormalDirectedProcess::~CDoubleNormalDirectedProcess() {
}
