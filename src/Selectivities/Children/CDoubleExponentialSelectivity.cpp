//============================================================================
// Name        : CDoubleExponentialSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CDoubleExponentialSelectivity.h"

//**********************************************************************
// CDoubleExponentialSelectivity::CDoubleExponentialSelectivity()
// Default constructor
//**********************************************************************
CDoubleExponentialSelectivity::CDoubleExponentialSelectivity(CDoubleExponentialSelectivity *Selectivity)
: CSelectivity(Selectivity) {

  // Register estimables
  registerEstimable(PARAM_X0, &dX0);
  registerEstimable(PARAM_Y0, &dY0);
  registerEstimable(PARAM_Y1, &dY1);
  registerEstimable(PARAM_Y2, &dY2);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_X0);
  pParameterList->registerAllowed(PARAM_X1);
  pParameterList->registerAllowed(PARAM_X2);
  pParameterList->registerAllowed(PARAM_Y0);
  pParameterList->registerAllowed(PARAM_Y1);
  pParameterList->registerAllowed(PARAM_Y2);
}

//**********************************************************************
// void CDoubleExponentialSelectivity::validate()
// Validate the selectivity
//**********************************************************************
void CDoubleExponentialSelectivity::validate() {
  try {
    // Base
    CSelectivity::validate();

    // Populate our parameters
    dX0   = pParameterList->getDouble(PARAM_X0);
    dX1   = pParameterList->getDouble(PARAM_X1);
    dX2   = pParameterList->getDouble(PARAM_X2);
    dY0   = pParameterList->getDouble(PARAM_Y0);
    dY1   = pParameterList->getDouble(PARAM_Y1);
    dY2   = pParameterList->getDouble(PARAM_Y2);

  } catch (string Ex) {
    Ex = "CDoubleExponentialSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDoubleExponentialSelectivity::getResult(int Index)
// Get the result from our selectivity
//**********************************************************************
double CDoubleExponentialSelectivity::getResult(int Index) {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CDoubleExponentialSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// CDoubleExponentialSelectivity::~CDoubleExponentialSelectivity()
// Destructor
//**********************************************************************
CDoubleExponentialSelectivity::~CDoubleExponentialSelectivity() {
  // TODO Auto-generated destructor stub
}
