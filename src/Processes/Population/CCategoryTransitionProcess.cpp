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
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

// TODO: This is now CatTransRate, New one to go here.

//**********************************************************************
// CCategoryTransitionProcess::CCategoryTransitionProcess(CCategoryTransitionProcess *Process = 0)
// Default Constructor
//**********************************************************************
CCategoryTransitionProcess::CCategoryTransitionProcess(CCategoryTransitionProcess *Process)
: CProcess(Process) {
  // Vars
  sFrom           = "";
  sTo             = "";
  dProportion     = 0.0;
  iFromIndex      = -1;
  iToIndex        = -1;

  registerEstimable(PARAM_PROPORTION, &dProportion);

  // Copy Construct
  if (Process != 0) {
    sFrom         = Process->getFrom();
    sTo           = Process->getTo();
    dProportion   = Process->getProportion();
  }
}

//**********************************************************************
// void CCategoryTransitionProcess::validate()
// Validate This Object
//**********************************************************************
void CCategoryTransitionProcess::validate() {
  try {
    // Base Validation
    CProcess::validate();

    // Validate
    if (bDependsOnLayer)
      CError::errorSupported(PARAM_LAYER_NAME);
    if (sFrom == "")
      CError::errorMissing(PARAM_FROM);
    if (sTo == "")
      CError::errorMissing(PARAM_TO);
    if (CComparer::isZero(dProportion))
      CError::errorMissing(PARAM_PROPORTION);
    if (getSelectivityCount() != 1)
      CError::errorMissing(PARAM_SELECTIVITY);
    if (getCategoryCount() != 0)
      CError::errorSupported(PARAM_CATEGORIES);
    if (sPenalty != "")
      CError::errorSupported(PARAM_PENALTY);
    if (dProportion > 1.0)
      CError::errorGreaterThan(PARAM_PROPORTION, PARAM_ONE);

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
    iFromIndex = pWorld->getCategoryIndexForName(getFrom());
    iToIndex   = pWorld->getCategoryIndexForName(getTo());

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
        pBase       = pWorld->getBaseSquare(i, j);
        // Check if usable
        if (!pBase->getEnabled())
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        for (int l = 0; l < iBaseColCount; ++l) {
          dCurrent = pBase->getValue(iFromIndex, l);
          if(CComparer::isZero(dCurrent))
             continue;
          dCurrent = dCurrent * dProportion * vSelectivityIndex[0]->getResult(l);
          pBase->subValue(iFromIndex, l, dCurrent);
          pBase->addValue(iToIndex, l, dCurrent);
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
