//============================================================================
// Name        : CConstantMortalityRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CConstantMortalityRateProcess.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

// TODO: This is a copy of CNaturalMortalityProcess. It probably need to be migrated properly

//**********************************************************************
// CConstantMortalityRateProcess::CConstantMortalityRateProcess()
// Default Constructor
//**********************************************************************
CConstantMortalityRateProcess::CConstantMortalityRateProcess() {
  // TODO: Implement this
  // Variables
  pGrid            = 0;
  dM               = 0.0;
  pLayer           = 0;

  // Register Estimables
  registerEstimable(PARAM_M, &dM);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_M);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);

}

//**********************************************************************
// void CConstantMortalityRateProcess::validate()
// Validate our process
//**********************************************************************
void CConstantMortalityRateProcess::validate() {
// TODO: Implement this
  try {
    // Base Validate
    CProcess::validate();

    // Get our parameters
    dM      = pParameterList->getDouble(PARAM_M);
    sLayer  = pParameterList->getString(PARAM_LAYER, true, "");

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    // Local Validation
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

  } catch (string Ex) {
    Ex = "CConstantMortalityRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantMortalityRateProcess::build()
// Build our process
//**********************************************************************
void CConstantMortalityRateProcess::build() {
// TODO: Implement this
  try {
    // Base Build
    CProcess::build();

    // Allocate our Grid
    if (pGrid == 0) {
      // Allocate Space for our X (Height) Y (Width) Grid
      pGrid = new CWorldSquare*[iWorldHeight];
      for (int i = 0; i < iWorldHeight; ++i) {
        pGrid[i] = new CWorldSquare[iWorldWidth];
      }

      // Build our Grid
      for (int i = 0; i < iWorldHeight; ++i)
        for (int j = 0; j < iWorldWidth; ++j)
          pGrid[i][j].build();
    }

    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Rebuild
    rebuild();

  } catch (string Ex) {
    Ex = "CConstantMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNaturalMortalityProcess::rebuild()
// Rebuild
//**********************************************************************
void CConstantMortalityRateProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif
    // Populate Grid With Values
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Our Selectivity Result
            dSelectivityResult = vSelectivityIndex[k]->getResult(l);
            // Calculate Our Value
            double dValue = dM*dSelectivityResult;

            // Multiply it by Layer Value
            if (pLayer != 0)
              dValue *= pLayer->getValue(i, j);

            // Convert To Proportion
            dValue = 1-exp(-dValue);

            // Make sure it's between 0 and 1
            if (dValue < 0.0)
              dValue = 0.0;
            if (dValue > 1.0)
              dValue = 1.0;

            // Assign it to our Grid
            pGrid[i][j].setValue(vCategoryIndex[k], l, dValue);
          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CConstantMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CConstantMortalityRateProcess::execute()
// Execute our process
//**********************************************************************
void CConstantMortalityRateProcess::execute() {
// TODO: Implement this
#ifndef OPTIMIZE
  try {
#endif
    // Populate Grid With Values
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Our Selectivity Result
            dSelectivityResult = vSelectivityIndex[k]->getResult(l);
            // Calculate Our Value
            double dValue = dM*dSelectivityResult;

            // Multiply it by Layer Value
            if (pLayer != 0)
              dValue *= pLayer->getValue(i, j);

            // Convert To Proportion
            dValue = 1-exp(-dValue);

            // Make sure it's between 0 and 1
            if (dValue < 0.0)
              dValue = 0.0;
            if (dValue > 1.0)
              dValue = 1.0;

            // Assign it to our Grid
            pGrid[i][j].setValue(vCategoryIndex[k], l, dValue);
          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CConstantMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CConstantMortalityRateProcess::~CConstantMortalityRateProcess()
// Destructor
//**********************************************************************
CConstantMortalityRateProcess::~CConstantMortalityRateProcess() {
}
