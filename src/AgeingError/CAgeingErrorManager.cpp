//============================================================================
// Name        : CAgeingErrorManager.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "CAgeingErrorManager.h"
#include "CAgeingError.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Using
using std::cout;
using std::endl;

// Singleton Variable
boost::thread_specific_ptr<CAgeingErrorManager> CAgeingErrorManager::clInstance;

//**********************************************************************
// CAgeingErrorManager::CAgeingErrorManager()
// Default Constructor
//**********************************************************************
CAgeingErrorManager::CAgeingErrorManager() {
}

//**********************************************************************
// CAgeingErrorManager* CAgeingErrorManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CAgeingErrorManager* CAgeingErrorManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CAgeingErrorManager());
  return clInstance.get();
}

//**********************************************************************
// void CAgeingErrorManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CAgeingErrorManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CAgeingErrorManager::clone(CAgeingErrorManager *Manager)
// Clone our Ageing Errors
//**********************************************************************
void CAgeingErrorManager::clone(CAgeingErrorManager *Manager) {
  // TODO: Implement Ageing Error Manager Clone
}

//**********************************************************************
// void CAgeingErrorManager::addAgeingError(CAgeingError *ageingError)
// Add Ageing Error to the List
//**********************************************************************
void CAgeingErrorManager::addAgeingError(CAgeingError *ageingError) {
  vAgeingErrors.push_back(ageingError);
}

//**********************************************************************
// CAgeingError* CAgeingErrorManager::getAgeingError(string label)
// Get our Ageing Error
//**********************************************************************
CAgeingError* CAgeingErrorManager::getAgeingError(string label) {
  try {
    foreach(CAgeingError *ageingError, vAgeingErrors) {
      if (ageingError->getLabel() == label)
        return ageingError;
    }

    CError::errorUnknown(PARAM_AGEING_ERROR, label);

  } catch (string Ex) {
    Ex = "CAgeingErrorManager.getAgeingError(" + label + ")->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CAgeingErrorManager::validate()
// Validate our Ageing Errors
//**********************************************************************
void CAgeingErrorManager::validate() {
  try {
    foreach(CAgeingError *ageingError, vAgeingErrors) {
      ageingError->validate();
    }
  } catch (string Ex) {
    Ex = "CAgeingErrorManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeingErrorManager::build()
// Build our AgeingErrors
//**********************************************************************
void CAgeingErrorManager::build() {
  try {
    foreach(CAgeingError *ageingError, vAgeingErrors) {
      ageingError->build();
    }
  } catch (string Ex) {
    Ex = "CAgeingErrorManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeingErrorManager::rebuild()
// Rebuild our ageing errors
//**********************************************************************
void CAgeingErrorManager::rebuild() {
  try {
    foreach(CAgeingError *ageingError, vAgeingErrors) {
      ageingError->rebuild();
    }

  } catch (string Ex) {
    Ex = "CAgeingErrorManager.rebuild()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CAgeingErrorManager::~CAgeingErrorManager()
// Destructor
//**********************************************************************
CAgeingErrorManager::~CAgeingErrorManager() {
  foreach(CAgeingError *ageingError, vAgeingErrors) {
    delete ageingError;
  }
}
