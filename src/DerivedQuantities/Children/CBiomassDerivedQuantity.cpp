//============================================================================
// Name        : CBiomassDerivedQuantity.cpp
// Author      : S.Rasmussen
// Date        : 18/06/2012
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CBiomassDerivedQuantity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
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
CBiomassDerivedQuantity::CBiomassDerivedQuantity() {

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
void CBiomassDerivedQuantity::validate() {
  try {
    // Base
    CBaseBuild::validate();

    // Get our parameters
    sTimeStep               = pParameterList->getString(PARAM_TIME_STEP);
    sLayer                  = pParameterList->getString(PARAM_LAYER);

    pParameterList->fillVector(vInitializationTimeStepNames, PARAM_INITIALIZATION_TIME_STEPS,true); // not currently used: but if not defined, should default to the end of the annual cycle in each initialisation phase
    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Validate
    if (vCategoryNames.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

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
void CBiomassDerivedQuantity::build() {
  try {
    // Get TimeStep and Layer
    pTimeStepManager = CTimeStepManager::Instance();
    iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);

    pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

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
void CBiomassDerivedQuantity::calculate() {

  if (pTimeStepManager->getCurrentTimeStep() != iTimeStep) {
    return;
  }

  double dValue = 0.0;

  pWorldView->execute();
  pBaseSquare = pWorldView->getSquare();

  for (int i = 0; i < (int)vCategories.size(); ++i) {
    for (int j = 0; j < pBaseSquare->getWidth(); ++j) {
      double dAbundance = pBaseSquare->getValue(vCategories[i], j) * vSelectivities[i]->getResult(j);
      dValue += dAbundance * pWorld->getMeanWeight(j,i);
    }
  }

  // Store our Value
  vValues.push_back(dValue);

}

//**********************************************************************
// void CSampleDerivedQuantity::calculate(int initialisationPhase)
// Calculate a value during one of our initialisation phases
//**********************************************************************
void CBiomassDerivedQuantity::calculate(int initialisationPhase, int timeStep) {

  if ((int)vvInitialisationValues.size() <= initialisationPhase)
    vvInitialisationValues.resize(initialisationPhase+1);

  double dValue = 0.0;

  pWorldView->execute();
  pBaseSquare = pWorldView->getSquare();

  for (int i = 0; i < (int)vCategories.size(); ++i) {
    for (int j = 0; j < pBaseSquare->getWidth(); ++j) {
      double dAbundance = pBaseSquare->getValue(vCategories[i], j) * vSelectivities[i]->getResult(j);
      dValue += dAbundance * pWorld->getMeanWeight(j,i);
    }
  }

  vvInitialisationValues[initialisationPhase].push_back(dValue);
}

//**********************************************************************
//
//
//**********************************************************************
CBiomassDerivedQuantity::~CBiomassDerivedQuantity() {
}

