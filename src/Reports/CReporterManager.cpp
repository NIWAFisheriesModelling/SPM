//============================================================================
// Name        : CReporterManager.cpp
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local headers
#include "CReporterManager.h"
#include "CReporter.h"
#include "../Helpers/ForEach.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CReporterManager> CReporterManager::clInstance;

//**********************************************************************
// CReporterManager::CReporterManager()
// Default Constructor
//**********************************************************************
CReporterManager::CReporterManager() {
}

//**********************************************************************
// CReporterManager* CReporterManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CReporterManager* CReporterManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CReporterManager());
  return clInstance.get();
}

//**********************************************************************
// void CReporterManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CReporterManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CReporterManager::addReporter(CReporter *value)
// Add a Reporter to our vector
//**********************************************************************
void CReporterManager::addReporter(CReporter *value) {
  vReporters.push_back(value);
}

//**********************************************************************
// void CReporterManager::clone(CReporterManager *Manager)
// Clone our reporters
//**********************************************************************
void CReporterManager::clone(CReporterManager *Manager) {
  // TODO: Implement Clone Function
}

//**********************************************************************
// void CReporterManager::validate()
// Validate our Reporters
//**********************************************************************
void CReporterManager::validate() {
  try {
    foreach(CReporter *Reporter, vReporters) {
      Reporter->validate();
    }

  } catch (string Ex) {
    Ex = "ReporterManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CReporterManager::build()
// Build our Reporters
//**********************************************************************
void CReporterManager::build() {
  try {
    foreach(CReporter *Reporter, vReporters) {
      Reporter->build();
    }

    // Populate our other vectors
    foreach(CReporter *Reporter, vReporters) {
      switch(Reporter->getExecutionState()) {
      case STATE_MODELLING:
        vModellingReporters.push_back(Reporter);
        break;
      default:
        break;
      }
    }

  } catch (string Ex) {
    Ex = "CReporterManager.build()" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CReporterManager::execute()
// Execute Reporters
//**********************************************************************
void CReporterManager::execute() {
  // Check for correct modes
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    return;
  // Check for correct state
  if (pRuntimeController->getCurrentState() != STATE_MODELLING)
    return;

  // Execute Modelling Reporters
  // Reporter will check Year/TimeStep itself
  // This is because some will run across multiple-timesteps
  foreach(CReporter *Reporter, vModellingReporters) {
    Reporter->execute();
  }
}

//**********************************************************************
// void CReporterManager::execute(EState state)
// Execute State-Based reporters
//**********************************************************************
void CReporterManager::execute(EState state) {
  foreach(CReporter *Reporter, vReporters) {
    if (Reporter->getExecutionState() == state)
      Reporter->execute();
  }
}

//**********************************************************************
// CReporterManager::~CReporterManager()
// Destructor
//**********************************************************************
CReporterManager::~CReporterManager() {
  foreach(CReporter *Reporter, vReporters) {
    delete Reporter;
  }
}
