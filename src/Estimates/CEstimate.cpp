//============================================================================
// Name        : CEstimate.cpp
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local headers
#include "CEstimate.h"
#include "../ParameterParser/CParamParser.h"
#include "../Priors/CPriorManager.h"
#include "../Priors/CPrior.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CConvertor.h"

//**********************************************************************
// CEstimate::CEstimate()
// Default Constructor
//**********************************************************************
CEstimate::CEstimate() {
  // Default Values
  pPrior    = 0;
  pTarget   = 0;
  bEnabled  = true;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_PARAMETER);
  pParameterList->registerAllowed(PARAM_LOWER_BOUND);
  pParameterList->registerAllowed(PARAM_UPPER_BOUND);
  pParameterList->registerAllowed(PARAM_PRIOR);
  pParameterList->registerAllowed(PARAM_SAME);

  // Add Default
  pParameterList->addParameter(PARAM_LABEL, "Estimate");
}

//**********************************************************************
// void CEstimate::addValue(double value)
// Add A Value to our Estimate
//**********************************************************************
void CEstimate::addValue(double value) {
  vValueList.push_back(value);
}

//**********************************************************************
// void CEstimate::setValue(double value)
// Set Value of our Target
//**********************************************************************
void CEstimate::setValue(double value) {
#ifndef OPTIMIZE
  try {
#endif
    if (pTarget == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    (*pTarget) = value;

    // Set our Sames.
    foreach(double* Target, vSameIndex) {
      (*Target) = value;
    }

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CEstimate.setValue()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// double CEstimate::getValue()
// Get the Value of our Target
//**********************************************************************
double CEstimate::getValue() {
#ifndef OPTIMIZE
  try {
    if (pTarget == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

  } catch (string Ex) {
    Ex = "CEstimate.getValue()->" + Ex;
    throw Ex;
  }
#endif
  return (*pTarget);
}

//**********************************************************************
// double CEstimate::getPriorScore()
// Get The Score for Our Prior
//**********************************************************************
double CEstimate::getPriorScore() {
#ifndef OPTIMIZE
  try {
    if (pPrior == 0)
          CError::errorMissing(PARAM_PRIOR);
#endif

    if (sPrior == "")
      return 0.0; // No Prior

    return pPrior->getResult((*pTarget));

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CEstimate.getPriorScore(" + getParameter() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// void CEstimate::loadValue(int index)
// Load Our Value
//**********************************************************************
void CEstimate::loadValue(int index) {
  try {
    if (index < 0)
      throw string(ERROR_INVALID_IDX + CConvertor::intToString(index));
    if (index >= (int)vValueList.size())
      throw string(ERROR_INVALID_IDX + CConvertor::intToString(index));

    setValue(vValueList[index]);

  } catch (string Ex) {
    Ex = "CEstimate.loadValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimate::validate()
// validate
//**********************************************************************
void CEstimate::validate() {
  try {
    // Base
    CBaseBuild::validate();

    // Populate our Variables
    sParameter    = pParameterList->getString(PARAM_PARAMETER);
    dLowerBound   = pParameterList->getDouble(PARAM_LOWER_BOUND);
    dUpperBound   = pParameterList->getDouble(PARAM_UPPER_BOUND);
    sPrior        = pParameterList->getString(PARAM_PRIOR, true, "");

    pParameterList->fillVector(vSameList, PARAM_SAME, true);

    // Validate
    if (dUpperBound < dLowerBound)
      CError::errorLessThan(PARAM_UPPER_BOUND, PARAM_LOWER_BOUND);

  } catch (string Ex) {
    Ex = "CEstimate.validate(" + sParameter + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimate::build()
// build
//**********************************************************************
void CEstimate::build() {
  try {
    // Build Our Estimate Target
    CParamParser clParser = CParamParser();
    pTarget = clParser.parseCommand(sParameter);

    // Build our Prior Target
    if (sPrior != "") {
      CPriorManager *pPriorManager = CPriorManager::Instance();
      pPrior = pPriorManager->getPrior(sPrior);
    }

    // Populate Same Index
    vSameIndex.clear();
    foreach(string Same, vSameList) {
      vSameIndex.push_back(clParser.parseCommand(Same));
    }

  } catch (string Ex) {
    Ex = "CEstimate.build(" + sParameter + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CEstimate::~CEstimate()
// Default De-Constructor
//**********************************************************************
CEstimate::~CEstimate() {
}
