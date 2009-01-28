//============================================================================
// Name        : CLogisticproducingSelectivity.cpp
// Author      : A. Dunn
// Date        : 7/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CLogisticProducingSelectivity.h"

//**********************************************************************
// CLogisticproducingSelectivity::CLogisticProducingSelectivity()
// Default Constructor
//**********************************************************************
CLogisticProducingSelectivity::CLogisticProducingSelectivity() {
  // Register estimables
  registerEstimable(PARAM_A50, &dA50);
  registerEstimable(PARAM_ATO95, &dAto95);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_L);
  pParameterList->registerAllowed(PARAM_H);
  pParameterList->registerAllowed(PARAM_A50);
  pParameterList->registerAllowed(PARAM_ATO95);
}

//**********************************************************************
// void CLogisticProducingSelectivity::validate()
// validate
//**********************************************************************
void CLogisticProducingSelectivity::validate() {
  try {
    // Base
    CSelectivity::validate();

    // Populate our variables
    iL      = pParameterList->getInt(PARAM_L);
    iH      = pParameterList->getInt(PARAM_H);
    dA50    = pParameterList->getDouble(PARAM_A50);
    dAto95  = pParameterList->getDouble(PARAM_ATO95);

  } catch (string Ex) {
    Ex = "CLogisticProducingSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLogisticProducingSelectivity::calculateResult(int Age)
// Calculate Our Result
//**********************************************************************
double CLogisticProducingSelectivity::calculateResult(int Age) {
#ifndef OPTIMISE
  try {
    // Do our logistic producing Function
#endif
    if (Age < iL)
      return 0.0;
    else if (Age >= iH)
      return 1.0;
    else if (Age == iL) {
      return 1.0/(1.0+pow(19.0,(dA50-Age)/dAto95));
    } else {
      double lambda2 = 1.0/(1.0+pow(19.0,(dA50-(Age-1))/dAto95));
      if (lambda2 > 0.9999)
        return 1;
      double lambda1 = 1.0/(1.0+pow(19.0,(dA50-Age)/dAto95));
      return (lambda1-lambda2)/(1-lambda2);
    }
    return 0.0;

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CLogisticProducingSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CLogisticProducingSelectivity::~CLogisticProducingSelectivity()
// Default De-Constructor
//**********************************************************************
CLogisticProducingSelectivity::~CLogisticProducingSelectivity() {
}
