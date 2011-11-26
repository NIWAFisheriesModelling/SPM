//============================================================================
// Name        : CAgeingProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CAgeingProcess.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CAgeingProcess::CAgeingProcess()
// Default Constructor
//**********************************************************************
CAgeingProcess::CAgeingProcess() {
  // Register Allowed Parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
}

//**********************************************************************
// void CAgeingProcess:validate()
// Validate This
//**********************************************************************
void CAgeingProcess::validate() {
  try {
    // Call Base Validate
    CProcess::validate();

    // populate our vector
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);

  } catch(string &Ex) {
    Ex = "CAgeingProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeingProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CAgeingProcess::build() {
  try {
    // Call Our Base Build
    CProcess::build();

    // We Remove 1 Because We Don't Touch Last Square
    // This Is because of the age_plus concept
    iBaseColCount--;

  } catch(string &Ex) {
    Ex = "CAgeingProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeingProcess::execute()
// execute this Process
//**********************************************************************
void CAgeingProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base Execute
    CProcess::execute();

    // Loop through World Grid (i, j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        // Loop Through Categories and Ages (vPtr, k)
        vector<int>::iterator vPtr = vCategoryIndex.begin();
        while (vPtr != vCategoryIndex.end()) {

          for (int k = 0; k < iBaseColCount; ++k) {
            dCurrent = pBaseSquare->getValue( (*vPtr), k);
            if(CComparer::isZero(dCurrent))
               continue;
            pDiff->subValue( (*vPtr), k, dCurrent);
            pDiff->addValue( (*vPtr), (k+1), dCurrent);
          }

          if (!pBaseSquare->getAgePlus())
            pDiff->subValue( (*vPtr), iBaseColCount, pBaseSquare->getValue((*vPtr), iBaseColCount));

          vPtr++;
        }
      }
    }
#ifndef OPTIMIZE
  } catch(string &Ex) {
    Ex = "CAgeingProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAgeingProcess::~CAgeingProcess()
// Default De-Constructor
//**********************************************************************
CAgeingProcess::~CAgeingProcess() {
}
