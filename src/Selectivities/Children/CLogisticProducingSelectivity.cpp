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
#include "../../Helpers/CError.h"

//**********************************************************************
// CLogisticproducingSelectivity::CLogisticProducingSelectivity(CLogisticProducingSelectivity *Selectivity = 0)
// Default Constructor
//**********************************************************************
CLogisticProducingSelectivity::CLogisticProducingSelectivity(CLogisticProducingSelectivity *Selectivity)
: CSelectivity(Selectivity) {

  // Vars
  iL      = -1;
  iH      = -1;
  dA50    = 0.0;
  dAto95  = 0.0;

  registerEstimable(PARAM_A50, &dA50);
  registerEstimable(PARAM_ATO95, &dAto95);

  // Copy Construct
  if (Selectivity != 0) {
    iL      = Selectivity->getL();
    iH      = Selectivity->getH();
    dA50    = Selectivity->getA50();
    dAto95  = Selectivity->getAto95();
  }
}

//**********************************************************************
// void CLogisticProducingSelectivity::validate()
// validate
//**********************************************************************
void CLogisticProducingSelectivity::validate() {
  try {
    if (iL < pConfig->getMinAge())
      CError::errorLessThan(PARAM_L, PARAM_MIN_AGE);
    if (iH > pConfig->getMaxAge())
      CError::errorGreaterThan(PARAM_H, PARAM_MAX_AGE);
    if (iL == -1)
      CError::errorMissing(PARAM_L);
    if (iH == -1)
      CError::errorMissing(PARAM_H);

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
