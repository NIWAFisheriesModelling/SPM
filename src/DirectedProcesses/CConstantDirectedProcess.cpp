//============================================================================
// Name        : CConstantDirectedProcess.cpp
// Author      : A.Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CConstantDirectedProcess.h"
#include "../Layers/CNumericLayer.h"

//**********************************************************************
// CConstantDirectedProcess::CConstantDirectedProcess()
// Default Constructor
//**********************************************************************
CConstantDirectedProcess::CConstantDirectedProcess(CConstantDirectedProcess *Process)
: CDirectedProcess(Process) {

  sType = PARAM_CONSTANT;
}

//**********************************************************************
// void CConstantDirectedProcess::validate()
// Validate
//**********************************************************************
void CConstantDirectedProcess::validate() {
  try {
    // Base Val
    CDirectedProcess::validate();

  } catch (string Ex) {
    Ex = "CConstantDirectedProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CConstantDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CConstantDirectedProcess::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
#ifndef OPTIMISE
  try {
#endif

    dRet = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CConstantDirectedProcess.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  //return dAlpha * dRet;
  return zeroFun(pow(dRet,dAlpha),ZERO);
}

//**********************************************************************
// CConstantDirectedProcess::~CConstantDirectedProcess()
// Default De-Constructor
//**********************************************************************
CConstantDirectedProcess::~CConstantDirectedProcess() {
}
