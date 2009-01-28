//============================================================================
// Name        : CInitializationPhase.cpp
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CInitializationPhase.h"
#include "../Processes/CProcessManager.h"
#include "../Processes/CProcess.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

//**********************************************************************
// CInitializationPhase::CInitializationPhase()
// Default constructor
//**********************************************************************
CInitializationPhase::CInitializationPhase() {
  // Vars
  iYears    = 0;

  // Register parameters
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_PROCESSES);
}

//**********************************************************************
// void CInitializationPhase::validate()
// Validate our Initialization Phase
//**********************************************************************
void CInitializationPhase::validate() {
  try {
    // Fill our Variables
    iYears  = pParameterList->getInt(PARAM_YEARS);
    pParameterList->fillVector(vProcessNames, PARAM_PROCESSES);

  } catch(string Ex) {
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
    CProcessManager *pProcessManager = CProcessManager::Instance();

    // Loop Through Our Population Processes and Get Pointers To Each
    foreach(string Label, vProcessNames) {
      vProcesses.push_back(pProcessManager->getProcess(Label));
    }

  } catch (string Ex) {
    Ex = "CInitializationPhase.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhase::execute()
//
//**********************************************************************
void CInitializationPhase::execute() {
  // Loop Through and Execute
  for (int i = 0; i < iYears; i++) {
    foreach(CProcess* Process, vProcesses) {
      Process->execute();
      pWorld->mergeDifferenceGrid();
    }
  }
}

//**********************************************************************
// CInitializationPhase::~CInitializationPhase()
// Destructor
//**********************************************************************
CInitializationPhase::~CInitializationPhase() {
}
