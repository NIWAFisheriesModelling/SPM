//============================================================================
// Name        : CProfile.cpp
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CProfile.h"
#include "../World/CWorld.h"
#include "../ParameterParser/CParamParser.h"
#include "../Estimates/CEstimateManager.h"
#include "../Estimates/CEstimate.h"
#include "../Helpers/CError.h"
#include "../Helpers/CComparer.h"

// TODO: Refactor variable names to full versions

//**********************************************************************
// CProfile::CProfile()
// Default Constructor
//**********************************************************************
CProfile::CProfile() {

  // Vars
  dN            = 0.0;
  dL            = 0.0;
  dU            = 0.0;
  dCurrent      = 0.0;
  sParameter    = "";
  pTarget       = 0;

  // Register Params
  pParameterList->registerAllowed(PARAM_LOWER_BOUND);
  pParameterList->registerAllowed(PARAM_UPPER_BOUND);
  pParameterList->registerAllowed(PARAM_N);
  pParameterList->registerAllowed(PARAM_PARAMETER);
}

//**********************************************************************
// bool CProfile::doStep()
// Do A Step
//**********************************************************************
bool CProfile::doStep() {
  try {
    // Increase Current Value
    if (CComparer::isZero(dCurrent) && (!CComparer::isZero(dL)))
      dCurrent = dL;
    else
      dCurrent += dN;

    // Check
    if (dCurrent > dU)
      return false; // Finished

    // Set Value
    pTarget->setValue(dCurrent);

  } catch (string Ex) {
    Ex = "CProfile.doStep(" + getParameter() + ")->" + Ex;
    throw Ex;
  }

  return true;
}

//**********************************************************************
// void CProfile::setEnabled(bool value)
// set Enabled
//**********************************************************************
void CProfile::setEnabled(bool value) {
  try {
    // If this is enabled, we want to disable the estimation
    // of our target
    pTarget->setEnabled(!value);
  } catch (string Ex) {
    Ex = "CProfile.setEnabled(" + getParameter() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProfile::validate()
// validate
//**********************************************************************
void CProfile::validate() {
  try {
    // Base
    CBaseBuild::validate();

    // Get our Parameters
    dL          = pParameterList->getDouble(PARAM_LOWER_BOUND);
    dU          = pParameterList->getDouble(PARAM_UPPER_BOUND);
    dN          = pParameterList->getDouble(PARAM_N);
    sParameter  = pParameterList->getString(PARAM_PARAMETER);

    if ((dL-dU) > ZERO) // Lower Bound Must be < Upper Bound
      CError::errorGreaterThan(PARAM_UPPER_BOUND, PARAM_LOWER_BOUND);
    if (dN <= ZERO) // N is number of steps
      CError::errorLessThanEqualTo(PARAM_N, PARAM_ZERO);

  } catch (string Ex) {
    Ex = "CProfile.validate(" + getParameter() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProfile::build()
// Build
//**********************************************************************
void CProfile::build() {
  try {
    // Get our Target
    if (pTarget == 0) {
      CEstimateManager *pEstimateManager = CEstimateManager::Instance();
      pTarget = pEstimateManager->getEstimate(sParameter);
    }
  } catch (string Ex) {
    Ex = "CProfile.build(" + getParameter() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CProfile::~CProfile()
// Default De-Constructor
//**********************************************************************
CProfile::~CProfile() {
}
