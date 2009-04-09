//============================================================================
// Name        : CObservation.cpp
// Author      : S.Rasmussen
// Date        : 19/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CObservation.h"
#include "../Layers/CLayerManager.h"
#include "../Selectivities/CSelectivityManager.h"
#include "../TimeSteps/CTimeStepManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

//**********************************************************************
// CObservation::CObservation()
// Default Constructor
//**********************************************************************
CObservation::CObservation() {
  // Variables
  pWorldView = 0;

  // Register some user allowed variables
  pParameterList->registerAllowed(PARAM_YEAR);
  pParameterList->registerAllowed(PARAM_TIME_STEP);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_LIKELIHOOD);
}

//**********************************************************************
// string CObservation::getCategory(int index)
// Get Category
//**********************************************************************
string CObservation::getCategory(int index) {
  return vCategoryNames[index];
}

//**********************************************************************
// string CObservation::getSelectivity(int index)
// Get The selectivity for index
//**********************************************************************
string CObservation::getSelectivity(int index) {
  return vSelectivityNames[index];
}

//**********************************************************************
// void CObservation::saveComparison(string key, double expected, double observed, double errorValue, double score)
// Save comparison into our Vector
//**********************************************************************
void CObservation::saveComparison(string key, double expected, double observed, double errorValue, double score) {

  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    return;

  SComparison *pComparison = new SComparison();
  pComparison->sKey           = key;
  pComparison->dExpectedValue = expected;
  pComparison->dObservedValue = observed;
  pComparison->dErrorValue    = errorValue;
  pComparison->dScore         = score;
  vComparisons.push_back(pComparison);
}

//**********************************************************************
// void CObservation::fillComparisons(vector<SComparison*> &comparisons)
// Fill Vector with Comparisons for Print Out
//**********************************************************************
void CObservation::fillComparisons(vector<SComparison*> &comparisons) {
 comparisons.clear();

 foreach(SComparison *Comparison, vComparisons) {
   comparisons.push_back(Comparison);
 }
}

//**********************************************************************
// void CObservation::validate()
// Validate the Observation
//**********************************************************************
void CObservation::validate() {
  try {
    // Base
    CBaseExecute::validate();

    // Assign our Variables
    iYear       = pParameterList->getInt(PARAM_YEAR);
    sTimeStep   = pParameterList->getString(PARAM_TIME_STEP);
    sLayer      = pParameterList->getString(PARAM_LAYER);
    sLikelihood = pParameterList->getString(PARAM_LIKELIHOOD);

    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

  } catch (string Ex) {
    Ex = "CObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// void CObservation::build()
// build
//**********************************************************************
void CObservation::build() {
  try {
    // Get our Layer Pointer
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayer = pLayerManager->getStringLayer(sLayer);

    // Get Selectivities
    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vSelectivities, vSelectivityNames);

    // Get Categories
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    // Get the Index for our TimeStep in the Order Vector
    CTimeStepManager *pTimeStepManager = CTimeStepManager::Instance();
    iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);

    // Build our World View
    pWorldView = new CLayerDerivedWorldView(pLayer);
    pWorldView->validate();
    pWorldView->build();

  } catch (string Ex) {
    Ex = "CObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservation::execute()
// Execute Observation
//**********************************************************************
void CObservation::execute() {
  // Clear Comparisons List
  foreach(SComparison *Comparison, vComparisons) {
      delete Comparison;
  }
  vComparisons.clear();
}

//**********************************************************************
// CObservation::~CObservation()
// Default De-Constructor
//**********************************************************************
CObservation::~CObservation() {
  delete pWorldView;

  foreach(SComparison *Comparison, vComparisons) {
    delete Comparison;
  }
  vComparisons.clear();
}
