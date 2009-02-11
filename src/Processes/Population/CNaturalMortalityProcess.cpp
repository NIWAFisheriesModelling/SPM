//============================================================================
// Name        : CNaturalMortalityProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CNaturalMortalityProcess.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

// TODO: Migrate this to constant mortality rate process

//**********************************************************************
// CNaturalMortalityProcess::CNaturalMortalityProcess()
// Default Constructor
//**********************************************************************
CNaturalMortalityProcess::CNaturalMortalityProcess() {
  // Variables
  pGrid            = 0;
  dM               = 0.0;
  bDependsOnLayer  = false;
  pLayer           = 0;

  // Register Estimables
  registerEstimable(PARAM_M, &dM);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_M);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
}
//**********************************************************************
// void CNaturalMortalityProcess::validate()
// Validate
//**********************************************************************
void CNaturalMortalityProcess::validate() {
  try {
    // Base Validate
    CProcess::validate();

    // Get our parameters
    dM    = pParameterList->getDouble(PARAM_M);

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    // Local Validation
    if (getCategoryCount() != getSelectivityCount())
      throw string(ERROR_EQUAL_CATEGORY_SELECTIVITY); // TODO: FIX THIS

  } catch (string Ex) {
    Ex = "CNaturalMortalityProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNaturalMortalityProcess::build()
// Build our Relationships and Indexes
//**********************************************************************
void CNaturalMortalityProcess::build() {
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

    // Rebuild
    rebuild();

  } catch (string Ex) {
    Ex = "CNaturalMortalityProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNaturalMortalityProcess::rebuild()
// Rebuild
//**********************************************************************
void CNaturalMortalityProcess::rebuild() {
#ifndef OPTIMISE
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
            if (bDependsOnLayer)
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

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CNaturalMortalityProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CNaturalMortalityProcess::execute()
// Execute
//**********************************************************************
void CNaturalMortalityProcess::execute() {
#ifndef OPTIMISE
  try {
#endif
    // Base execute
    CProcess::execute();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        // Check Square Ok
        if (!pBaseSquare->getEnabled())
          continue;
        if ( (bDependsOnLayer) && (!pLayer->checkSpace(i, j)) )
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        // Loop Through Categories and Ages
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Current Value
            dCurrent = pBaseSquare->getValue( vCategoryIndex[k], l);

            // Check 0
            if(CComparer::isZero(dCurrent))
               continue;

            // Get Amount To Subtract
            dCurrent *= pGrid[i][j].getValue(vCategoryIndex[k], l);

            // Do Add/Subs
            pDiff->subValue( vCategoryIndex[k], l, dCurrent);
          }
        }
      }
    }
#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CNaturalMortalityProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CNaturalMortalityProcess::~CNaturalMortalityProcess()
// Default De-Constructor
//**********************************************************************
CNaturalMortalityProcess::~CNaturalMortalityProcess() {

  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iWorldHeight; ++i) {
      delete [] pGrid[i];
      pGrid[i] = 0;
    }
    delete [] pGrid;
  }
}
