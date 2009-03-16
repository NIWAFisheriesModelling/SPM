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
CDoubleExponentialSelectivity::CDoubleExponentialSelectivity() {
  // Register estimables
  registerEstimable(PARAM_X0, &dX0);
  registerEstimable(PARAM_Y0, &dY0);
  registerEstimable(PARAM_Y1, &dY1);
  registerEstimable(PARAM_Y2, &dY2);
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_X0);
  pParameterList->registerAllowed(PARAM_X1);
  pParameterList->registerAllowed(PARAM_X2);
  pParameterList->registerAllowed(PARAM_Y0);
  pParameterList->registerAllowed(PARAM_Y1);
  pParameterList->registerAllowed(PARAM_Y2);
  pParameterList->registerAllowed(PARAM_ALPHA);
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
    dX0    = pParameterList->getDouble(PARAM_X0);
    dX1    = pParameterList->getDouble(PARAM_X1);
    dX2    = pParameterList->getDouble(PARAM_X2);
    dY0    = pParameterList->getDouble(PARAM_Y0);
    dY1    = pParameterList->getDouble(PARAM_Y1);
    dY2    = pParameterList->getDouble(PARAM_Y2);
    dAlpha    = pParameterList->getDouble(PARAM_ALPHA,true,1.0);

    if (dAlpha <= 0)
      throw("Alpha must be positive"); // TODO: better error messages
    if (dX1 >= dX0)
      throw("x0 must be defined so that x1 < x0 < x2"); // TODO: better error messages
    if (dX0 >= dX1)
      throw("x0 must be defined so that x1 < x0 < x2"); // TODO: better error messages
    if (dX0 >= dX1)
      throw("x0 must be defined so that x1 < x0 < x2"); // TODO: better error messages

    if (dY0 < 0 || dY1 < 0 || dY2 < 0)
      throw("y0, y1, and y2 must be positive numbers"); // TODO: better error messages

  } catch (string Ex) {
    Ex = "CDoubleExponentialSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDoubleExponentialSelectivity::getResult(int Index)
// Get the result from our selectivity
//**********************************************************************
double CDoubleExponentialSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif

  double dRet = 0.0;

  if(Age <= dX0)
    dRet = dY0 * pow((dY1 / dY0), ((double)Age - dX0)/(dX1 - dX0)) * dAlpha; //TODO: validate equation... haven't checked to see if it works with a dAlpha parameter
  else
    dRet = dY0 * pow((dY2 / dY0), ((double)Age - dX0)/(dX2 - dX0)) * dAlpha; //TODO: validate equation... haven't checked to see if it works with a dAlpha parameter

  return dRet;

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CDoubleExponentialSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CDoubleExponentialSelectivity::~CDoubleExponentialSelectivity()
// Destructor
//**********************************************************************
CDoubleExponentialSelectivity::~CDoubleExponentialSelectivity() {
  // TODO Auto-generated destructor stub
}
