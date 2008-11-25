//============================================================================
// Name        : CDirectedProcessManager.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : << See CDirectedProcessManager.h >>
// $Date$
//============================================================================

// Local Headers
#include "CDirectedProcessManager.h"
#include "DirectedProcesses/CDirectedProcess.h"

// Singleton Instance
boost::thread_specific_ptr<CDirectedProcessManager> CDirectedProcessManager::clInstance;

//**********************************************************************
// CDirectedProcessManager::CDirectedProcessManager()
// Default Constructor
//**********************************************************************
CDirectedProcessManager::CDirectedProcessManager() {
}

//**********************************************************************
// CDirectedProcessManager* CDirectedProcessManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CDirectedProcessManager* CDirectedProcessManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CDirectedProcessManager());
  return clInstance.get();
}

//**********************************************************************
// void CDirectedProcessManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CDirectedProcessManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CDirectedProcessManager::addProcess(CDirectedProcess *Process)
// Add DirectedProcess to our list
//**********************************************************************
void CDirectedProcessManager::addProcess(CDirectedProcess *Process) {
  vDirectedProcessList.push_back(Process);
}

//**********************************************************************
// CDirectedProcess* CDirectedProcessManager::getProcess(int index)
// Get A Process by Index
//**********************************************************************
CDirectedProcess* CDirectedProcessManager::getProcess(int index) {
  try {
    if (index < 0)
      errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (index >= (int)vDirectedProcessList.size())
      errorGreaterThanEqualTo(PARAM_INDEX, PARAM_DIRECTED_PROCESSES);

    return vDirectedProcessList[index];

  } catch (string Ex) {
    Ex = "CDirectedProcessManager.getProcess()->" + Ex;
  }

  return 0;
}

//**********************************************************************
// CDirectedProcess* CDirectedProcessManager::getProcess(string Label)
// get The Process Pointer For Label
//**********************************************************************
CDirectedProcess* CDirectedProcessManager::getProcess(string Label) {
  try {
    // Loop Through And Find
    foreach(CDirectedProcess *Process, vDirectedProcessList) {
      if (Process->getLabel() == Label)
        return Process;
    }

    throw string(ERROR_UNKNOWN_PROCESS + Label);

  } catch (string Ex) {
    Ex = "CDirectedProcessManager.getProcess()->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// void CDirectedProcessManager::clone(CDirectedProcessManager *Manager)
// Load our Process Manager From Another One. Multi-Threaded Thing
//**********************************************************************
void CDirectedProcessManager::clone(CDirectedProcessManager *Manager) {
  try {

    // Copy our Directed Processes
    for (int i = 0; i < Manager->getProcessCount(); ++i) {
      CDirectedProcess *pProcess = Manager->getProcess(i);
      vDirectedProcessList.push_back(pProcess->clone());
    }

  } catch (string Ex) {
    Ex = "CDirectedProcessManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDirectedProcessManager::validate()
// validate
//**********************************************************************
void CDirectedProcessManager::validate() {
  try {
    // Loop through and Validate
    vector<CDirectedProcess*>::iterator vPtr = vDirectedProcessList.begin();
    while (vPtr != vDirectedProcessList.end()) {
      (*vPtr)->validate();
      vPtr++;
    }

  } catch (string Ex) {
    Ex = "CDirectedProcessManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDirectedProcessManager::build()
// build
//**********************************************************************
void CDirectedProcessManager::build() {
  try {
    // Loop through and build
    vector<CDirectedProcess*>::iterator vPtr = vDirectedProcessList.begin();
    while (vPtr != vDirectedProcessList.end()) {
      (*vPtr)->build();
      vPtr++;
    }

  } catch (string Ex) {
    Ex = "CDirectedProcessManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDirectedProcessManager::~CDirectedProcessManager()
// Default De-Constructor
//**********************************************************************
CDirectedProcessManager::~CDirectedProcessManager() {
  vector<CDirectedProcess*>::iterator vPtr;
  vPtr = vDirectedProcessList.begin();
  while (vPtr != vDirectedProcessList.end()) {
    delete (*vPtr);
    vPtr++;
  }
  vDirectedProcessList.clear();
}
