//============================================================================
// Name        : CPenaltyManager.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CPenaltyManager.h"
#include "Penalties/CPenalty.h"

// Single Static variable
boost::thread_specific_ptr<CPenaltyManager> CPenaltyManager::clInstance;

//**********************************************************************
// CPenaltyManager::CPenaltyManager()
// Default Constructor
//**********************************************************************
CPenaltyManager::CPenaltyManager() {
}

//**********************************************************************
// CPenaltyManager* CPenaltyManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CPenaltyManager* CPenaltyManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CPenaltyManager());
  return clInstance.get();
}

//**********************************************************************
// void CPenaltyManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CPenaltyManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CPenaltyManager::addPenalty(CPenalty *Penalty)
// add Penalty to our list
//**********************************************************************
void CPenaltyManager::addPenalty(CPenalty *Penalty) {
 vPenaltyList.push_back(Penalty);
}

//**********************************************************************
// CPenalty* CPenaltyManager::getPenalty(string Label)
// Get Penalty Pointer
//**********************************************************************
CPenalty* CPenaltyManager::getPenalty(string Label) {
  try {
    foreach(CPenalty *Penalty, vPenaltyList) {
      if (Penalty->getLabel() == Label)
        return Penalty;
    }

    throw string(ERROR_UNKNOWN_PENALTY + Label);

  } catch (string Ex) {
    Ex = "CPenaltyManager.getPenalty()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPenalty* CPenaltyManager::getPenalty(int index)
// Get the penalty from our vector @ index
//**********************************************************************
CPenalty* CPenaltyManager::getPenalty(int index) {
  try {
    if (index >= (int)vPenaltyList.size())
      errorGreaterThanEqualTo(PARAM_INDEX, PARAM_PENALTY);
    if (index < 0)
      errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vPenaltyList[index];

  } catch (string Ex) {
    Ex = "CPenaltyManager.getPenalty()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPenaltyManager::addPenalty(string Label, double Value)
// Add A Penalty to our list of Executed ones.
//**********************************************************************
void CPenaltyManager::flagPenalty(string Label, double Value) {
  SFlaggedPenalty stPenalty;
  stPenalty.Label = Label;
  stPenalty.Score = Value;

  vFlaggedPenaltyList.push_back(stPenalty);
}

//**********************************************************************
// void CPenaltyManager::clearFlaggedPenaltyList()
// Clear Our Penalty List
//**********************************************************************
void CPenaltyManager::clearFlaggedPenaltyList() {
  vFlaggedPenaltyList.clear();
}

//**********************************************************************
// SFlaggedPenalty* CPenaltyManager::getFlaggedPenalty(int Index)
//
//**********************************************************************
SFlaggedPenalty* CPenaltyManager::getFlaggedPenalty(int Index) {
#ifndef OPTIMISE
  try {
    if (Index < 0)
      errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (Index >= (int)vFlaggedPenaltyList.size())
      errorGreaterThanEqualTo(PARAM_INDEX, PARAM_FLAGGED_PENALTIES);
#endif

    return &vFlaggedPenaltyList[Index];

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CPenaltyManager.getFlaggedPenalty()->" + Ex;
    throw Ex;
  }

  return 0;
#endif
}

//**********************************************************************
// void CPenaltyManager::clone(CPenaltyManager *Manager)
// Clone the Manager to match the one passed in
//**********************************************************************
void CPenaltyManager::clone(CPenaltyManager *Manager) {
  try {

    for (int i = 0; i < Manager->getPenaltyCount(); ++i) {
      CPenalty *pPenalty = Manager->getPenalty(i);
      vPenaltyList.push_back(pPenalty->clone());
    }

  } catch (string Ex) {
    Ex = "CPenaltyManager.clone()->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CPenaltyManager::validate()
// validate
//**********************************************************************
void CPenaltyManager::validate() {
  try {
    // Loop and Validate
    foreach(CPenalty *Penalty, vPenaltyList) {
      Penalty->validate();
    }

  } catch (string Ex) {
    Ex = "CPenaltyManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPenaltyManager::build()
// build
//**********************************************************************
void CPenaltyManager::build() {
  try {
    // Loop and build
    foreach(CPenalty *Penalty, vPenaltyList) {
      Penalty->build();
    }

  } catch (string Ex) {
    Ex = "CPenaltyManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPenaltyManager::~CPenaltyManager()
// Default De-Constructor
//**********************************************************************
CPenaltyManager::~CPenaltyManager() {
  // De-Allocate our Memory
  vector<CPenalty*>::iterator vPtr;
  vPtr = vPenaltyList.begin();
  while (vPtr != vPenaltyList.end()) {
    delete (*vPtr);
    vPtr++;
  }
  vPenaltyList.clear();
  vFlaggedPenaltyList.clear();
}
