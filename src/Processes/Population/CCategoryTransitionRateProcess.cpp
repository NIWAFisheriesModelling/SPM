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

//**********************************************************************
// CCategoryTransitionRateProcess::CCategoryTransitionRateProcess()
// Default constructor
//**********************************************************************
CCategoryTransitionRateProcess::CCategoryTransitionRateProcess() {
  // Register estimables
  registerEstimable(PARAM_PROPORTION, &dProportion);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FROM);
  pParameterList->registerAllowed(PARAM_TO);
  pParameterList->registerAllowed(PARAM_PROPORTION);
  pParameterList->registerAllowed(PARAM_SELECTIVITY);
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
    sFrom         = pParameterList->getString(PARAM_FROM);
    sTo           = pParameterList->getString(PARAM_TO);
    dProportion   = pParameterList->getDouble(PARAM_PROPORTION);
    sSelectivity  = pParameterList->getString(PARAM_SELECTIVITY);

    // Local Validation
    if (dProportion > 1.0)
      CError::errorGreaterThan(PARAM_PROPORTION, PARAM_ONE);

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
    iFromIndex    = pWorld->getCategoryIndexForName(sFrom);
    iToIndex      = pWorld->getCategoryIndexForName(sTo);

    pSelectivity  = CSelectivityManager::Instance()->getSelectivity(sSelectivity);
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
          dCurrent = pBaseSquare->getValue(iFromIndex, l);
          if(CComparer::isZero(dCurrent))
             continue;
          dCurrent = dCurrent * dProportion * pSelectivity->getResult(l);
          pBaseSquare->subValue(iFromIndex, l, dCurrent);
          pBaseSquare->addValue(iToIndex, l, dCurrent);
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
