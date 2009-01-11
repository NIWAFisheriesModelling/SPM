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
// CEstimate::CEstimate(CEstimate *Estimate = 0)
// Default Constructor
//**********************************************************************
CEstimate::CEstimate(CEstimate *Estimate)
: CBaseBuildableObject(Estimate) {
  // Vars
  sParameter        = "";
  dLowerBound       = 0.0;
  dUpperBound       = 0.0;
  sPrior            = "";
  pPrior            = 0;
  pTarget           = 0;
  bEnabled          = true;

  // Copy Construct
  if (Estimate != 0) {
    sParameter      = Estimate->getParameter();
    dLowerBound     = Estimate->getLowerBound();
    dUpperBound     = Estimate->getUpperBound();
    sPrior          = Estimate->getPrior();

    // Copy Vectors
    for (int i = 0; i < Estimate->getSameCount(); ++i)
      addSame(Estimate->getSame(i));
  }
}

//**********************************************************************
// void CEstimate::addSame(string value)
// Add a same to our Vector.
//**********************************************************************
void CEstimate::addSame(string value) {
  vSameList.push_back(value);
}

//**********************************************************************
// string CEstimate::getSame(int index)
// Get Same
//**********************************************************************
string CEstimate::getSame(int index) {
  try {
    if (index >= (int)vSameList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_SAME);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vSameList[index];

  } catch (string Ex) {
    Ex = "CEstimable.getSame()->" + Ex;
    throw Ex;
  }

  return "";
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
#ifndef OPTIMISE
  try {
#endif
    if (pTarget == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    (*pTarget) = value;

    // Set our Sames.
    foreach(double* Target, vSameIndex) {
      (*Target) = value;
    }

#ifndef OPTIMISE
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
#ifndef OPTIMISE
  try {
#endif
    if (pTarget == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    return (*pTarget);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CEstimate.getValue()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// double CEstimate::getPriorScore()
// Get The Score for Our Prior
//**********************************************************************
double CEstimate::getPriorScore() {
#ifndef OPTIMISE
  try {
#endif

    if (sPrior == "")
      return 0.0; // No Prior
    if (pPrior == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    return pPrior->getResult((*pTarget));

#ifndef OPTIMISE
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
    if (sParameter == "")
      CError::errorMissing(PARAM_PARAMETER);
    if ( (dLowerBound == 0.0) && (dUpperBound == 0.0) )
      CError::errorMissing(PARAM_LOWER_BOUND);
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
    // Clear Same Index
    vSameIndex.clear();

    // Build Our Estimate Target
    CParamParser clParser = CParamParser();
    pTarget = clParser.parseCommand(sParameter);

    // Build our Prior Target
    if ( (pPrior == 0) && (sPrior != "")) {
      CPriorManager *pPriorManager = CPriorManager::Instance();
      pPrior = pPriorManager->getPrior(sPrior);
    }

    if ((int)vSameIndex.size() == 0) {
      foreach(string Same, vSameList) {
        vSameIndex.push_back(clParser.parseCommand(Same));
      }
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
