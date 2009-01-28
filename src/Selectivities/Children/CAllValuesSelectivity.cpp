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
double CAllValuesSelectivity::getResult(int Index) {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CAllValuesSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CAllValuesSelectivity::~CAllValuesSelectivity()
// Destructor
//**********************************************************************
CAllValuesSelectivity::~CAllValuesSelectivity() {
}
