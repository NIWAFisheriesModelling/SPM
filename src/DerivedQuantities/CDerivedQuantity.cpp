//============================================================================
// Name        : CDerivedQuantity.cpp
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CDerivedQuantity.h"
#include "../TimeSteps/CTimeStepManager.h"
#include "../Layers/CLayerManager.h"
#include "../Layers/Numeric/Base/CNumericLayer.h"
#include "../Selectivities/CSelectivity.h"
#include "../Helpers/ForEach.h"
#include "../World/WorldView/CCompleteWorldView.h"
#include "../Helpers/CError.h"
#include "../Selectivities/CSelectivityManager.h"

//**********************************************************************
// CDerivedQuantity::CDerivedQuantity()
// Default Constructor
//**********************************************************************
CDerivedQuantity::CDerivedQuantity() {

  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_TIME_STEP);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);

  // Build World View
  pWorldView = new CCompleteWorldView();
}

//**********************************************************************
// void CDerivedQuantity::validate()
// Validate our Derived Quantity
//**********************************************************************
void CDerivedQuantity::validate() {
  try {
    // Base
    CBaseExecute::validate();

    // Get our parameters
    sTimeStep     = pParameterList->getString(PARAM_TIME_STEP);
    sLayer        = pParameterList->getString(PARAM_LAYER);

    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Validate
    if (vCategoryNames.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    pWorldView->validate();

  } catch (string Ex) {
    Ex = "CDerivedQuantity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantity::build()
// Build our Derived Quantity
//**********************************************************************
void CDerivedQuantity::build() {
  try {

    // Get TimeStep and Layer
    pTimeStepManager = CTimeStepManager::Instance();
    iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);

    pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Get our Selectivitys and Categories
    CSelectivityManager::Instance()->fillVector(vSelectivities, vSelectivityNames);
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    pWorldView->build();

  } catch (string Ex) {
    Ex = "CDerivedQuantity.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantity::execute()
// Execute our Derived Quantity
//**********************************************************************
void CDerivedQuantity::execute() {

  if (pTimeStepManager->getCurrentTimeStep() != iTimeStep)
    return;

  double value = 0.0;


  pWorldView->execute();
  pBaseSquare = pWorldView->getSquare();

  for (int i = 0; i < (int)vCategories.size(); ++i) {
    for (int j = 0; j < pBaseSquare->getWidth(); ++j) {
      value += pBaseSquare->getValue(vCategories[i], j) * vSelectivities[i]->getResult(j);
    }
  }

}

//**********************************************************************
// CDerivedQuantity::~CDerivedQuantity()
// Destructor
//**********************************************************************
CDerivedQuantity::~CDerivedQuantity() {
}
