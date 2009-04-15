//============================================================================
// Name        : CDerivedQuantityManager.cpp
// Author      : S.Rasmussen
// Date        : 30/03/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CDerivedQuantityManager.h"
#include "CDerivedQuantity.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Singleton Variable
boost::thread_specific_ptr<CDerivedQuantityManager> CDerivedQuantityManager::clInstance;

//**********************************************************************
// CDerivedQuantityManager::CDerivedQuantityManager()
// Default Constructor
//**********************************************************************
CDerivedQuantityManager::CDerivedQuantityManager() {
}

//**********************************************************************
// CDerivedQuantityManager* CDerivedQuantityManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CDerivedQuantityManager* CDerivedQuantityManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CDerivedQuantityManager());
  return clInstance.get();
}

//**********************************************************************
// void CDerivedQuantityManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CDerivedQuantityManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CDerivedQuantityManager::clone(CDerivedQuantityManager *Manager)
// Clone our Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::clone(CDerivedQuantityManager *Manager) {
  // TODO: Implement this clone function
}

//**********************************************************************
// void CDerivedQuantityManager::addDerivedQuantity(CDerivedQuantity *DerivedQuantity)
// Add Derived Quantity to our list
//**********************************************************************
void CDerivedQuantityManager::addDerivedQuantity(CDerivedQuantity *DerivedQuantity) {
  vDerivedQuantities.push_back(DerivedQuantity);
}

//**********************************************************************
// void CDerivedQuantityManager::validate()
// Validate our Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::validate() {
  try {

    foreach(CDerivedQuantity *DerivedQuantity, vDerivedQuantities) {
      DerivedQuantity->validate();
    }

  } catch (string Ex) {
    Ex = "CDerivedQuantityManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityManager::build()
// Build our Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::build() {
  try {

    foreach(CDerivedQuantity *DerivedQuantity, vDerivedQuantities) {
      DerivedQuantity->build();
    }

  } catch (string Ex) {
    Ex = "CDerivedQuantityManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityManager::execute()
// Execute Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::execute() {

  foreach(CDerivedQuantity *DerivedQuantity, vDerivedQuantities) {
    DerivedQuantity->execute();
  }
}

//**********************************************************************
// CDerivedQuantityManager::~CDerivedQuantityManager()
// Destructor
//**********************************************************************
CDerivedQuantityManager::~CDerivedQuantityManager() {
}
