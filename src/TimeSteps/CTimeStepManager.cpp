//============================================================================
// Name        : CTimeStepManager.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : << See CTimeStepManager.h >>
// $Date$
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "CTimeStepManager.h"
#include "CTimeStep.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CConvertor.h"
#include "../World/CWorld.h"
#include "../Observations/CObservationManager.h"
#include "../Reporters/CReporterManager.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CTimeStepManager> CTimeStepManager::clInstance;

//**********************************************************************
// CTimeStepManager::CTimeStepManager()
// Default Constructor
//**********************************************************************
CTimeStepManager::CTimeStepManager() {
  pObservationManager = 0;
  pReporterManager    = 0;
}

//**********************************************************************
// CTimeStepManager* CTimeStepManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CTimeStepManager* CTimeStepManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CTimeStepManager());
  return clInstance.get();
}

//**********************************************************************
// void CTimeStepManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CTimeStepManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CTimeStepManager::addTimeStep(CTimeStep *value)
// Add New Time Step To The List
//**********************************************************************
void CTimeStepManager::addTimeStep(CTimeStep *value) {
  vTimeSteps.push_back(value);
}

//**********************************************************************
// CTimeStep* CTimeStepManager::getTimeStep(int index)
// Get the timestep from our vector @ index
//**********************************************************************
//CTimeStep* CTimeStepManager::getTimeStep(int index) {
//  try {
//    if (index >= (int)vTimeSteps.size())
//      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_TIME_STEPS);
//    if (index < 0)
//      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
//
//    return vTimeSteps[index];
//
//  } catch (string Ex) {
//    Ex = "CTimeStepManager.getTimeStep()->" + Ex;
//    throw Ex;
//  }
//
//  return 0;
//}

//**********************************************************************
// void CTimeStepManager::loadTimeStepOrder(vector<string> &order)
// Load the TimeStep Order for Execution
//**********************************************************************
void CTimeStepManager::loadTimeStepOrder(vector<string> &order) {
  vTimeStepsOrder.clear();

  foreach(string Label, order) {
    foreach(CTimeStep *TimeStep, vTimeSteps) {
      if (TimeStep->getLabel() == Label) {
        vTimeStepsOrder.push_back(TimeStep);
        break;
      }
    }
  }
}

//**********************************************************************
// int CTimeStepManager::getTimeStepOrderIndex(string label)
// Get the Index of a TimeStep in our Order
//**********************************************************************
int CTimeStepManager::getTimeStepOrderIndex(string label) {
  try {
    for (int i = 0; i < (int)vTimeStepsOrder.size(); ++i)
      if (vTimeStepsOrder[i]->getLabel() == label)
        return i;

    throw string("Unknown timestep: " + label); // TODO: Add Error

  } catch (string Ex) {
    Ex = "CTimeStepManager.getTimeStepOrderIndex()->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CTimeStepManager::clone(CTimeStepManager *Manager)
// Clone the TimeStepManager with the parameter
//**********************************************************************
void CTimeStepManager::clone(CTimeStepManager *Manager) {
  try {
    for (int i = 0; i < (int)Manager->vTimeSteps.size(); ++i) {
      CTimeStep *pTimeStep = Manager->vTimeSteps[i];
      vTimeSteps.push_back(pTimeStep->clone());
    }

  } catch (string Ex) {
    Ex = "CTimeStepManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStepManager::validate()
// Validate The Time Steps
//**********************************************************************
void CTimeStepManager::validate() {
  try {
    if ((int)vTimeSteps.size() == 0)
      throw string("No time steps loaded"); // TODO: Add Translation

    // Call TimeStep Validations
    foreach( CTimeStep *TimeStep, vTimeSteps) {
      TimeStep->validate();
    }

  } catch(string Ex) {
    Ex = "CTimeStepManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStepManager::build()
// Build out TimeSteps
//**********************************************************************
void CTimeStepManager::build() {
#ifndef OPTIMISE
  try {
#endif

    foreach(CTimeStep *TimeStep, vTimeSteps) {
      TimeStep->build();
    }

    CWorld *pWorld = CWorld::Instance();
    iFirstHumanYear   = pWorld->getInitialYear();
    iNumberOfYears    = pWorld->getCurrentYear() - iFirstHumanYear;

    pObservationManager = CObservationManager::Instance();
    pReporterManager    = CReporterManager::Instance();

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CTimeStepManager.build()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CTimeStepManager::executeTimeSteps(int Step)
// Execute Our TimeSteps
//**********************************************************************
void CTimeStepManager::execute() {
#ifdef VERBOSE
  cout << "TimeStep Manager Execution" << endl;
  cout << ">> TimeSteps Size: " << vTimeSteps.size() << endl;
  cout << ">> Order Size: " << vTimeStepsOrder.size() << endl;
  cout << ">> NumberOfYears: " << iNumberOfYears << endl;
#endif

  for (int i = 0; i <= iNumberOfYears; ++i) {
    iCurrentYear = i + iFirstHumanYear;

    for (int j = 0; j < (int)vTimeStepsOrder.size(); ++j) {
      iCurrentTimeStep = j;

      // Execute Time Step
      vTimeStepsOrder[j]->execute();

      // Execute Other Tasks
      pObservationManager->execute(iCurrentYear, j);
      pReporterManager->execute();
    }
  }
}

//**********************************************************************
// CTimeStepManager::~CTimeStepManager()
// Default De-constructor
//**********************************************************************
CTimeStepManager::~CTimeStepManager() {
  // Delete Our Layers
  foreach( CTimeStep *TimeStep, vTimeSteps) {
    delete TimeStep;
  }
}
