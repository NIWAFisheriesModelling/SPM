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
    dL      = pParameterList->getDouble(PARAM_L);
    dH      = pParameterList->getDouble(PARAM_H);

    pParameterList->fillVector(vVs, PARAM_V);

    // TODO: Complete validation

    // Register our vector as estimable
    for (int i = 0; i < (int)vVs.size(); ++i)
      registerEstimable(PARAM_V, i, &vVs[i]);

  } catch (string Ex) {
    Ex = "CAllValuesBoundedSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CAllValuesBoundedSelectivity::getResult(int Index)
// Get the result from our Selectivity
//**********************************************************************
double CAllValuesBoundedSelectivity::getResult(int Index) {
  try {
    throw string("Not yet implemented");

  } catch (string Ex) {
    Ex = "CAllValuesBoundedSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// CAllValuesBoundedSelectivity::~CAllValuesBoundedSelectivity()
// Destructor
//**********************************************************************
CAllValuesBoundedSelectivity::~CAllValuesBoundedSelectivity() {
}
