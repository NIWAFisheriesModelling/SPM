//============================================================================
// Name        : CAgeingErrorManager.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAgeingErrorManager.h"
#include "CAgeingError.h"

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
// void CAgeingErrorManager::validate()
// Validate our Ageing Errors
//**********************************************************************
void CAgeingErrorManager::validate() {

}

//**********************************************************************
// CAgeingErrorManager::~CAgeingErrorManager()
// Destructor
//**********************************************************************
CAgeingErrorManager::~CAgeingErrorManager() {
}
