//============================================================================
// Name        : CAllValuesBoundedSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAllValuesBoundedSelectivity.h"

//**********************************************************************
// CAllValuesBoundedSelectivity::CAllValuesBoundedSelectivity()
// Default Constructor
//**********************************************************************
CAllValuesBoundedSelectivity::CAllValuesBoundedSelectivity() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_L);
  pParameterList->registerAllowed(PARAM_H);
  pParameterList->registerAllowed(PARAM_V);
}

//**********************************************************************
// void CAllValuesBoundedSelectivity::validate()
// Validate the selectivity
//**********************************************************************
void CAllValuesBoundedSelectivity::validate() {
  try {
    // Base
    CSelectivity::validate();

    // Get our variables
    iL      = pParameterList->getInt(PARAM_L);
    iH      = pParameterList->getInt(PARAM_H);

    pParameterList->fillVector(vVs, PARAM_V);

    // TODO: Complete validation - error messages need to be better phrased
    if (iL < pWorld->getMinAge())
      throw("L needs to be a value at least the same as the minimum age in the model"); //TODO: Better error message
    if (iL > pWorld->getMaxAge())
      throw("L cannot be larger that the maximum age in the model"); //TODO: Better error message
    if (iH <= iL)
       throw("L must be less than H"); //TODO: Better error message
    if ((int)vVs.size() != (iH - iL))
       throw("You need to supply the correct number of entries for V"); //TODO: Better error message

    // Register our vector as estimable
    for (int i = 0; i < (int)vVs.size(); ++i)
      registerEstimable(PARAM_V, i, &vVs[i]);

  } catch (string Ex) {
    Ex = "CAllValuesBoundedSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CAllValuesBoundedSelectivity::calculateResult(int Index)
// Get the result from our Selectivity
//**********************************************************************
double CAllValuesBoundedSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet = 0.0;
    if (Age <= iL)
      dRet = 0.0;
    else if (Age >= iH)
      dRet = vVs[iH - iL - 1];
    else
      dRet = vVs[Age - iL - 1];

    return dRet;

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CAllValuesBoundedSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CAllValuesBoundedSelectivity::~CAllValuesBoundedSelectivity()
// Destructor
//**********************************************************************
CAllValuesBoundedSelectivity::~CAllValuesBoundedSelectivity() {
}
