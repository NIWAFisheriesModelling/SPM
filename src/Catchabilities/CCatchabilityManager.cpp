//============================================================================
// Name        : CCatchabilityManager.cpp
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CCatchabilityManager.h"
#include "CCatchability.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Singleton Variable
boost::thread_specific_ptr<CCatchabilityManager> CCatchabilityManager::clInstance;

//**********************************************************************
// CCatchabilityManager::CCatchabilityManager()
// Default Constructor
//**********************************************************************
CCatchabilityManager::CCatchabilityManager() {
}

//**********************************************************************
// CCatchabilityManager* CCatchabilityManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CCatchabilityManager* CCatchabilityManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CCatchabilityManager());
  return clInstance.get();
}

//**********************************************************************
// void CCatchabilityManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CCatchabilityManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CCatchabilityManager::addQ(CCatchability *Q)
// Add a Q (I hate this short name) to our List
//**********************************************************************
void CCatchabilityManager::addCatchability(CCatchability *Q) {
  vCatchabilityList.push_back(Q);
}

//**********************************************************************
// CCatchability* CCatchabilityManager::getQ(string label)
// Get a pointer to our Q from the vector
//**********************************************************************
CCatchability* CCatchabilityManager::getCatchability(string label) {
  try {
    // Loop through and find our Q
    foreach(CCatchability *Q, vCatchabilityList) {
      if (Q->getLabel() == label)
        return Q;
    }
    // Couldn't find it.
    throw string(ERROR_UNKNOWN_Q + label);

  } catch (string Ex) {
    Ex = "CCatchabilityManager.getQ()->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// CCatchability* CCatchabilityManager::getQ(int index)
// Get the Q from vector @ index
//**********************************************************************
CCatchability* CCatchabilityManager::getCatchability(int index) {
  try {
    if (index >= (int)vCatchabilityList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_Q);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vCatchabilityList[index];

  } catch (string Ex) {
    Ex = "CCatchabilityManager.getQ()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CCatchabilityManager::clone(CCatchabilityManager *Manager)
// Clone the manager with param
//**********************************************************************
void CCatchabilityManager::clone(CCatchabilityManager *Manager) {
  try {

    for (int i = 0; i < Manager->getCatchabilityCount(); ++i) {
      CCatchability *pQ = Manager->getCatchability(i);
      vCatchabilityList.push_back(pQ->clone());
    }
    // TODO: Fix Clone

  } catch (string Ex) {
    Ex = "CCatchabilityManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCatchabilityManager::validate()
// Validate our catchabilities
//**********************************************************************
void CCatchabilityManager::validate() {
  try {
    foreach(CCatchability *Catchability, vCatchabilityList) {
      Catchability->validate();
    }
  } catch (string Ex) {
    Ex = "CCatchabilityManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CCatchabilityManager::~CCatchabilityManager()
// Default De-Constructor
//**********************************************************************
CCatchabilityManager::~CCatchabilityManager() {
}
