//============================================================================
// Name        : CSampleDerivedQuantity.cpp
// Author      : S.Rasmussen
// Date        : 18/06/2012
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CAbundanceDerivedQuantity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../InitializationPhases/CInitializationPhase.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../World/WorldView/CCompleteWorldView.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
//
//
//**********************************************************************
CAbundanceDerivedQuantity::CAbundanceDerivedQuantity() {

  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_TIME_STEP);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_INITIALIZATION_TIME_STEPS);
  // Build World View
  pWorldView = new CCompleteWorldView();
}

//**********************************************************************
// void CDerivedQuantity::validate()
// Validate our Derived Quantity
//**********************************************************************
void CAbundanceDerivedQuantity::validate() {
  try {
    // Base
    CBaseBuild::validate();

    // Get our parameters
    sTimeStep     = pParameterList->getString(PARAM_TIME_STEP);
    sLayer        = pParameterList->getString(PARAM_LAYER);

    pParameterList->fillVector(vInitializationTimeStepNames, PARAM_INITIALIZATION_TIME_STEPS,true);
    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Validate
    if (vCategoryNames.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    int initialisationPhaseCount = CInitializationPhaseManager::Instance()->getNumberInitializationPhases();
    if (vInitializationTimeStepNames.size() != 0 && (int)vInitializationTimeStepNames.size() != initialisationPhaseCount)
      THROW_EXCEPTION(PARAM_INITIALIZATION_TIME_STEPS + string(" size must be same as number of defined initialisation phases"));

    //Scott TODO: Validate PARAM_INITIALIZATION_TIME_STEPS are val;id time steps in each inialisation phase
    //            Should be a vector of length inialisation_phases
    //            each element should be valid within that phase
    // if the vector is not supplied, then default to the end of the annual cycle in each phase

    pWorldView->validate();

  } catch (string &Ex) {
    Ex = "CDerivedQuantity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantity::build()
// Build our Derived Quantity
//**********************************************************************
void CAbundanceDerivedQuantity::build() {
  try {
    // Get TimeStep and Layer
    pTimeStepManager = CTimeStepManager::Instance();
    iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);

    pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Get a vector of Initialisation indexes
    if (vInitializationTimeStepNames.size() > 0) {
      CInitializationPhaseManager *initialisationManager = CInitializationPhaseManager::Instance();

      foreach(string name, vInitializationTimeStepNames) {
        vInitializationTimeStepIndex.push_back(initialisationManager->getInitializationPhaseOrderIndex(name));
      }
    }

    // Get our Selectivitys and Categories
    CSelectivityManager::Instance()->fillVector(vSelectivities, vSelectivityNames);
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    pWorldView->build();

  } catch (string &Ex) {
    Ex = "CDerivedQuantity.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSampleDerivedQuantity::calculate()
// Calculate a value during a standard model run
//**********************************************************************
void CAbundanceDerivedQuantity::calculate() {

  if (pTimeStepManager->getCurrentTimeStep() != iTimeStep) {
    return;
  }

  double dValue = 0.0;

  pWorldView->execute();
  pBaseSquare = pWorldView->getSquare();

  for (int i = 0; i < (int)vCategories.size(); ++i) {
    for (int j = 0; j < pBaseSquare->getWidth(); ++j) {
      dValue += pBaseSquare->getValue(vCategories[i], j) * vSelectivities[i]->getResult(j);
    }
  }

  // Store our Value
  vValues.push_back(dValue);

}

//**********************************************************************
// void CSampleDerivedQuantity::calculate(int initialisationPhase)
// Calculate a value during one of our initialisation phases
//**********************************************************************
void CAbundanceDerivedQuantity::calculate(int initialisationPhase, int timeStep ) {

  // Check if we're in the right initialisation phase
  if (std::find(vInitializationTimeStepIndex.begin(), vInitializationTimeStepIndex.end(), initialisationPhase) == vInitializationTimeStepIndex.end()  ) {
    return;
  }

  // Check if we're in the right timestep
  CInitializationPhase *phase = CInitializationPhaseManager::Instance()->getInitializationPhase(initialisationPhase);
  if (phase->getCurrentTimeStep() != timeStep)
    return;


// SCOTT: TODO: work out the index of the initialisation phase timestep index, and test here to see if we are in the correct timestep
//              this same code needs adding to CBiomassDerivedQuantity.cpp as well
//   int what_is_the_index_of vInitializationTimeStepNames[initialisationPhase]
//   if (timeStep != what_is_the_index_of) {
//    return;
//  }

  if ((int)vvInitialisationValues.size() <= initialisationPhase)
    vvInitialisationValues.resize(initialisationPhase+1);

  double dValue = 0.0;

  pWorldView->execute();
  pBaseSquare = pWorldView->getSquare();

  for (int i = 0; i < (int)vCategories.size(); ++i) {
    for (int j = 0; j < pBaseSquare->getWidth(); ++j) {
      dValue += pBaseSquare->getValue(vCategories[i], j) * vSelectivities[i]->getResult(j);
    }
  }

  vvInitialisationValues[initialisationPhase].push_back(dValue);
}

//**********************************************************************
//
//
//**********************************************************************
CAbundanceDerivedQuantity::~CAbundanceDerivedQuantity() {
}
