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
// CConstantSelectivity::CConstantSelectivity()
// Default Constructor
//**********************************************************************
CConstantSelectivity::CConstantSelectivity() {
  // Register estimable
  registerEstimable(PARAM_C, &dC);

  // Register user allowed parameter
  pParameterList->registerAllowed(PARAM_C);
}

//**********************************************************************
// void CConstantSelectivity::validate()
// validate
//**********************************************************************
void CConstantSelectivity::validate() {
  try {
    // Base validation
    CSelectivity::validate();

    // Populate our variables
    dC = pParameterList->getDouble(PARAM_C);

  } catch (string Ex) {
    Ex = "CConstantSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CConstantSelectivity::getResult(int Index)
// get Result
//**********************************************************************
double CConstantSelectivity::getResult(int Index) {
#ifndef OPTIMIZE
  try {
    if ((Index+pWorld->getMinAge()) > pWorld->getMaxAge())
      throw string("index too high"); // TODO Add CERror
  } catch (string Ex) {
    Ex = "CConstantSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dC;
}

//**********************************************************************
// CConstantSelectivity::~CConstantSelectivity()
// Default De-Constructor
//**********************************************************************
CConstantSelectivity::~CConstantSelectivity() {
}
