//============================================================================
// Name        : CIncreasingSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CIncreasingSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"
//**********************************************************************
// CIncreasingSelectivity::CIncreasingSelectivity()
// Default constructor
//**********************************************************************
CIncreasingSelectivity::CIncreasingSelectivity() {
  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_L);
  pParameterList->registerAllowed(PARAM_H);
  pParameterList->registerAllowed(PARAM_V);
  pParameterList->registerAllowed(PARAM_ALPHA);

}

//**********************************************************************
// void CIncreasingSelectivity::validate()
// Validate the selectivity
//**********************************************************************
void CIncreasingSelectivity::validate() {
  try {
    // Base
    CSelectivity::validate();

    // Get our values
    iL     = pParameterList->getInt(PARAM_L);
    iH     = pParameterList->getInt(PARAM_H);
    dAlpha = pParameterList->getDouble(PARAM_H,true,1.0);

    pParameterList->fillVector(vVs, PARAM_V);

    // TODO: Complete validation - error messages need to be better phrased
    if (dAlpha <= 0)
      CError::errorLessThanEqualTo(PARAM_ALPHA, PARAM_ZERO);
    if (iL < pWorld->getMinAge())
      CError::errorLessThan(PARAM_L, PARAM_MIN_AGE);
    if (iL > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_L, PARAM_MAX_AGE);
    if (iH <= iL)
      CError::errorLessThanEqualTo(PARAM_H, PARAM_L);
    if ((int)vVs.size() != (iH - iL + 1))
       throw string("You need to supply the correct number of entries for V"); //TODO: Better error message
    for (int i = 0; i < (int)vVs.size(); ++i) {
      if ((vVs[i] > 1.0) || (vVs[i] < 0.0))
        throw string("Vs should be be between 0 and 1"); //TODO: Better error message
    }

    // Register Estimables
    for (int i = 0; i < (int)vVs.size(); ++i)
      registerEstimable(PARAM_V, i, &vVs[i]);

  } catch (string Ex) {
    Ex = "CIncreasingSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CIncreasingSelectivity::getResult(int Index)
// Get the result from the selectivity
//**********************************************************************
double CIncreasingSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet = 0.0;

    if (Age <= iL) {
      dRet = 0.0;
    } else if (Age > iH) {
      dRet = vVs[iH - iL];
    } else {
      dRet = vVs[0];
      for (int i=(iL+1); i < Age; i++) {
        if (i > iH || dRet >= dAlpha) break;
        dRet += (dAlpha-dRet) * vVs[i - iL];
      }
    }
    return dRet;

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CIncreasingSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0;
#endif
}

//**********************************************************************
// CIncreasingSelectivity::~CIncreasingSelectivity()
// Destructor
//**********************************************************************
CIncreasingSelectivity::~CIncreasingSelectivity() {
}
