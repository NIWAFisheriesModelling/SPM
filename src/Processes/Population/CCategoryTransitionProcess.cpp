//============================================================================
// Name        : CCategoryTransitionProcess.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CCategoryTransitionProcess.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CCategoryTransitionProcess::CCategoryTransitionProcess()
// Default Constructor
//**********************************************************************
CCategoryTransitionProcess::CCategoryTransitionProcess() {

  // Register estimables
  registerEstimable(PARAM_N, &dN);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FROM);
  pParameterList->registerAllowed(PARAM_TO);
  pParameterList->registerAllowed(PARAM_N);
  pParameterList->registerAllowed(PARAM_SELECTIVITY);
}

//**********************************************************************
// void CCategoryTransitionProcess::validate()
// Validate This Object
//**********************************************************************
void CCategoryTransitionProcess::validate() {
  try {
    // Base Validation
    CProcess::validate();

    // Populate our variables
    sFrom         = pParameterList->getString(PARAM_FROM);
    sTo           = pParameterList->getString(PARAM_TO);
    dN            = pParameterList->getDouble(PARAM_N);
    sSelectivity  = pParameterList->getString(PARAM_SELECTIVITY);

  } catch(string Ex) {
    Ex = "CCategoryTransitionProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionProcess::build()
// Build our Relationships and Indexes
//**********************************************************************
void CCategoryTransitionProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Get our Category Indexes.
    iFromIndex    = pWorld->getCategoryIndexForName(sFrom);
    iToIndex      = pWorld->getCategoryIndexForName(sTo);

    pSelectivity  = CSelectivityManager::Instance()->getSelectivity(sSelectivity);

  } catch(string Ex) {
    Ex = "CCategoryTransitionProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionProcess::execute()
// Execute This Process
//**********************************************************************
void CCategoryTransitionProcess::execute() {
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
        // Check if usable
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        for (int l = 0; l < iBaseColCount; ++l) {
          // TODO: Add Penalty if dN > Current Population
          pBaseSquare->subValue(iFromIndex, l, dN * vSelectivityIndex[0]->getResult(l));
          pBaseSquare->addValue(iToIndex, l, dN * vSelectivityIndex[0]->getResult(l));
        }
      }
    }
#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CCategoryTransitionProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CCategoryTransitionProcess::~CCategoryTransitionProcess()
// Default De-Constructor
//**********************************************************************
CCategoryTransitionProcess::~CCategoryTransitionProcess() {
}
