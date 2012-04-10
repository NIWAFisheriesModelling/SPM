//============================================================================
// Name        : CAdjacentCellMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CAdjacentCellMovementProcess.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CAdjacentCellMovementProcess::CAdjacentCellMovementProcess()
// Default Constructor
//**********************************************************************
CAdjacentCellMovementProcess::CAdjacentCellMovementProcess() {
}

//**********************************************************************
// void CAdjacentCellMovementProcess::validate()
// validate
//**********************************************************************
void CAdjacentCellMovementProcess::validate() {
  try {
    // Base Validation
    CMovementProcess::validate();

    // Local Validation
    if (getCategoryCount() == 0)
      CError::errorMissing(PARAM_CATEGORIES);
    if (getSelectivityCount() == 0)
      CError::errorMissing(PARAM_SELECTIVITIES);
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

  } catch (string &Ex) {
    Ex = "CAdjacentCellMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAdjacentCellMovementProcess::build()
// build
//**********************************************************************
void CAdjacentCellMovementProcess::build() {
  try {
    // Base Building
    CMovementProcess::build();

  } catch (string &Ex) {
    Ex = "CAdjacentCellMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAdjacentCellMovementProcess::execute()
// execute
//**********************************************************************
void CAdjacentCellMovementProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif

    // Base Execution
    CMovementProcess::execute();

    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Squares
        pBaseSquare = pWorld->getBaseSquare(i, j);
        pDiff       = pWorld->getDifferenceSquare(i, j);

        if (!pBaseSquare->getEnabled())
          continue;

        //TODO: Need to move individuals from cells that are defined by a categorical layer. Currently this moves all cells
        //      A seconds numeric layer defines the relative proportions to 'diffuse' So, instead of using 0.25 for
        //      each of the up/down/left/right cells, make these proportional to the layer values in the top/bottom/left/right
        //      cells.

        // Loop Through Categories and Ages
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {

            dCurrent = pBaseSquare->getValue( vCategoryIndex[k], l);
            if(CComparer::isZero(dCurrent))
              continue;
            dCurrent *= 0.25 * dProportion * vSelectivityIndex[k]->getResult(l);

            // Move Up
            moveUp(i, j, vCategoryIndex[k], l, dCurrent);
            moveDown(i, j, vCategoryIndex[k], l, dCurrent);
            moveLeft(i, j, vCategoryIndex[k], l, dCurrent);
            moveRight(i, j, vCategoryIndex[k], l, dCurrent);

          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CAdjacentCellMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAdjacentCellMovementProcess::~CAdjacentCellMovementProcess()
// Default De-Constructor
//**********************************************************************
CAdjacentCellMovementProcess::~CAdjacentCellMovementProcess() {
}
