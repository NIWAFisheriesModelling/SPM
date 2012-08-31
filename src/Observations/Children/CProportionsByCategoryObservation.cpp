//============================================================================
// Name        : CProportionsByCategoryObservation.cpp
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>
#include <limits>
#include <boost/lexical_cast.hpp>

// Local Headers
#include "CProportionsByCategoryObservation.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/ForEach.h"
#include "../../Selectivities/CSelectivityManager.h"

// Using
using std::cout;
using std::endl;
using std::numeric_limits;

//**********************************************************************
// CProportionsByCategoryObservation::CProportionsByCategoryObservation()
// Default Constructor
//**********************************************************************
CProportionsByCategoryObservation::CProportionsByCategoryObservation() {
  // Variables
  pAgeResults             = 0;
  pCombinedAgeResults     = 0;
  iMinAge                 = -1;
  iMaxAge                 = -1;
  bAgePlus                = false;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MIN_AGE);
  pParameterList->registerAllowed(PARAM_MAX_AGE);
  pParameterList->registerAllowed(PARAM_AGE_PLUS_GROUP);
  pParameterList->registerAllowed(PARAM_OBS);
  pParameterList->registerAllowed(PARAM_ERROR_VALUE);
  pParameterList->registerAllowed(PARAM_TARGET_CATEGORIES);
  pParameterList->registerAllowed(PARAM_TARGET_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_DELTA);
  pParameterList->registerAllowed(PARAM_PROCESS_ERROR);
}

//**********************************************************************
// void CProportionsByCategoryObservation::validate()
// Validate the Observation Parameters
//**********************************************************************
void CProportionsByCategoryObservation::validate() {
  try {
    // Base Validation
    CObservation::validate();

    // Get our Variables from ParameterList
    dDelta              = pParameterList->getDouble(PARAM_DELTA,true,DELTA);
    iMinAge             = pParameterList->getInt(PARAM_MIN_AGE);
    iMaxAge             = pParameterList->getInt(PARAM_MAX_AGE);
    bAgePlus            = pParameterList->getBool(PARAM_AGE_PLUS_GROUP);
    dProcessError       = pParameterList->getDouble(PARAM_PROCESS_ERROR,true,0);

    pParameterList->fillVector(vTargetCategoryNames, PARAM_TARGET_CATEGORIES);
    pParameterList->fillVector(vTargetSelectivityNames, PARAM_TARGET_SELECTIVITIES);

    if (dDelta < 0)
      CError::errorLessThan(PARAM_DELTA, PARAM_ZERO);

    // Find out the Spread in Ages
    int iAgeSpread = (iMaxAge+1) - iMinAge;

    if (iMinAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_MIN_AGE, PARAM_MIN_AGE);
    if (iMaxAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_MAX_AGE, PARAM_MAX_AGE);
    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    if ((vOBS.size() % (iAgeSpread+1)) != 0)
      throw string("OBS not right amount");

    for (int i = 0; i < (int)vOBS.size(); i+=(iAgeSpread+1)) {
      for (int j = 0; j < iAgeSpread; ++j) {
        try {
          mvProportionMatrix[vOBS[i]].push_back(boost::lexical_cast<double>(vOBS[i+j+1]));
        } catch (boost::bad_lexical_cast) {
          string Ex = string("Non-numeric value in ") + PARAM_OBS + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
          throw Ex;
        }
      }
    }

    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);

    // Get our Error Value
    vector<string> vErrorValues;
    pParameterList->fillVector(vErrorValues, PARAM_ERROR_VALUE);

    if (vErrorValues.size() != vOBS.size()) {
      CError::errorListSameSize(PARAM_OBS, PARAM_ERROR_VALUE);
    }

    for (int i = 0; i < (int)vErrorValues.size(); i+=(iAgeSpread+1)) {
      for (int j = 0; j < iAgeSpread; ++j) {
        try {
          mvErrorValue[vErrorValues[i]].push_back(boost::lexical_cast<double>(vErrorValues[i+j+1]));
        } catch (boost::bad_lexical_cast) {
          string Ex = string("Non-numeric value in ") + PARAM_ERROR_VALUE + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
          throw Ex;
        }

        // Check for negative values
        if(boost::lexical_cast<double>(vErrorValues[i+j+1]) < 0.0)
          CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);
      }
    }

  } catch (string &Ex) {
    Ex = "CProportionsByCategoryObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsByCategoryObservation::build()
// Build our Observation Objects and Relationships
//**********************************************************************
void CProportionsByCategoryObservation::build() {
  try {
    // Base Build
    CObservation::build();

    pWorld->fillCategoryVector(vTargetCategories, vTargetCategoryNames);
    foreach(int Category, vCategories) {
      vTargetCategories.push_back(Category);
    }

    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vTargetSelectivities, vTargetSelectivityNames);
    foreach(CSelectivity* Selectivity, vSelectivities) {
      vTargetSelectivities.push_back(Selectivity);
    }

    // Create Array of Age Results
    iArraySize = (iMaxAge+1) - iMinAge;

    if (pAgeResults == 0)
      pAgeResults = new double[iArraySize];
    for (int i = 0; i < iArraySize; ++i)
      pAgeResults[i] = 0.0;

    if (pCombinedAgeResults == 0)
      pCombinedAgeResults = new double[iArraySize];
    for (int i = 0; i < iArraySize; ++i)
      pCombinedAgeResults[i] = 0.0;

    // Validate our N's against the OBS
    // They have to have a 1-to-1 relationship
    bool bMatch = false;
    map<string, vector<double> >::iterator vNPtr = mvErrorValue.begin();
    map<string, vector<double> >::iterator vPropPtr = mvProportionMatrix.begin();

    while (vNPtr != mvErrorValue.end()) {
      bMatch = false;
      // Loop Props Looking For Match;
      vPropPtr = mvProportionMatrix.begin();
      while (vPropPtr != mvProportionMatrix.end()) {
        if ((*vPropPtr).first == (*vNPtr).first) {
          bMatch = true;
          break;
          }
      vPropPtr++;
      }

      if (!bMatch)
        throw string(ERROR_MISSING_N_OBS + (*vNPtr).first);

      vNPtr++;
    }

  } catch (string &Ex) {
    Ex = "CProportionsByCategoryObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsByCategoryObservation::execute()
// Execute our Observation to generate a score
//**********************************************************************
void CProportionsByCategoryObservation::execute() {

  // Base
  CObservation::execute();

  // Variables
  int                 iSquareAgeOffset   = iMinAge - pWorld->getMinAge();
  vector<string>      vKeys;
  vector<int>         vAges;
  vector<double>      vExpected;
  vector<double>      vObserved;
  vector<double>      vProcessError;
  vector<double>      vErrorValue;
  vector<double>      vScores;
                      dScore = 0.0;

  // Execute the World View to get a Snapshot
  pWorldView->execute();

  // Loop through our proportions
  map<string, vector<double> >::iterator mvPropPtr = mvProportionMatrix.begin();
  while (mvPropPtr != mvProportionMatrix.end()) {
    // Get Square for this Area
      CWorldSquare *pStartSquare = pStartWorldView->getSquare((*mvPropPtr).first);
      CWorldSquare *pSquare      = pWorldView->getSquare((*mvPropPtr).first);

    // Build our 2 Age Result arrays so we can compare them to get the
    // proportion to match against our observation.
    for (int i = 0; i < iArraySize; ++i) {
      // Loop Through Categories
      for (int j = 0; j < (int)vCategories.size(); ++j) {
        double dSelectResult = vSelectivities[j]->getResult(i);
        //pAgeResults[i] += dSelectResult * pSquare->getAbundanceInCategoryForAge((i+iSquareAgeOffset), vCategories[j]);
        double dStartValue      = pStartSquare->getAbundanceInCategoryForAge((i+iSquareAgeOffset), vCategories[j]);
        double dEndValue        = pSquare->getAbundanceInCategoryForAge((i+iSquareAgeOffset), vCategories[j]);
        double dProportionValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
        pAgeResults[i] += dSelectResult * dProportionValue;
      }
      for (int j = 0; j < (int)vTargetCategories.size(); ++j) {
        double dSelectResult = vTargetSelectivities[j]->getResult(i);
        //pCombinedAgeResults[i] += dSelectResult * pSquare->getAbundanceInCategoryForAge((i+iSquareAgeOffset), vTargetCategories[j]);
        double dStartValue      = pStartSquare->getAbundanceInCategoryForAge((i+iSquareAgeOffset), vTargetCategories[j]);
        double dEndValue        = pSquare->getAbundanceInCategoryForAge((i+iSquareAgeOffset), vTargetCategories[j]);
        double dProportionValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
        pCombinedAgeResults[i] += dSelectResult * dProportionValue;
      }
    }

    // If we have an age_plus_group we wanna add all + ages to the highest specified
    if(bAgePlus) {
      // Loop Through Plus Group Ages in that square and add them to count for the Plus group
      for (int i = iArraySize+iSquareAgeOffset; i < pWorld->getAgeSpread(); ++i) {
        // Loop Through Categories
        for (int j = 0; j < (int)vCategories.size(); ++j) {
          double dSelectResult = vSelectivities[j]->getResult(i);
          //pAgeResults[iArraySize-1] += dSelectResult * pSquare->getAbundanceInCategoryForAge(i, vCategories[j]);
          double dStartValue      = pStartSquare->getAbundanceInCategoryForAge(i, vCategories[j]);
          double dEndValue        = pSquare->getAbundanceInCategoryForAge(i, vCategories[j]);
          double dProportionValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
          pAgeResults[iArraySize-1] += dSelectResult * dProportionValue;
        }
        for (int j = 0; j < (int)vTargetCategories.size(); ++j) {
          double dSelectResult = vTargetSelectivities[j]->getResult(i);
          //pCombinedAgeResults[iArraySize-1] += dSelectResult * pSquare->getAbundanceInCategoryForAge(i, vTargetCategories[j]);
          double dStartValue      = pStartSquare->getAbundanceInCategoryForAge(i, vTargetCategories[j]);
          double dEndValue        = pSquare->getAbundanceInCategoryForAge(i, vTargetCategories[j]);
          double dProportionValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
          pCombinedAgeResults[iArraySize-1] += dSelectResult * dProportionValue;
        }
      }
    }

    // Do our Comparison
    for (int i = 0; i < iArraySize; ++i) {
      double dExpected = 0.0;
      if (!CComparer::isZero(pCombinedAgeResults[i]))
        dExpected = pAgeResults[i]/pCombinedAgeResults[i];

      // Store the items we want to calculate scores for
      vKeys.push_back((*mvPropPtr).first);
      vAges.push_back(i+pWorld->getMinAge());
      vExpected.push_back(dExpected);
      vObserved.push_back((*mvPropPtr).second[i]);
      vProcessError.push_back(dProcessError);
      vErrorValue.push_back(mvErrorValue[(*mvPropPtr).first][i]);
    }

    // Clear Our Age Results
    for (int i = 0; i < iArraySize; ++i) {
      pAgeResults[i] = 0.0;
      pCombinedAgeResults[i] = 0.0;
    }

    mvPropPtr++;
  }

  // Simulate or Generate Result?
  if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION) {
    // Simulate our values, then save them
    pLikelihood->simulateObserved(vKeys, vObserved, vExpected, vErrorValue, vProcessError, dDelta);
    for (int i = 0; i < (int)vObserved.size(); ++i)
      saveComparison(vKeys[i], vAges[i], vExpected[i], vObserved[i], vErrorValue[i], 0.0);

  } else { // Generate Score
    dScore = 0.0;

    // Generate Results and save them
    pLikelihood->getResult(vScores, vExpected, vObserved, vErrorValue, vProcessError, dDelta);
    for (int i = 0; i < (int)vScores.size(); ++i) {
      dScore += vScores[i];
      saveComparison(vKeys[i], vAges[i], vExpected[i], vObserved[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), vScores[i]);
    }
  }
}

//**********************************************************************
// CProportionsByCategoryObservation::~CProportionsByCategoryObservation()
// Default De-Constructor
//**********************************************************************
CProportionsByCategoryObservation::~CProportionsByCategoryObservation() {
  if (pAgeResults != 0)
    delete [] pAgeResults;
  if (pCombinedAgeResults != 0)
    delete [] pCombinedAgeResults;
}
