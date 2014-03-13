//============================================================================
// Name        : CSplineSelectivity.cpp
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science ©2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CSplineSelectivity.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CLogisticproducingSelectivity::CSplineSelectivity()
// Default Constructor
//**********************************************************************
CSplineSelectivity::CSplineSelectivity() {

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_KNOTS);
  pParameterList->registerAllowed(PARAM_VALUES);
  pParameterList->registerAllowed(PARAM_METHOD);

}

//**********************************************************************
// void CSplineSelectivity::validate()
// validate
//**********************************************************************
void CSplineSelectivity::validate() {
  try {

    // Populate our variables
    pParameterList->fillVector(vKnots, PARAM_KNOTS);
    pParameterList->fillVector(vValues, PARAM_VALUES);
    sMethod = pParameterList->getString(PARAM_METHOD,true,PARAM_NATURAL);

    // Validate parent
    CSelectivity::validate();

    // Useful parameters
    iN = vKnots.size();

    // Local validation
    if (vKnots.size() != vValues.size())
      CError::errorListSameSize(PARAM_KNOTS, PARAM_VALUES);
    if (iN < 2)
      CError::errorNotEnough(PARAM_KNOTS);


    if(sMethod==PARAM_NATURAL) {
      //A "natural spline" where the second derivatives are set to 0 at the boundaries
      spline.setLowBC(Spline::FIXED_2ND_DERIV_BC, 0);
      spline.setHighBC(Spline::FIXED_2ND_DERIV_BC, 0);
    } else if(sMethod==PARAM_FIXED) {
      //A spline with a fixed first derivative at the boundaries
      spline.setLowBC(Spline::FIXED_1ST_DERIV_BC, 0);
      spline.setHighBC(Spline::FIXED_1ST_DERIV_BC, 0);
    } else if(sMethod==PARAM_PARABOLA) {
      //A spline which turns into a parabola at the boundaries
      spline.setLowBC(Spline::PARABOLIC_RUNOUT_BC);
      spline.setHighBC(Spline::PARABOLIC_RUNOUT_BC);
    } else {
      CError::errorUnknown(PARAM_METHOD, sMethod);
    }

  } catch (string &Ex) {
    Ex = "CSplineSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCachedSelectivity::rebuild()
// Rebuild the selectivity
//**********************************************************************
void CSplineSelectivity::rebuild() {
  try {

    for (int i=0; i < iN; ++i) {
      spline.addPoint(vKnots[i],vValues[i]);
    }

    CCachedSelectivity::rebuild();

  } catch (string &Ex) {
    Ex = "CCachedSelectivity.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CSplineSelectivity::calculateResult(int Age)
// Calculate Our Result
//**********************************************************************
double CSplineSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
    // Do our function
#endif

  return ( spline((double)Age) );

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CSplineSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CSplineSelectivity::~CSplineSelectivity()
// Default De-Constructor
//**********************************************************************
CSplineSelectivity::~CSplineSelectivity() {
}
