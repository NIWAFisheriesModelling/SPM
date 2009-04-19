//============================================================================
// Name        : CCategoryTransitionRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CCategoryTransitionRateProcess.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"


//**********************************************************************
// CCategoryTransitionRateProcess::CCategoryTransitionRateProcess()
// Default constructor
//**********************************************************************
CCategoryTransitionRateProcess::CCategoryTransitionRateProcess() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FROM);
  pParameterList->registerAllowed(PARAM_TO);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CCategoryTransitionRateProcess::validate()
// validate the process
//**********************************************************************
void CCategoryTransitionRateProcess::validate() {
  try {
    // Base Validation
    CProcess::validate();

    // Populate our variables
    sLayer  = pParameterList->getString(PARAM_LAYER,true,""); //TODO: add as a multiplicative layer (somehow...)

    pParameterList->fillVector(vFrom, PARAM_FROM);
    pParameterList->fillVector(vTo, PARAM_TO);
    pParameterList->fillVector(vProportions, PARAM_PROPORTIONS);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Validate Sizes
    if (vFrom.size() != vTo.size())
      CError::errorListSameSize(PARAM_FROM, PARAM_TO);
    if (vFrom.size() != vProportions.size())
      CError::errorListSameSize(PARAM_FROM, PARAM_PROPORTIONS);
    if (vFrom.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_FROM, PARAM_SELECTIVITIES);

    // Local Validation
    for (int i = 0; i < (int)vProportions.size(); ++i) {
      if (vProportions[i] > 1.0)
        CError::errorGreaterThan(PARAM_PROPORTIONS, PARAM_ONE);

      // Register estimables
      registerEstimable(PARAM_PROPORTIONS, i, &vProportions[i]);
    }

  } catch (string Ex) {
    Ex = "CCategoryTransitionRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionRateProcess::build()
// Build the process
//**********************************************************************
void CCategoryTransitionRateProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Get our Category Indexes.
    foreach(string Category, vFrom) {
      vFromIndex.push_back(pWorld->getCategoryIndexForName(Category));
    }
    foreach(string Category, vTo) {
      vToIndex.push_back(pWorld->getCategoryIndexForName(Category));
    }

    // Get Selectivities
    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    foreach(string Label, vSelectivityNames) {
      vSelectivities.push_back(pSelectivityManager->getSelectivity(Label));
    }

    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

  } catch (string Ex) {
    Ex = "CCategoryTransitionRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionRateProcess::execute()
// Execute the process
//**********************************************************************
void CCategoryTransitionRateProcess::execute() {
  try {
    // Base execute
    CProcess::execute();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        for (int l = 0; l < iBaseColCount; ++l) {
          // Loop through vectors and make adjustment
          for (int k = 0; k < (int)vFromIndex.size(); ++k) {
            dCurrent = pBaseSquare->getValue(vFromIndex[k], l);
            if(CComparer::isZero(dCurrent))
               continue;

            // TODO: Add Multiplayer for layer here
            // dCurrent *= LOG(pLayer->getValue(i, j));

            dCurrent = dCurrent * vProportions[k] * vSelectivities[k]->getResult(l);
            pBaseSquare->subValue(vFromIndex[k], l, dCurrent);
            pBaseSquare->addValue(vToIndex[k], l, dCurrent);
          }
        }
      }
    }
  } catch (string Ex) {
    Ex = "CCategoryTransitionRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CCategoryTransitionRateProcess::~CCategoryTransitionRateProcess()
// Destructor
//**********************************************************************
CCategoryTransitionRateProcess::~CCategoryTransitionRateProcess() {
}
