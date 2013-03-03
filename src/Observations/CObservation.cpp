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
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Layers/CLayerManager.h"
#include "../Likelihoods/Factory/CLikelihoodFactory.h"
#include "../Selectivities/CSelectivityManager.h"
#include "../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CObservation::CObservation()
// Default Constructor
//**********************************************************************
CObservation::CObservation() {
  // Variables
  pStartWorldView       = 0;
  pWorldView            = 0;
  pLikelihood           = 0;
  bSimulationRunMode    = false;

  // Register some user allowed variables
  pParameterList->registerAllowed(PARAM_YEAR);
  pParameterList->registerAllowed(PARAM_TIME_STEP);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_PROPORTION_TIME_STEP);
  pParameterList->registerAllowed(PARAM_PROPORTION_METHOD);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_LIKELIHOOD);
  pParameterList->registerAllowed(PARAM_SIMULATION_LIKELIHOOD);
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
// void CObservation::saveComparison(string key, int age, double expected, double observed, double errorValue, double score)
// Save comparison into our Vector
//**********************************************************************
void CObservation::saveComparison(string key, int age, double expected, double observed, double errorValue, double score) {

  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      if (pRuntimeController->getRunMode() != RUN_MODE_SIMULATION)
        return;

  SComparison *pComparison = new SComparison();
  pComparison->sKey           = key;
  pComparison->iAge           = age;
  pComparison->dExpectedValue = expected;
  pComparison->dObservedValue = observed;
  pComparison->dErrorValue    = errorValue;
  pComparison->dScore         = score;
  vComparisons.push_back(pComparison);
}

//**********************************************************************
// void CObservation::saveComparison(string key, double expected, double observed, double errorValue, double score)
// Save comparison into our Vector
//**********************************************************************
void CObservation::saveComparison(string key, double expected, double observed, double errorValue, double score) {

  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      if (pRuntimeController->getRunMode() != RUN_MODE_SIMULATION)
        return;

  SComparison *pComparison = new SComparison();
  pComparison->sKey           = key;
  pComparison->iAge           = -1;
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
    iYear               = pParameterList->getInt(PARAM_YEAR);
    sTimeStep           = pParameterList->getString(PARAM_TIME_STEP);
    sLayer              = pParameterList->getString(PARAM_LAYER);
    sLikelihood         = pParameterList->getString(PARAM_LIKELIHOOD);
    dProportionTimeStep = pParameterList->getDouble(PARAM_PROPORTION_TIME_STEP,true,1.0);
    sProportionMethod   = pParameterList->getString(PARAM_PROPORTION_METHOD,true,PARAM_MEAN);

    if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION) {
      if(sLikelihood == PARAM_PSEUDO) {
        sSimulationLikelihood = pParameterList->getString(PARAM_SIMULATION_LIKELIHOOD);
        sLikelihood = sSimulationLikelihood;
      } else {
        sSimulationLikelihood = sLikelihood;
      }
    }

    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    if (dProportionTimeStep < 0)
      CError::errorLessThan(PARAM_PROPORTION_TIME_STEP, PARAM_ZERO);
    if (dProportionTimeStep > 1)
      CError::errorGreaterThan(PARAM_PROPORTION_TIME_STEP, PARAM_ONE);

    if (!(sProportionMethod == PARAM_MEAN || sProportionMethod == PARAM_DIFFERENCE)) {
      CError::errorNotEqual(PARAM_PROPORTION_METHOD,PARAM_MEAN + string(" or ") + PARAM_DIFFERENCE);
    }

    //Check length of categories and selectivites are equal
    unsigned iCategoryNamesSize = vCategoryNames.size();
    unsigned iSelectivityNamesSize = vSelectivityNames.size();

    if (iCategoryNamesSize != iSelectivityNamesSize)
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

  } catch (string &Ex) {
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
    pLayer = pLayerManager->getCategoricalLayer(sLayer);

    // Get Selectivities
    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vSelectivities, vSelectivityNames);

    // Get Categories
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    // Get the Index for our TimeStep in the Order Vector
    CTimeStepManager *pTimeStepManager = CTimeStepManager::Instance();
    iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);

    // Build our start world view. This represents the world before the timestep
    pStartWorldView = new CLayerDerivedWorldView(pLayer);
    pStartWorldView->validate();
    pStartWorldView->build();

    // Build our World View
    pWorldView = new CLayerDerivedWorldView(pLayer);
    pWorldView->validate();
    pWorldView->build();

    // Get our Likelihood
    pLikelihood = CLikelihoodFactory::buildLikelihood(pParameterList->getString(PARAM_TYPE), sLikelihood);

    // Set simulation mode flag if needed
    if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION)
      bSimulationRunMode = true;
    else
      bSimulationRunMode = false;

  } catch (string &Ex) {
    Ex = "CObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservation::prepare()
// This method is called before the timestep to load any pre-timestep info
//**********************************************************************
void CObservation::prepare() {
  /**
   * Execute our start world view. This means when we actually call
   * execute we'll have a view of the world from before the timestep
   * and we can interpolate this.
   */
  pStartWorldView->execute();
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
  if (pWorldView != 0)
    delete pWorldView;

  foreach(SComparison *Comparison, vComparisons) {
    delete Comparison;
  }
  vComparisons.clear();

  if (pLikelihood != 0)
    delete pLikelihood;
}
