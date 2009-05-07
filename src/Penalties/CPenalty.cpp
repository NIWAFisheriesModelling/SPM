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
#include <CMath>

//**********************************************************************
// CPenalty::CPenalty()
// Default Constructor
//**********************************************************************
CPenalty::CPenalty() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MULTIPLIER);
  pParameterList->registerAllowed(PARAM_LOG_SCALE);
}

//**********************************************************************
// void CPenalty::validate()
// validate
//**********************************************************************
void CPenalty::validate() {
  try {
    // Base
    CBaseValidate::validate();

    // Get local Parameters
    dMultiplier   = pParameterList->getDouble(PARAM_MULTIPLIER, true, 1.0);
    bLogScale     = pParameterList->getBool(PARAM_LOG_SCALE, true, false);

  } catch (string Ex) {
    Ex = "CPenalty.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPenalty::trigger(string Label, double Value)
// trigger The penalty
//**********************************************************************
void CPenalty::trigger(string Label, double Value1, double Value2) {
#ifndef OPTIMIZE
  try {
#endif
    // Value should never be 0
    //if (CComparer::isZero(Value))
    //  CError::errorEqualTo(PARAM_PENALTY, PARAM_ZERO);

    // Assign Variables
    string sFullLabel = sLabel + "(" + Label + ")";
    double dValue;

    if(bLogScale) {
      dValue = abs((log(Value1) - log(Value2)) * dMultiplier);
    } else {
      dValue = abs((Value1 - Value2) * dMultiplier);
    }

    // Flag Penalty Manager
    CPenaltyManager *pPenaltyManager = CPenaltyManager::Instance();
    pPenaltyManager->flagPenalty(sFullLabel, dValue);

#ifndef OPTIMIZE
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
