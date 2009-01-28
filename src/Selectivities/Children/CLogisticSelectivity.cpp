//============================================================================
// Name        : CLogisticSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 6/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CLogisticSelectivity.h"

//**********************************************************************
// CLogisticSelectivity::CLogisticSelectivity()
// Default constructor
//**********************************************************************
CLogisticSelectivity::CLogisticSelectivity() {
  // Register Estimables
  registerEstimable(PARAM_A50, &dA50);
  registerEstimable(PARAM_ATO95, &dAto95);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_A50);
  pParameterList->registerAllowed(PARAM_ATO95);
}

//**********************************************************************
// void CLogisticSelectivity::validate()
// validate
//**********************************************************************
void CLogisticSelectivity::validate() {
  try {
    // Base
    CSelectivity::validate();

    // Populate our variables
    dA50    = pParameterList->getDouble(PARAM_A50);
    dAto95  = pParameterList->getDouble(PARAM_ATO95);

  } catch (string Ex) {
    Ex = "CLogisticSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLogisticSelectivity::calculateResult(int Age)
// Calculate a result for our Vector
//**********************************************************************
double CLogisticSelectivity::calculateResult(int Age) {
#ifndef OPTIMISE
  try {
#endif

    double dRet = 0.0;
    double dTemp = (dA50-Age)/dAto95;

    if(dTemp > 5.0)
      dRet = 0.0;
    else if (dTemp < -5.0)
      dRet = 1.0;
    else
      dRet  = 1.0/(1.0+pow(19.0,dTemp));

    return dRet;

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CLogisticSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CLogisticSelectivity::~CLogisticSelectivity()
// Default De-Constructor
//**********************************************************************
CLogisticSelectivity::~CLogisticSelectivity() {
}
