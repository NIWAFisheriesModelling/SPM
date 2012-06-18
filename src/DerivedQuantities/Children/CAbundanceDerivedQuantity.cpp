//============================================================================
// Name        : CSampleDerivedQuantity.cpp
// Author      : S.Rasmussen
// Date        : 18/06/2012
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CAbundanceDerivedQuantity.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/ForEach.h"
#include "../../World/WorldView/CCompleteWorldView.h"
#include "../../Helpers/CError.h"
#include "../../Selectivities/CSelectivityManager.h"

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

  // Build World View
  pWorldView = new CCompleteWorldView();
}

//**********************************************************************
//
//
//**********************************************************************
CAbundanceDerivedQuantity::~CAbundanceDerivedQuantity() {
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
void CAbundanceDerivedQuantity::build() {
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
void CAbundanceDerivedQuantity::calculate(int initialisationPhase) {

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
