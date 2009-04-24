//============================================================================
// Name        : CAllValuesBoundedSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "CAllValuesBoundedSelectivity.h"

// Usong
using std::cout;
using std::endl;

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

    iMinAge = pWorld->getMinAge();

  } catch (string Ex) {
    Ex = "CAllValuesBoundedSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CAllValuesBoundedSelectivity::calculateResult(int Age)
// Calculate a cached result for this selectivity
//**********************************************************************
double CAllValuesBoundedSelectivity::calculateResult(int Age) {

  double dRet = 0.0;

  if ( Age < iL)
    dRet = 0.0;
  else  if ( Age >= iH)
    dRet = vVs[vVs.size() - 1];
  else
    dRet = vVs[(Age-iL)];

  return dRet;
}

//**********************************************************************
// CAllValuesBoundedSelectivity::~CAllValuesBoundedSelectivity()
// Destructor
//**********************************************************************
CAllValuesBoundedSelectivity::~CAllValuesBoundedSelectivity() {
}
