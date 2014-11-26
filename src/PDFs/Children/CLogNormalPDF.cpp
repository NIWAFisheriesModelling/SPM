//============================================================================
// Name        : CLogNormalPDF.cpp
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science ©2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CLogNormalPDF.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/DefinedValues.h"

//**********************************************************************
// CLogNormalPDF::CLogNormalPDF()
// Default Constructor
//**********************************************************************
CLogNormalPDF::CLogNormalPDF() {

  sType = PARAM_LOGNORMAL;

  // Register Estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
}

//**********************************************************************
// void CLogNormalPDF::validate()
// Validate
//**********************************************************************
void CLogNormalPDF::validate() {
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
// double CLogNormalPDF::getPDFResult(double Value)
// get Result
//**********************************************************************
double CLogNormalPDF::getPDFResult(double value) {
// not required ?

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

  dRet = exp((-((log(value)-dMu) * (log(value)-dMu)))/(2.0*dSigma*dSigma)) / (value*dSigma*sqrt(TWO_PI));

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CLogNormalPDF.getPDFResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// double CLogNormalPDF::getCDFResult(double Value)
// get Result
//**********************************************************************
double CLogNormalPDF::getCDFResult(double value) {
// not required ?

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    double Z = (log(value) - dMu)/dSigma;
    dRet = exp(-(Z * Z))/sqrt(PI);

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CLogNormalPDF.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}
//**********************************************************************
// CLogNormalPDF::~CLogNormalPDF()
// Default De-Constructor
//**********************************************************************
CLogNormalPDF::~CLogNormalPDF() {
}
