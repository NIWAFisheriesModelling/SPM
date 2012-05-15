//============================================================================
// Name        : CMigrationMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CMigrationMovementProcess.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Layers/CLayerManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CMigrationMovementProcess::CMigrationMovementProcess()
// Default Constructor
//**********************************************************************
CMigrationMovementProcess::CMigrationMovementProcess() {

    //Default values
    pSourceLayer = 0;
    pSinkLayer = 0;

    // Register user allowed parameters
    pParameterList->registerAllowed(PARAM_CATEGORIES);
    pParameterList->registerAllowed(PARAM_SELECTIVITIES);
    pParameterList->registerAllowed(PARAM_PROPORTION);
    pParameterList->registerAllowed(PARAM_SINK_LAYER);
    pParameterList->registerAllowed(PARAM_SOURCE_LAYER);
}

//**********************************************************************
// void CMigrationMovementProcess::validate()
// validate
//**********************************************************************
void CMigrationMovementProcess::validate() {
  try {

    // Get our Variables
    sSinkLayer = pParameterList->getString(PARAM_SINK_LAYER);
    sSourceLayer = pParameterList->getString(PARAM_SOURCE_LAYER);

    dProportion = pParameterList->getDouble(PARAM_PROPORTION);

    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Base Validation
    CMovementProcess::validate();

    // Local Validation
    if (getCategoryCount() == 0)
      CError::errorMissing(PARAM_CATEGORIES);
    if (getSelectivityCount() == 0)
      CError::errorMissing(PARAM_SELECTIVITIES);
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    if (getProportion() < 0.0)
      CError::errorLessThan(PARAM_PROPORTION, PARAM_ZERO);
    if (getProportion() > 1.0)
      CError::errorGreaterThan(PARAM_PROPORTION, PARAM_ONE);

  } catch (string &Ex) {
    Ex = "CMigrationMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMigrationMovementProcess::build()
// build
//**********************************************************************
void CMigrationMovementProcess::build() {
  try {
    // Base Building
    CMovementProcess::build();

    // Get selectivities and categories.
    CSelectivityManager::Instance()->fillVector(vSelectivities, vSelectivityNames);
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    // Get our Layers
    if (sSinkLayer != "")
      pSinkLayer = CLayerManager::Instance()->getNumericLayer(sSinkLayer);
    if (sSourceLayer != "")
      pSourceLayer = CLayerManager::Instance()->getNumericLayer(sSourceLayer);

  } catch (string &Ex) {
    Ex = "CMigrationMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMigrationMovementProcess::execute()
// execute
//**********************************************************************
void CMigrationMovementProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif

    CMovementProcess::execute();

// iterate over source layer and calc. max_layer_source_value
// iterate over sink layer and calc. total_layer_sink_value
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Squares
        pBaseSquare = pWorld->getBaseSquare(i, j);
        pDiff       = pWorld->getDifferenceSquare(i, j);

        if (!pBaseSquare->getEnabled())
          continue;

        //dSourceLayerMax = max(dSourceLayerMax, pSourceLayer->getValue(i, j));
        //dSinkLayerTotal += pSinkLayer->getValue(i, j);
      }
    }

// iterate over the world, and get
//    number at age and category value
//    multiply by source layer/max_layer_value
//    multiply by selectivity
//  and sum the result for age and category (call total)




// iterate over the world, and allocate total to
//   all cells with proportion sink layer value / total
//


#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CMigrationMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CMigrationMovementProcess::~CMigrationMovementProcess()
// Default De-Constructor
//**********************************************************************
CMigrationMovementProcess::~CMigrationMovementProcess() {
}
