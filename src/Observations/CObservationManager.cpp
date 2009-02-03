//============================================================================
// Name        : CObservationManager.cpp
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : << See CObservationManager.h >>
// $Date$
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "CObservationManager.h"
#include "CObservation.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CObservationManager> CObservationManager::clInstance;

//**********************************************************************
// CObservationManager::CObservationManager()
// Default Constructor
//**********************************************************************
CObservationManager::CObservationManager() {
}

//**********************************************************************
// CObservationManager* CObservationManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CObservationManager* CObservationManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CObservationManager());
  return clInstance.get();
}

//**********************************************************************
// void CObservationManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CObservationManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CObservationManager::addObservation(CObservation *pObservation)
// Add Proportion To Our List
//**********************************************************************
void CObservationManager::addObservation(CObservation *pObservation) {
  vObservationList.push_back(pObservation);
}

//**********************************************************************
// CObservation* CObservationManager::getObservation(int index)
// Get Observation by Index
//**********************************************************************
CObservation* CObservationManager::getObservation(int index) {
  try {
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (index >= (int)vObservationList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_OBSERVATIONS);

    return vObservationList[index];

  } catch (string Ex) {
    Ex = "CObservationManager.getObservation()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CObservationManager::clone(CObservationManager *Manager)
// Clone the Observation Manager
//**********************************************************************
void CObservationManager::clone(CObservationManager *Manager) {
  try {

//    for (int i = 0; i < Manager->getObservationCount(); ++i) {
//      CObservation *pObservation = Manager->getObservation(i);
//      vObservationList.push_back(pObservation->clone());
//    }
    // TODO: Fix Clones

  } catch (string Ex) {
    Ex = "CObservationManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationManager::validate()
// Loop Through and Validate our Proportions
//**********************************************************************
void CObservationManager::validate() {
  try {
    foreach(CObservation *Observation, vObservationList) {
      Observation->validate();
    }

    // Variables
    vector<CObservation*>::iterator vPtr;
    map<string, int>                     mObservationList;

    // Check For Duplicates
    vPtr = vObservationList.begin();
    while (vPtr != vObservationList.end()) {
      // Inc
      mObservationList[(*vPtr)->getLabel()] += 1;

      // Check
      if (mObservationList[(*vPtr)->getLabel()] > 1)
        throw string(ERROR_DUPLICATE_LABEL + (*vPtr)->getLabel());

      vPtr++;
    }


  } catch (string Ex) {
    Ex = "CObservationManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationManager::build()
// Build
//**********************************************************************
void CObservationManager::build() {
  try {

    // Loop and build
    foreach(CObservation *Observation, vObservationList) {
      Observation->build();
    }

  } catch (string Ex) {
    Ex = "CObservationManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationManager::execute(int year, int step)
// Execute
//**********************************************************************
void CObservationManager::execute(int year, int step) {
  try {
    // Loop and Test
    foreach(CObservation *Observation, vObservationList) {
      if ( (Observation->getYear() == year) && (Observation->getTimeStep() == step) ) {
        Observation->execute();
      }
    }
  } catch (string Ex) {
    Ex = "CObservationManager.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CObservationManager::~CObservationManager()
// Default De-Constructor
//**********************************************************************
CObservationManager::~CObservationManager() {
  vector<CObservation*>::iterator vPtr;
  vPtr = vObservationList.begin();
  while (vPtr != vObservationList.end()) {
    delete (*vPtr);
    vPtr++;
  }
  vObservationList.clear();
}
