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
#include "../TimeSteps/CTimeStep.h"
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
// void CInitializationPhaseManager::addTimeStep(CTimeStep *value)
// Add our Timestep To The List
//**********************************************************************
void CInitializationPhaseManager::addTimeStep(CTimeStep *value) {
  // Set The Step Number and Push.
  value->setStep(1);
  vTimeStepList.push_back(value);
}

//**********************************************************************
// CTimeStep* CInitializationPhaseManager::getTimeStep(string label)
// Get a Pointer to our TimeStep
//**********************************************************************
CTimeStep* CInitializationPhaseManager::getTimeStep(string label) {
  try {
    // Loop through looking for match.
    foreach(CTimeStep *TimeStep, vTimeStepList) {
      if (TimeStep->getLabel() == label)
        return TimeStep;
    }
    // Match not found
    throw string(ERROR_UNKNOWN_TIME_STEP + label);

  } catch (string Ex) {
    Ex = "CInitialisationManager.getTimeStep()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// CTimeStep* CInitializationPhaseManager::getTimeStep(int index)
// Get timestep from our vector @ index
//**********************************************************************
CTimeStep* CInitializationPhaseManager::getTimeStep(int index) {
  try {
    if (index >= (int)vTimeStepList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_TIME_STEPS);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vTimeStepList[index];

  } catch (string Ex) {
    Ex = "CInitialisationManager.getTimeStep()->" + Ex;
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
    for (int i = 0; i < Manager->getTimeStepCount(); ++i) {
      CTimeStep *pTimeStep = Manager->getTimeStep(i);
      vTimeStepList.push_back(pTimeStep->clone());
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
    foreach( CTimeStep *TimeStep, vTimeStepList) {
      TimeStep->validate();
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
    foreach( CTimeStep *TimeStep, vTimeStepList) {
      TimeStep->build();
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
  foreach( CTimeStep *TimeStep, vTimeStepList) {
    delete TimeStep;
  }

  // Clear Vector
  vTimeStepList.clear();
}
