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

    CError::errorUnknown(PARAM_PRIOR, Label);

  } catch (string &Ex) {
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
  } catch (string &Ex) {
    Ex = "CPriorManager.getPrior()->" + Ex;
    throw Ex;
  }

  return vPriorList[index];
}

//**********************************************************************
// void CPriorManager::clone(CPriorManager *Manager)
// Clone the prior manager passed in as param
//**********************************************************************
void CPriorManager::clone(CPriorManager *Manager) {

  foreach(CPrior *prior, Manager->vPriorList) {
    vPriorList.push_back(prior->clone());
  }
}

//**********************************************************************
// void CPriorManager::validate()
// validate
//**********************************************************************
void CPriorManager::validate() {
  try {
    foreach(CPrior *Prior, vPriorList) {
      Prior->validate();
    }


  } catch (string &Ex) {
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
