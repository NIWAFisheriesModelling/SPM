//============================================================================
// Name        : CInitializationManager.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CInitializationManager.h"
#include "TimeSteps/CTimeStep.h"

// Singleton Variable
boost::thread_specific_ptr<CInitializationManager> CInitializationManager::clInstance;

//**********************************************************************
// CInitializationManager::CInitializationManager()
// Default Constructor
//**********************************************************************
CInitializationManager::CInitializationManager() {
}

//**********************************************************************
// CInitializationManager* CInitializationManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CInitializationManager* CInitializationManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CInitializationManager());
  return clInstance.get();
}

//**********************************************************************
// void CInitializationManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CInitializationManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CInitializationManager::addTimeStep(CTimeStep *value)
// Add our Timestep To The List
//**********************************************************************
void CInitializationManager::addTimeStep(CTimeStep *value) {
  // Set The Step Number and Push.
  value->setStep(1);
  vTimeStepList.push_back(value);
}

//**********************************************************************
// CTimeStep* CInitializationManager::getTimeStep(string label)
// Get a Pointer to our TimeStep
//**********************************************************************
CTimeStep* CInitializationManager::getTimeStep(string label) {
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
// CTimeStep* CInitializationManager::getTimeStep(int index)
// Get timestep from our vector @ index
//**********************************************************************
CTimeStep* CInitializationManager::getTimeStep(int index) {
  try {
    if (index >= (int)vTimeStepList.size())
      errorGreaterThanEqualTo(PARAM_INDEX, PARAM_TIME_STEPS);
    if (index < 0)
      errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vTimeStepList[index];

  } catch (string Ex) {
    Ex = "CInitialisationManager.getTimeStep()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CInitializationManager::clone(CInitializationManager *Manager)
// Clone the manager passed in as a parameter
//**********************************************************************
void CInitializationManager::clone(CInitializationManager *Manager) {
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
// void CInitializationManager::validate()
// Validate our TimeSteps
//**********************************************************************
void CInitializationManager::validate() {
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
// void CInitializationManager::build()
// Build our Time Steps
//**********************************************************************
void CInitializationManager::build() {
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
// CInitializationManager::~CInitializationManager()
// Default De-Constructor
//**********************************************************************
CInitializationManager::~CInitializationManager() {
  // Delete Our Layers
  foreach( CTimeStep *TimeStep, vTimeStepList) {
    delete TimeStep;
  }

  // Clear Vector
  vTimeStepList.clear();
}
