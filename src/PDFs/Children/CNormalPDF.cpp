//============================================================================
// Name        : CNormalPDF.cpp
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science ©2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CNormalPDF.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CNormalPDF::CNormalPDF()
// Default Constructor
//**********************************************************************
CNormalPDF::CNormalPDF() {

  sType = PARAM_NORMAL;

  // Register Estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
}

//**********************************************************************
// void CNormalPDF::validate()
// Validate
//**********************************************************************
void CNormalPDF::validate() {
  try {

    // Assign our variables
    dMu       = pParameterList->getDouble(PARAM_MU);
    dSigma    = pParameterList->getDouble(PARAM_SIGMA);

    // Validate parent
    CPDF::validate();

    //Local validation
    if (dSigma <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA, PARAM_ZERO);

  } catch (string &Ex) {
    Ex = "CNormalPDF.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalPDF::getPDFResult(double Value)
// get Result
//**********************************************************************
double CNormalPDF::getPDFResult(double value) {
// not required ?

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    dRet = pow(2.0,-((value-dMu)/dSigma * (value-dMu)/dSigma));

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CNormalPDF.getPDFResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// double CNormalPDF::getCDFResult(double Value)
// get Result
//**********************************************************************
double CNormalPDF::getCDFResult(double value) {
// not required ?

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    dRet = pow(2.0,-((value-dMu)/dSigma * (value-dMu)/dSigma));

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CNormalCDF.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}
//**********************************************************************
// CNormalPDF::~CNormalPDF()
// Default De-Constructor
//**********************************************************************
CNormalPDF::~CNormalPDF() {
}
