//============================================================================
// Name        : CLogisticDirectedProcess.cpp
// Author      : A.Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CLogisticDirectedProcess.h"
#include "../Layers/CNumericLayer.h"

//**********************************************************************
// CLogisticDirectedProcess::CLogisticDirectedProcess()
// Default Constructor
//**********************************************************************
CLogisticDirectedProcess::CLogisticDirectedProcess(CLogisticDirectedProcess *Process)
: CDirectedProcess(Process) {

  // Variables
  dA50          = -1.0;
  dAto95        = -1.0;
  sType         = PARAM_LOGISTIC;

  registerEstimable(PARAM_A50, &dA50);
  registerEstimable(PARAM_ATO95, &dAto95);

  // Copy Construct
  if (Process != 0) {
    dA50    = Process->getA50();
    dAto95  = Process->getAto95();
  }
}

//**********************************************************************
// void CLogisticDirectedProcess::validate()
// Validate
//**********************************************************************
void CLogisticDirectedProcess::validate() {
  try {
    // Base
    CDirectedProcess::validate();

    // Local
    if (isSame(dA50, -1.0))
      errorMissing(PARAM_A50);
    if (isSame(dAto95, -1.0))
      errorMissing(PARAM_ATO95);

  } catch (string Ex) {
    Ex = "CLogisticDirectedProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLogisticDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CLogisticDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet= 0.0;

#ifndef OPTIMISE
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

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CLogisticDirectedProcess.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  //return (dAlpha * dRet);
  return zeroFun(pow(dRet,dAlpha),ZERO);
}

//**********************************************************************
// CLogisticDirectedProcess::~CLogisticDirectedProcess()
// Default De-Constructor
//**********************************************************************
CLogisticDirectedProcess::~CLogisticDirectedProcess() {
}
