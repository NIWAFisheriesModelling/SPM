//============================================================================
// Name        : CInitializationPhase.cpp
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "CInitializationPhase.h"
#include "../TimeSteps/CTimeStep.h"
#include "../TimeSteps/CTimeStepManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../DerivedQuantities/CDerivedQuantityManager.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CInitializationPhase::CInitializationPhase()
// Default constructor
//**********************************************************************
CInitializationPhase::CInitializationPhase() {
  // Vars
  iYears    = 0;

  // Register parameters
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_TIME_STEPS);
}

//**********************************************************************
// void CInitializationPhase::validate()
// Validate our Initialization Phase
//**********************************************************************
void CInitializationPhase::validate() {
  try {
    // Base
    CBaseExecute::validate();

    // Fill our Variables
    iYears  = pParameterList->getInt(PARAM_YEARS);
    pParameterList->fillVector(vTimeStepNames, PARAM_TIME_STEPS);

  } catch(string &Ex) {
    Ex = "CInitializationPhase.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhase::build()
// Build this Initilization phase
//**********************************************************************
void CInitializationPhase::build() {
  try {
    // Now Lets Build Our Relationships
    CTimeStepManager *pTimeStepManager = CTimeStepManager::Instance();
    pTimeStepManager->fillVector(vTimeStepNames, vTimeSteps);

  } catch (string &Ex) {
    Ex = "CInitializationPhase.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhase::execute()
// Execute the TimeSteps for this initialisation phase
//**********************************************************************
void CInitializationPhase::execute() {
  CDerivedQuantityManager *pDerivedQuantityManager = CDerivedQuantityManager::Instance();

  // Loop Through and Execute
  for (int i = 0; i < iYears; i++) {
    foreach(CTimeStep *timeStep, vTimeSteps) {
      timeStep->execute();
    }

    pDerivedQuantityManager->calculate(true);
  }
}

//**********************************************************************
// CInitializationPhase::~CInitializationPhase()
// Destructor
//**********************************************************************
CInitializationPhase::~CInitializationPhase() {
}
