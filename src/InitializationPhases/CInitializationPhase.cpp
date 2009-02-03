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
#include "../Processes/CProcessManager.h"
#include "../Processes/CProcess.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

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
  pParameterList->registerAllowed(PARAM_PROCESSES);
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
    pProcessManager->fillVector(vProcesses, vProcessNames);

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
  cout << "Initialization Phase " << getLabel() << endl;
  cout << ">> " << iYears << " years to run" << endl;

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
