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

//**********************************************************************
// CProfile::CProfile(CProfile *Profile = 0)
// Default Constructor
//**********************************************************************
CProfile::CProfile(CProfile *Profile)
: CBaseBuildableObject(Profile) {

  // Vars
  dN            = 0.0;
  dL            = 0.0;
  dU            = 0.0;
  dCurrent      = 0.0;
  sParameter    = "";
  pTarget       = 0;

  // Copy Construct
  if (Profile != 0) {
    dN          = Profile->getN();
    dL          = Profile->getL();
    dU          = Profile->getU();
    dCurrent    = Profile->getCurrent();
    sParameter  = Profile->getParameter();
  }
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
    // Lower Bound Must be < Upper Bound
    if ((dL-dU) > ZERO)
      CError::errorGreaterThan(PARAM_UPPER_BOUND, PARAM_LOWER_BOUND);
    // N must be < Upper Bound
    if ((dN-dU) > ZERO)
      CError::errorGreaterThan(PARAM_N, PARAM_UPPER_BOUND);
    if (CComparer::isZero(dN))
      CError::errorEqualTo(PARAM_N, PARAM_ZERO);

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
