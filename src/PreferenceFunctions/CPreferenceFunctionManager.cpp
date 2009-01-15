//============================================================================
// Name        : CPreferenceFunctionManager.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : << See CPreferenceFunctionManager.h >>
// $Date: 2009-01-12 11:44:49 +1300 (Mon, 12 Jan 2009) $
//============================================================================

// Local Headers
#include "CPreferenceFunctionManager.h"
#include "CPreferenceFunction.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Singleton Instance
boost::thread_specific_ptr<CPreferenceFunctionManager> CPreferenceFunctionManager::clInstance;

//**********************************************************************
// CPreferenceFunctionManager::CPreferenceFunctionManager()
// Default Constructor
//**********************************************************************
CPreferenceFunctionManager::CPreferenceFunctionManager() {
}

//**********************************************************************
// CPreferenceFunctionManager* CPreferenceFunctionManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CPreferenceFunctionManager* CPreferenceFunctionManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CPreferenceFunctionManager());
  return clInstance.get();
}

//**********************************************************************
// void CPreferenceFunctionManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CPreferenceFunctionManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CPreferenceFunctionManager::addProcess(CPreferenceFunction *Process)
// Add DirectedProcess to our list
//**********************************************************************
void CPreferenceFunctionManager::addProcess(CPreferenceFunction *Process) {
  vPreferenceFunctions.push_back(Process);
}

//**********************************************************************
// CPreferenceFunction* CPreferenceFunctionManager::getProcess(int index)
// Get A Process by Index
//**********************************************************************
CPreferenceFunction* CPreferenceFunctionManager::getProcess(int index) {
  try {
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (index >= (int)vPreferenceFunctions.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_DIRECTED_PROCESSES);

    return vPreferenceFunctions[index];

  } catch (string Ex) {
    Ex = "CPreferenceFunctionManager.getProcess()->" + Ex;
  }

  return 0;
}

//**********************************************************************
// CPreferenceFunction* CPreferenceFunctionManager::getProcess(string Label)
// get The Process Pointer For Label
//**********************************************************************
CPreferenceFunction* CPreferenceFunctionManager::getProcess(string Label) {
  try {
    // Loop Through And Find
    foreach(CPreferenceFunction *Process, vPreferenceFunctions) {
      if (Process->getLabel() == Label)
        return Process;
    }

    throw string(ERROR_UNKNOWN_PROCESS + Label);

  } catch (string Ex) {
    Ex = "CPreferenceFunctionManager.getProcess()->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// void CPreferenceFunctionManager::clone(CPreferenceFunctionManager *Manager)
// Load our Process Manager From Another One. Multi-Threaded Thing
//**********************************************************************
void CPreferenceFunctionManager::clone(CPreferenceFunctionManager *Manager) {
  try {

    // Copy our Directed Processes
    for (int i = 0; i < Manager->getProcessCount(); ++i) {
      CPreferenceFunction *pProcess = Manager->getProcess(i);
      vPreferenceFunctions.push_back(pProcess->clone());
    }

  } catch (string Ex) {
    Ex = "CPreferenceFunctionManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceFunctionManager::validate()
// validate
//**********************************************************************
void CPreferenceFunctionManager::validate() {
  try {
    // Loop through and Validate
    vector<CPreferenceFunction*>::iterator vPtr = vPreferenceFunctions.begin();
    while (vPtr != vPreferenceFunctions.end()) {
      (*vPtr)->validate();
      vPtr++;
    }

  } catch (string Ex) {
    Ex = "CPreferenceFunctionManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceFunctionManager::build()
// build
//**********************************************************************
void CPreferenceFunctionManager::build() {
  try {
    // Loop through and build
    vector<CPreferenceFunction*>::iterator vPtr = vPreferenceFunctions.begin();
    while (vPtr != vPreferenceFunctions.end()) {
      (*vPtr)->build();
      vPtr++;
    }

  } catch (string Ex) {
    Ex = "CPreferenceFunctionManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPreferenceFunctionManager::~CPreferenceFunctionManager()
// Default De-Constructor
//**********************************************************************
CPreferenceFunctionManager::~CPreferenceFunctionManager() {
  vector<CPreferenceFunction*>::iterator vPtr;
  vPtr = vPreferenceFunctions.begin();
  while (vPtr != vPreferenceFunctions.end()) {
    delete (*vPtr);
    vPtr++;
  }
  vPreferenceFunctions.clear();
}
