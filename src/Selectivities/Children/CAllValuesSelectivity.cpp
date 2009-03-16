//============================================================================
// Name        : CAllValuesSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAllValuesSelectivity.h"

//**********************************************************************
// CAllValuesSelectivity::CAllValuesSelectivity()
// Default constructor
//**********************************************************************
CAllValuesSelectivity::CAllValuesSelectivity() {
  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_V);
}

//**********************************************************************
// void CAllValuesSelectivity::validate()
// Validate the selectivity
//**********************************************************************
void CAllValuesSelectivity::validate() {
  try {
    // Base
    CSelectivity::validate();

    // Fill our vector
    pParameterList->fillVector(vVs, PARAM_V);

    // TODO: Complete validation
    if ((int)vVs.size() !=  (pWorld->getMaxAge() - pWorld->getMinAge()))
      throw string("Too many/not enough values in V. Supply exactly one value of V for every age classs in the model"); // TODO ADD CError

    // Register the Vs as estimable
    for (int i = 0; i < (int)vVs.size(); ++i)
      registerEstimable(PARAM_V, i, &vVs[i]);

  } catch (string Ex) {
    Ex = "CAllValuesSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CAllValuesSelectivity::getResult(int Index)
// Get the result from our selectivity
//**********************************************************************
double CAllValuesSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet = 0.0;
    dRet = vVs[Age - pWorld->getMinAge() - 1];
    return dRet;

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CAllValuesSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CAllValuesSelectivity::~CAllValuesSelectivity()
// Destructor
//**********************************************************************
CAllValuesSelectivity::~CAllValuesSelectivity() {
}
