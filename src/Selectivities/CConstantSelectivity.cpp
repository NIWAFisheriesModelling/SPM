//============================================================================
// Name        : CConstantSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 6/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CConstantSelectivity.h"

//**********************************************************************
// CConstantSelectivity::CConstantSelectivity(CConstantSelectivity *Selectivity = 0)
// Default Constructor
//**********************************************************************
CConstantSelectivity::CConstantSelectivity(CConstantSelectivity *Selectivity)
: CSelectivity(Selectivity) {

  // Variabes
  dC        = -1.0;

  registerEstimable(PARAM_C, &dC);

  // Copy Construct
  if (Selectivity != 0) {
    dC    = Selectivity->getC();
  }
}

//**********************************************************************
// void CConstantSelectivity::validate()
// validate
//**********************************************************************
void CConstantSelectivity::validate() {
  try {
    // Nothing To do
  } catch (string Ex) {
    Ex = "CConstantSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CConstantSelectivity::calculateResult(int Age)
// Calculate our Results
//**********************************************************************
double CConstantSelectivity::calculateResult(int Age) {
  try {
    throw string(ERROR_SUPPORTED_FUNCTION);
  } catch (string Ex) {
    Ex = "CConstantSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CConstantSelectivity::getResult(int Index)
// get Result
//**********************************************************************
double CConstantSelectivity::getResult(int Index) {
#ifndef OPTIMISE
  try {
#endif
    return dC;

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CConstantSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CConstantSelectivity::~CConstantSelectivity()
// Default De-Constructor
//**********************************************************************
CConstantSelectivity::~CConstantSelectivity() {
}
