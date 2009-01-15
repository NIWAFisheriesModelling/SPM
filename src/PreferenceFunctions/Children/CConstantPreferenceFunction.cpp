//============================================================================
// Name        : CConstantPreferenceFunction.cpp
// Author      : A.Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CConstantPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CConstantPreferenceFunction::CConstantPreferenceFunction()
// Default Constructor
//**********************************************************************
CConstantPreferenceFunction::CConstantPreferenceFunction(CConstantPreferenceFunction *Process)
: CPreferenceFunction(Process) {
}

//**********************************************************************
// void CConstantPreferenceFunction::validate()
// Validate
//**********************************************************************
void CConstantPreferenceFunction::validate() {
  try {
    // Base Val
    CPreferenceFunction::validate();

  } catch (string Ex) {
    Ex = "CConstantPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CConstantPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CConstantPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
#ifndef OPTIMISE
  try {
#endif

    dRet = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CConstantPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  //return dAlpha * dRet;
  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}

//**********************************************************************
// CConstantPreferenceFunction::~CConstantPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CConstantPreferenceFunction::~CConstantPreferenceFunction() {
}
