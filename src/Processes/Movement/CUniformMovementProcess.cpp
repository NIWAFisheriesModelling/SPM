//============================================================================
// Name        : CUniformMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CUniformMovementProcess.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CUniformMovementProcess::CUniformMovementProcess()
// Default Constructor
//**********************************************************************
CUniformMovementProcess::CUniformMovementProcess() {
}

//**********************************************************************
// void CUniformMovementProcess::validate()
// validate
//**********************************************************************
void CUniformMovementProcess::validate() {
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

  } catch (string Ex) {
    Ex = "CUniformMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CUniformMovementProcess::build()
// build
//**********************************************************************
void CUniformMovementProcess::build() {
  try {
    // Base Building
    CMovementProcess::build();

  } catch (string Ex) {
    Ex = "CUniformMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CUniformMovementProcess::execute()
// execute
//**********************************************************************
void CUniformMovementProcess::execute() {
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

        // Check if this square is ok
        //if (!checkUsableBaseSquare(i, j))
          //continue;
        // TODO: Fix this

        // Loop Through Categories and Ages
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {

            dCurrent = pBaseSquare->getValue( vCategoryIndex[k], l);
            if(CComparer::isZero(dCurrent))
              continue;
            dCurrent *= dProportion * vSelectivityIndex[k]->getResult(l);

            if (bHexMode)
              dCurrent /= 6;
            else
              dCurrent /= 4;

            // Move Up
            moveUp(i, j, vCategoryIndex[k], l, dCurrent);
            moveDown(i, j, vCategoryIndex[k], l, dCurrent);
            moveLeft(i, j, vCategoryIndex[k], l, dCurrent);
            moveRight(i, j, vCategoryIndex[k], l, dCurrent);

            if (bHexMode) {
              moveLeftUp(i, j, vCategoryIndex[k], l, dCurrent);
              moveLeftDown(i, j, vCategoryIndex[k], l, dCurrent);
            }
          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CUniformMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CUniformMovementProcess::~CUniformMovementProcess()
// Default De-Constructor
//**********************************************************************
CUniformMovementProcess::~CUniformMovementProcess() {
}
