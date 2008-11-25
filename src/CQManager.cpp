//============================================================================
// Name        : CQManager.cpp
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CQManager.h"
#include "Qs/CQ.h"

// Singleton Variable
boost::thread_specific_ptr<CQManager> CQManager::clInstance;

//**********************************************************************
// CQManager::CQManager()
// Default Constructor
//**********************************************************************
CQManager::CQManager() {
}

//**********************************************************************
// CQManager* CQManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CQManager* CQManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CQManager());
  return clInstance.get();
}

//**********************************************************************
// void CQManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CQManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CQManager::addQ(CQ *Q)
// Add a Q (I hate this short name) to our List
//**********************************************************************
void CQManager::addQ(CQ *Q) {
  vQList.push_back(Q);
}

//**********************************************************************
// CQ* CQManager::getQ(string label)
// Get a pointer to our Q from the vector
//**********************************************************************
CQ* CQManager::getQ(string label) {
  try {
    // Loop through and find our Q
    foreach(CQ *Q, vQList) {
      if (Q->getLabel() == label)
        return Q;
    }
    // Couldn't find it.
    throw string(ERROR_UNKNOWN_Q + label);

  } catch (string Ex) {
    Ex = "CQManager.getQ()->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// CQ* CQManager::getQ(int index)
// Get the Q from vector @ index
//**********************************************************************
CQ* CQManager::getQ(int index) {
  try {
    if (index >= (int)vQList.size())
      errorGreaterThanEqualTo(PARAM_INDEX, PARAM_Q);
    if (index < 0)
      errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vQList[index];

  } catch (string Ex) {
    Ex = "CQManager.getQ()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CQManager::clone(CQManager *Manager)
// Clone the manager with param
//**********************************************************************
void CQManager::clone(CQManager *Manager) {
  try {

    for (int i = 0; i < Manager->getQCount(); ++i) {
      CQ *pQ = Manager->getQ(i);
      vQList.push_back(pQ->clone());
    }

  } catch (string Ex) {
    Ex = "CQManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CQManager::~CQManager()
// Default De-Constructor
//**********************************************************************
CQManager::~CQManager() {
}
