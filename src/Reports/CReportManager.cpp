//============================================================================
// Name        : CReportManager.cpp
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local headers
#include "CReportManager.h"
#include "CReport.h"
#include "../Helpers/ForEach.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CReportManager> CReportManager::clInstance;

//**********************************************************************
// CReportManager::CReportManager()
// Default Constructor
//**********************************************************************
CReportManager::CReportManager() {
}

//**********************************************************************
// CReportManager* CReportManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CReportManager* CReportManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CReportManager());
  return clInstance.get();
}

//**********************************************************************
// void CReportManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CReportManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CReportManager::addReporter(CReport *value)
// Add a Reporter to our vector
//**********************************************************************
void CReportManager::addReporter(CReport *value) {
  vReporters.push_back(value);
}

//**********************************************************************
// void CReportManager::clone(CReportManager *Manager)
// Clone our reporters
//**********************************************************************
void CReportManager::clone(CReportManager *Manager) {
  // TODO: Implement Clone Function
}

//**********************************************************************
// void CReportManager::validate()
// Validate our Reporters
//**********************************************************************
void CReportManager::validate() {
  try {
    foreach(CReport *Reporter, vReporters) {
      Reporter->validate();
    }

  } catch (string Ex) {
    Ex = "ReporterManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CReportManager::build()
// Build our Reporters
//**********************************************************************
void CReportManager::build() {
  try {
    foreach(CReport *Reporter, vReporters) {
      Reporter->build();
    }

    // Populate our other vectors
    foreach(CReport *Reporter, vReporters) {
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
// void CReportManager::execute()
// Execute Reporters
//**********************************************************************
void CReportManager::execute() {
  // Check for correct modes
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    return;
  // Check for correct state
  if (pRuntimeController->getCurrentState() != STATE_MODELLING)
    return;

  // Execute Modelling Reporters
  // Reporter will check Year/TimeStep itself
  // This is because some will run across multiple-timesteps
  foreach(CReport *Reporter, vModellingReporters) {
    Reporter->execute();
  }
}

//**********************************************************************
// void CReportManager::execute(EState state)
// Execute State-Based reporters
//**********************************************************************
void CReportManager::execute(EState state) {
  foreach(CReport *Reporter, vReporters) {
    if (Reporter->getExecutionState() == state)
      Reporter->execute();
  }
}

//**********************************************************************
// CReportManager::~CReportManager()
// Destructor
//**********************************************************************
CReportManager::~CReportManager() {
  foreach(CReport *Reporter, vReporters) {
    delete Reporter;
  }
}
