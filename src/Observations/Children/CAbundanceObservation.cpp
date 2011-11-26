//============================================================================
// Name        : CAbundanceObservation.cpp
// Author      : S.Rasmussen
// Date        : 4/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CAbundanceObservation.h"
#include "../../Catchabilities/CCatchabilityManager.h"
#include "../../Catchabilities/CCatchability.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CConvertor.h"

//**********************************************************************
// CAbundanceObservation::CAbundanceObservation()
// Default Constructor
//**********************************************************************
CAbundanceObservation::CAbundanceObservation() {

  // Variables
  sCatchability   = "";
  pCatchability   = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATCHABILITY);
  pParameterList->registerAllowed(PARAM_OBS);
  pParameterList->registerAllowed(PARAM_ERROR_VALUE);
  pParameterList->registerAllowed(PARAM_DELTA);
  pParameterList->registerAllowed(PARAM_PROPORTION_TIME_STEP);
  pParameterList->registerAllowed(PARAM_PROCESS_ERROR);
}

//**********************************************************************
// void CAbundanceObservation::validate()
// validate
//**********************************************************************
void CAbundanceObservation::validate() {
  try {
    // Base Validate
    CObservation::validate();

    // Get our Parameters
    sCatchability       = pParameterList->getString(PARAM_CATCHABILITY);
    dDelta              = pParameterList->getDouble(PARAM_DELTA,true,DELTA);
    dProportionTimeStep = pParameterList->getDouble(PARAM_PROPORTION_TIME_STEP,true,1.0);
    dProcessError       = pParameterList->getDouble(PARAM_PROCESS_ERROR,true,0);

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    if ((vOBS.size() % 2) != 0)
      CError::errorPairs(PARAM_OBS);

    for (int i = 0; i < (int)vOBS.size(); i+=2)
      mProportionMatrix[vOBS[i]] = CConvertor::stringToDouble(vOBS[i+1]);

    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);

    // Get our ErrorValues
    vector<string> vErrorValues;
    pParameterList->fillVector(vErrorValues, PARAM_ERROR_VALUE);

    if ((vErrorValues.size() % 2) != 0)
      CError::errorPairs(PARAM_ERROR_VALUE);

    for (int i = 0; i < (int)vErrorValues.size(); i+=2) {
      mErrorValue[vErrorValues[i]] = CConvertor::stringToDouble(vErrorValues[i+1]);
      // Check for negative values
      if(mErrorValue[vErrorValues[i]] < 0.0)
        CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);
    }

    // Validate our vErrorValues's to make sure we have the right amount for our
    // Observations
    bool bMatch = false;
    map<string, double>::iterator mErrorValuePtr  = mErrorValue.begin();
    map<string, double>::iterator mPropPtr        = mProportionMatrix.begin();

    while (mErrorValuePtr != mErrorValue.end()) {
      // Reset Vars
      bMatch      = false;
      mPropPtr    = mProportionMatrix.begin();

      while (mPropPtr != mProportionMatrix.end()) {
        if ( (*mPropPtr).first == (*mErrorValuePtr).first ) {
          bMatch = true;
          break;
        }
        mPropPtr++;
      }

      if (!bMatch)
        CError::errorNoMatch(PARAM_ERROR_VALUE, (*mErrorValuePtr).first, PARAM_OBS);

      mErrorValuePtr++;
    }

  } catch (string &Ex) {
    Ex = "CAbundanceObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAbundanceObservation::build()
// build
//**********************************************************************
void CAbundanceObservation::build() {
  try {
    // Base build
    CObservation::build();

    // Build relationships
    CCatchabilityManager *pCatchabilityManager = CCatchabilityManager::Instance();
    pCatchability = pCatchabilityManager->getCatchability(sCatchability);

  } catch (string &Ex) {
    Ex = "CAbundanceObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAbundanceObservation::execute()
// Execute
//**********************************************************************
void CAbundanceObservation::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Variables
                        dScore           = 0.0;
    double              dExpectedTotal   = 0.0;
    vector<string>      vKeys;
    vector<double>      vExpected;
    vector<double>      vObserved;
    vector<double>      vProcessError;
    vector<double>      vErrorValue;
    vector<double>      vScores;

    // Base
    CObservation::execute();

    pWorldView->execute();

    // Loop Through Obs
    map<string, double>::iterator mPropPtr = mProportionMatrix.begin();
    while (mPropPtr != mProportionMatrix.end()) {
      // Reset Vars
      dExpectedTotal = 0.0;

      CWorldSquare *pSquare = pWorldView->getSquare((*mPropPtr).first);

      for (int i = 0; i < (int)vCategories.size(); ++i)
        for (int j = 0; j < pSquare->getWidth(); ++j) {
          double dSelectResult = vSelectivities[i]->getResult(j);
          dExpectedTotal += dSelectResult * pSquare->getAbundanceInCategoryForAge(j, vCategories[i]);
        }

      // Note: dExpectedTotal is total number of fish the model has for that
      // Proportion Label across all squares in that layer where that
      // label is used.
      dExpectedTotal *= pCatchability->getQ();
      double dErrorValue = mErrorValue[(*mPropPtr).first];

      // Store our Values
      vKeys.push_back((*mPropPtr).first);
      vExpected.push_back(dExpectedTotal);
      vObserved.push_back((*mPropPtr).second);
      vErrorValue.push_back(dErrorValue);
      vProcessError.push_back(dProcessError);

      mPropPtr++;
    }

    // Simulate or Generate Result?
    if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION) {
      // Simulate our values, then save them
      pLikelihood->simulateObserved(vKeys, vObserved, vExpected, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vObserved.size(); ++i)
        saveComparison(vKeys[i], vExpected[i], vObserved[i], vErrorValue[i], 0.0);

    } else { // Generate Score
      dScore = 0.0;

      // Generate Results and save them
      pLikelihood->getResult(vScores, vExpected, vObserved, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vScores.size(); ++i) {
        dScore += vScores[i];
        saveComparison(vKeys[i], vExpected[i], vObserved[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), vScores[i]);
      }
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CAbundanceObservation.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAbundanceObservation::~CAbundanceObservation()
// Default De-Constructor
//**********************************************************************
CAbundanceObservation::~CAbundanceObservation() {
}
