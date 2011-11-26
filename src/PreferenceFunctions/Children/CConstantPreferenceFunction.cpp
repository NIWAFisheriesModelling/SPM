//============================================================================
// Name        : CConstantPreferenceFunction.cpp
// Author      : A.Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "CConstantPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CComparer.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CConstantPreferenceFunction::CConstantPreferenceFunction()
// Default Constructor
//**********************************************************************
CConstantPreferenceFunction::CConstantPreferenceFunction() {
}

//**********************************************************************
// double CConstantPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CConstantPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
#ifndef OPTIMIZE
  try {
#endif

    dRet = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);

#ifndef OPTIMIZE
  } catch (string &Ex) {
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
