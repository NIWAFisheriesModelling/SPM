//============================================================================
// Name        : CNormalDirectedProcess.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNormalDirectedProcess.h"
#include "../Layers/CNumericLayer.h"

//**********************************************************************
// CNormalDirectedProcess::CNormalDirectedProcess()
// Default Constructor
//**********************************************************************
CNormalDirectedProcess::CNormalDirectedProcess(CNormalDirectedProcess *Process)
: CDirectedProcess(Process) {

  // Vars
  dMu     = -1.0;
  dSigma  = -1.0;
  sType   = PARAM_NORMAL;

  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Copy Constructor
  if (Process != 0) {
    dMu     = Process->getMu();
    dSigma  = Process->getSigma();
  }
}

//**********************************************************************
// void CNormalDirectedProcess::validate()
// Validate
//**********************************************************************
void CNormalDirectedProcess::validate() {
  try {
    // Base Validation
    CDirectedProcess::validate();

    // Local
    if (isSame(dMu, -1.0))
      errorMissing(PARAM_MU);
    if (isSame(dSigma, -1.0))
      errorMissing(PARAM_SIGMA);

  } catch (string Ex) {
    Ex = "CNormalDirectedProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CNormalDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMISE
  try {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    dRet = pow(2.0,-((dLayerValue-dMu)/dSigma * (dLayerValue-dMu)/dSigma));

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CNormalDirectedProcess.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  //return (dAlpha * dRet);
  return zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CNormalDirectedProcess::~CNormalDirectedProcess()
// Default De-Constructor
//**********************************************************************
CNormalDirectedProcess::~CNormalDirectedProcess() {
}
