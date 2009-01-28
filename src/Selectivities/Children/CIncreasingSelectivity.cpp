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

//**********************************************************************
// CIncreasingSelectivity::CIncreasingSelectivity()
// Default constructor
//**********************************************************************
CIncreasingSelectivity::CIncreasingSelectivity() {
  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_L);
  pParameterList->registerAllowed(PARAM_H);
  pParameterList->registerAllowed(PARAM_V);
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
    dL    = pParameterList->getDouble(PARAM_L);
    dH    = pParameterList->getDouble(PARAM_H);

    pParameterList->fillVector(vVs, PARAM_V);

    // TODO: Complete validation

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
double CIncreasingSelectivity::getResult(int Index) {
  try {
    throw string("Not yet implemented");
  } catch (string Ex) {
    Ex = "CIncreasingSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// CIncreasingSelectivity::~CIncreasingSelectivity()
// Destructor
//**********************************************************************
CIncreasingSelectivity::~CIncreasingSelectivity() {
}
