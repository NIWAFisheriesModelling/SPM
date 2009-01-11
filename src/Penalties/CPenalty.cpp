//============================================================================
// Name        : CPenalty.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CPenalty.h"
#include "CPenaltyManager.h"
#include "../Processes/CProcessManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/CComparer.h"

//**********************************************************************
// CPenalty::CPenalty(CPenalty *Penalty = 0)
// Default Constructor
//**********************************************************************
CPenalty::CPenalty(CPenalty *Penalty)
: CBaseBuildableObject(Penalty) {

  // Variables
  bLogScale             = false;
  dMultiplier           = -1.0;

  // Copy Construct
  if (Penalty != 0) {
    bLogScale   = Penalty->getLogScale();
    dMultiplier = Penalty->getMultiplier();
  }
}

//**********************************************************************
// void CPenalty::validate()
// validate
//**********************************************************************
void CPenalty::validate() {
  try {
    if (sLabel == "")
      CError::errorMissing(PARAM_LABEL);
    if (CComparer::isEqual(dMultiplier, -1.0))
      CError::errorMissing(PARAM_MULTIPLIER);

  } catch (string Ex) {
    Ex = "CPenalty.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPenalty::build()
// build
//**********************************************************************
void CPenalty::build() {
  try {

  } catch (string Ex) {
    Ex = "CPenalty.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPenalty::execute(string Label, double Value)
// execute (Flag this Penalty - sort of)
//**********************************************************************
void CPenalty::execute(string Label, double Value) {
#ifndef OPTIMISE
  try {
#endif
    // Value should Never be 0
    if (CComparer::isZero(Value))
      CError::errorEqualTo(PARAM_PENALTY, PARAM_ZERO);

    // Assign Variables
    string sFullLabel = sLabel + "(" + Label + ")";
    double dValue     = Value * dMultiplier;

    //if (bLogScale)
    // ToDo: Add LogScale Code

    // Flag Penalty Manager
    CPenaltyManager *pPenaltyManager = CPenaltyManager::Instance();
    pPenaltyManager->flagPenalty(sFullLabel, dValue);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CPenalty.execute(" + sLabel + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CPenalty::~CPenalty()
// Default De-Constructor
//**********************************************************************
CPenalty::~CPenalty() {
}
