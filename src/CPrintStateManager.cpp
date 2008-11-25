//============================================================================
// Name        : CPrintStateManager.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CPrintStateManager.h >>
// $Date$
//============================================================================

// Local Headers
#include "CPrintStateManager.h"
#include "CRuntimeController.h"
#include "PrintStates/CPrintState.h"

// Single Static variable
boost::thread_specific_ptr<CPrintStateManager> CPrintStateManager::clInstance;
//CPrintStateManager* CPrintStateManager::clInstance = 0;

//**********************************************************************
// CPrintStateManager::CPrintStateManager()
// Default Constructor
//**********************************************************************
CPrintStateManager::CPrintStateManager() {
}

//**********************************************************************
// CPrintStateManager* CPrintStateManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CPrintStateManager* CPrintStateManager::Instance() {
/*  if (clInstance == 0)
    clInstance = new CPrintStateManager();
  return clInstance;*/

  if (clInstance.get() == 0)
    clInstance.reset(new CPrintStateManager());
  return clInstance.get();
}

//**********************************************************************
// void CPrintStateManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CPrintStateManager::Destroy() {
  /*if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }*/
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CPrintStateManager::addPrintState(CPrintState* PrintState)
// Add PrintState To our list
//**********************************************************************
void CPrintStateManager::addPrintState(CPrintState* PrintState) {
  vPrintStateList.push_back(PrintState);
}

//**********************************************************************
// void CPrintStateManager::validate()
// Validate PrintStates
//**********************************************************************
void CPrintStateManager::validate() {
  try {
    // Variables
    map<string, int>                mLabel;

    // Make sure we have no duplicate labels
    foreach(CPrintState *Print, vPrintStateList) {
      mLabel[Print->getLabel()] += 1;
      if (mLabel[Print->getLabel()] > 1)
        throw string(ERROR_DUPLICATE_LABEL + Print->getLabel());
    }

    // Validate Each print_state
    foreach(CPrintState *Print, vPrintStateList) {
      Print->validate();
    }

  } catch (string Ex) {
    Ex = "CPrintStateManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPrintStateManager::build()
// Build PrintStates
//**********************************************************************
void CPrintStateManager::build() {
  try {
    foreach(CPrintState *Print, vPrintStateList) {
      Print->build();
    }
  } catch (string Ex) {
    Ex = "CPrintStateManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPrintStateManager::execute(int Year, int Step)
// Execute PrintStates
//**********************************************************************
void CPrintStateManager::execute() {
  try {
    if (pRuntimeController->getCurrentState() != STATE_MODELLING)
      return;

    // Not allowed print_states in any mode but Basic Run
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;


    // Loop through print_states
    foreach(CPrintState *Print, vPrintStateList) {
        if (Print->getState() == STATE_MODELLING)
          Print->execute();
    }

  } catch (string Ex) {
    Ex = "CPrintStateManager.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPrintStateManager::execute(EState state)
// Print our Print-States
//**********************************************************************
void CPrintStateManager::execute(EState state) {
  try {
    // Not allowed print_states in any mode but Basic Run
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;

    foreach(CPrintState *print, vPrintStateList) {
      if (print->getState() == state)
        print->execute();
    }

  } catch (string Ex) {
    Ex = "CPrintStateManager.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPrintStateManager::~CPrintStateManager()
// Default De-Constructor
//**********************************************************************
CPrintStateManager::~CPrintStateManager() {

  // Clear our Memory
  foreach(CPrintState *Print, vPrintStateList) {
    delete Print;
  }
  vPrintStateList.clear();
}
