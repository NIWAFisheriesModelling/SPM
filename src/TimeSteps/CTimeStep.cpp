//============================================================================
// Name        : CTimeStep.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// $Date$
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "CTimeStep.h"
#include "../Processes/CProcessManager.h"
#include "../Processes/CProcess.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CTimeStep::CTimeStep()
// Default Constructor
//**********************************************************************
CTimeStep::CTimeStep() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_PROCESSES);
}

//**********************************************************************
// void CTimeStep::validate()
// Validate Time Step
//**********************************************************************
void CTimeStep::validate() {
  try {
    // Base
    CBaseExecute::validate();

    // Populate our parameters
    pParameterList->fillVector(vProcessNames, PARAM_PROCESSES);

  } catch(string Ex) {
    Ex = "CTimeStep.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStep::build()
//
//**********************************************************************
void CTimeStep::build() {
  try {
    // Now Lets Build Our Relationships
    CProcessManager *pProcessManager = CProcessManager::Instance();
    pProcessManager->fillVector(vProcesses, vProcessNames);

  } catch (string Ex) {
    Ex = "CTimeStep.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStep::execute()
// Execute This TimeStep
//**********************************************************************
void CTimeStep::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Loop Through and Execute
    foreach(CProcess* Process, vProcesses) {
      Process->execute();
      pWorld->mergeDifferenceGrid();
    }

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CTimeStep.execute()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CTimeStep::~CTimeStep()
// Default De-Constructor
//**********************************************************************
CTimeStep::~CTimeStep() {
}
