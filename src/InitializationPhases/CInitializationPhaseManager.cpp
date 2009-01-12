//============================================================================
// Name        : CInitializationPhaseManager.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CInitializationPhaseManager.h"
#include "CInitializationPhase.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Singleton Variable
boost::thread_specific_ptr<CInitializationPhaseManager> CInitializationPhaseManager::clInstance;

//**********************************************************************
// CInitializationPhaseManager::CInitializationPhaseManager()
// Default Constructor
//**********************************************************************
CInitializationPhaseManager::CInitializationPhaseManager() {
}

//**********************************************************************
// CInitializationPhaseManager* CInitializationPhaseManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CInitializationPhaseManager* CInitializationPhaseManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CInitializationPhaseManager());
  return clInstance.get();
}

//**********************************************************************
// void CInitializationPhaseManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CInitializationPhaseManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CInitializationPhaseManager::addInitializationPhase(CInitializationPhase *value)
// Add our Timestep To The List
//**********************************************************************
void CInitializationPhaseManager::addInitializationPhase(CInitializationPhase *value) {
  vInitializationPhases.push_back(value);
}

//**********************************************************************
// CInitializationPhase* CInitializationPhaseManager::getInitializationPhase(string label)
// Get a Pointer to our InitializationPhase
//**********************************************************************
CInitializationPhase* CInitializationPhaseManager::getInitializationPhase(string label) {
  try {
    // Loop through looking for match.
    foreach(CInitializationPhase *InitializationPhase, vInitializationPhases) {
      if (InitializationPhase->getLabel() == label)
        return InitializationPhase;
    }
    // Match not found
    throw string(ERROR_UNKNOWN_TIME_STEP + label); // TODO: Add CError and Translation

  } catch (string Ex) {
    Ex = "CInitialisationManager.getInitializationPhase()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// CInitializationPhase* CInitializationPhaseManager::getInitializationPhase(int index)
// Get InitializationPhase from our vector @ index
//**********************************************************************
CInitializationPhase* CInitializationPhaseManager::getInitializationPhase(int index) {
  try {
    if (index >= (int)vInitializationPhases.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_TIME_STEPS);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vInitializationPhases[index];

  } catch (string Ex) {
    Ex = "CInitialisationManager.getInitializationPhase()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CInitializationPhaseManager::clone(CInitializationPhaseManager *Manager)
// Clone the manager passed in as a parameter
//**********************************************************************
void CInitializationPhaseManager::clone(CInitializationPhaseManager *Manager) {
  try {
    for (int i = 0; i < Manager->getInitializationPhaseCount(); ++i) {
      CInitializationPhase *pInitializationPhase = Manager->getInitializationPhase(i);
      vInitializationPhases.push_back(pInitializationPhase->clone());
    }

  } catch (string Ex) {
    Ex = "CInitialisationManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhaseManager::validate()
// Validate our TimeSteps
//**********************************************************************
void CInitializationPhaseManager::validate() {
  try {
    foreach( CInitializationPhase *InitializationPhase, vInitializationPhases) {
      InitializationPhase->validate();
    }

  } catch(string Ex) {
    Ex = "CInitialisationManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhaseManager::build()
// Build our Time Steps
//**********************************************************************
void CInitializationPhaseManager::build() {
  try {
    // Now, Call TimeStep Validations
    foreach( CInitializationPhase *InitializationPhase, vInitializationPhases) {
      InitializationPhase->build();
    }

  } catch(string Ex) {
    Ex = "CInitialisationManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CInitializationPhaseManager::~CInitializationPhaseManager()
// Default De-Constructor
//**********************************************************************
CInitializationPhaseManager::~CInitializationPhaseManager() {
  // Delete Our Layers
  foreach( CInitializationPhase *InitializationPhase, vInitializationPhases) {
    delete InitializationPhase;
  }

  // Clear Vector
  vInitializationPhases.clear();
}
