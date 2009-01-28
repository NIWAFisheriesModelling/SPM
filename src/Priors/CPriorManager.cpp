//============================================================================
// Name        : CPriorManager.cpp
// Author      : S.Rasmussen
// Date        : 10/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CPriorManager.h"
#include "CPrior.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Single Static variable
boost::thread_specific_ptr<CPriorManager> CPriorManager::clInstance;

//**********************************************************************
// CPriorManager::CPriorManager()
// Default Constructor
//**********************************************************************
CPriorManager::CPriorManager() {
}

//**********************************************************************
// CPriorManager* CPriorManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CPriorManager* CPriorManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CPriorManager());
  return clInstance.get();
}

//**********************************************************************
// void CPriorManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CPriorManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CPriorManager::addPrior(CPrior *Prior)
// add Prior to List
//**********************************************************************
void CPriorManager::addPrior(CPrior *Prior) {
  vPriorList.push_back(Prior);
}

//**********************************************************************
// CPrior* CPriorManager::getPrior(string Label)
// Get Prior Pointer
//**********************************************************************
CPrior* CPriorManager::getPrior(string Label) {
  try {
    foreach(CPrior *Prior, vPriorList) {
      if (Prior->getLabel() == Label)
        return Prior;
    }

    throw string(ERROR_UNKNOWN_PRIOR + Label);

  } catch (string Ex) {
    Ex = "CPriorManager.getPrior()->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// CPrior* CPriorManager::getPrior(int index)
// Return prior from our vector @ index
//**********************************************************************
CPrior* CPriorManager::getPrior(int index) {
  try {
    if (index >= (int)vPriorList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_PRIOR);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vPriorList[index];

  } catch (string Ex) {
    Ex = "CPriorManager.getPrior()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPriorManager::clone(CPriorManager *Manager)
// Clone the prior manager passed in as param
//**********************************************************************
void CPriorManager::clone(CPriorManager *Manager) {
  try {

//    for (int i = 0; i < Manager->getPriorCount(); ++i) {
//      CPrior *pPrior = Manager->getPrior(i);
//      vPriorList.push_back(pPrior->clone());
//    }
    // TODO: Fix Clones
  } catch (string Ex) {
    Ex = "CPriorManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPriorManager::validate()
// validate
//**********************************************************************
void CPriorManager::validate() {
  try {

  } catch (string Ex) {
    Ex = "CPriorManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPriorManager::~CPriorManager()
// Default De-Constructor
//**********************************************************************
CPriorManager::~CPriorManager() {

  // Clear Prior Memory
  foreach(CPrior *Prior, vPriorList) {
    delete Prior;
  }
  vPriorList.clear();
}
