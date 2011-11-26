//============================================================================
// Name        : CAnnualMortalityRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAnnualMortalityRateProcess.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Layers/CLayerManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CAnnualMortalityRateProcess::CAnnualMortalityRateProcess()
// Default constructor
//**********************************************************************
CAnnualMortalityRateProcess::CAnnualMortalityRateProcess() {
  // Variables
  pLayer = 0;

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_M);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CAnnualMortalityRateProcess::validate()
// Validate the process
//**********************************************************************
void CAnnualMortalityRateProcess::validate() {
  try {
    // Base
    CProcess::validate();

    // Get our variables
    sLayer  = pParameterList->getString(PARAM_LAYER, true, "");

    pParameterList->fillVector(vYears, PARAM_YEARS);
    pParameterList->fillVector(vMs, PARAM_M);
    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Check Sizes
    if (vYears.size() != vMs.size())
      CError::errorListSameSize(PARAM_YEARS, PARAM_M);
    if (vCategoryNames.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

  } catch (string &Ex) {
    Ex = "CAnnualMortalityRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAnnualMortalityRateProcess::build()
// Build this process
//**********************************************************************
void CAnnualMortalityRateProcess::build() {
  try {
    // Base
    CProcess::build();

    // Get our Layer
    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Get selectivities and categories.
    CSelectivityManager::Instance()->fillVector(vSelectivities, vSelectivityNames);
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    // Build Refs
    pTimeStepManager = CTimeStepManager::Instance();

  } catch (string &Ex) {
    Ex = "CAnnualMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAnnualMortalityRateProcess::execute()
// Execute this process
//**********************************************************************
void CAnnualMortalityRateProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base Execute
    CProcess::execute();

    // Check if we run this year
    double dM = -1.0;
    for (int i = 0; i < (int)vYears.size(); ++i) {
      if (pTimeStepManager->getCurrentYear() == vYears[i]) {
        dM = vMs[i];
        break;
      }
    }

    if (CComparer::isEqual(dM, 1.0))
      return; // Don't run this year

    // Loop through World Grid (i, j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        double dLayerValue = 0.0;
        if (pLayer != 0)
          dLayerValue = pLayer->getValue(i, j);

        for(int k = 0; k < (int)vCategories.size(); ++k) {
          for (int m = 0; m < iBaseColCount; ++m) {
            double dCurrent = pBaseSquare->getValue(vCategories[k], m);
            dCurrent *= dM * vSelectivities[k]->getResult(m);

            if (pLayer != 0)
              dCurrent *= dLayerValue;

            pDiff->subValue(vCategories[k], m, dCurrent);
          } // for m
        } // for k
      } // for j
    } // for i

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CAnnualMortalityRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAnnualMortalityRateProcess::~CAnnualMortalityRateProcess()
// Destructor
//**********************************************************************
CAnnualMortalityRateProcess::~CAnnualMortalityRateProcess() {
}
