/*
 * CMCMCManager.cpp
 *
 *  Created on: 10/11/2014
 *      Author: Admin
 */

// Global headers
#include <iostream>

// Local Headers
#include "CMCMCManager.h"
#include "CMCMC.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CMCMCManager> CMCMCManager::clInstance;

//**********************************************************************
// CMCMCManager::CMCMCManager()
// Default constructor
//**********************************************************************
CMCMCManager::CMCMCManager() {


}

//**********************************************************************
// CProcessManager* CProcessManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CMCMCManager::~CMCMCManager() {
  // Loop n Delete
  foreach(CMCMC *MCMC, vMCMCList) {
    delete MCMC;
  }

  vMCMCList.clear();
}

//**********************************************************************
// CMCMCManager* CProcessManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CMCMCManager* CMCMCManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CMCMCManager());
  return clInstance.get();
}

//**********************************************************************
// void CProcessManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CMCMCManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CMCMCManager::addMCMC(CMCMC *MCMC)
// Add A MCMC To Our List
//**********************************************************************
void CMCMCManager::addMCMC(CMCMC *MCMC) {
  vMCMCList.push_back(MCMC);
}

//**********************************************************************
// CMCMC* CMCMCManager::getMCMC(string Label)
// Return Link To Our MCMC
//**********************************************************************
CMCMC* CMCMCManager::getMCMC(string Label) {
  // Loop for Match
  foreach(CMCMC *MCMC, vMCMCList) {
    if (MCMC->getLabel() == Label)
      return MCMC;
  }

  CError::errorUnknown(PARAM_MCMC, Label);
  return 0;
}

//**********************************************************************
// void CMCMCManager::clone(CMCMCManager *Manager)
// Clone the manager passed in as a parameter
//**********************************************************************
void CMCMCManager::clone(CMCMCManager *Manager) {

  foreach(CMCMC *mcmc, Manager->vMCMCList) {
    vMCMCList.push_back(mcmc->clone());
  }
}

//**********************************************************************
// void CMCMCManager::validate()
// Validate Our MCMC Against Bad Input Data
//**********************************************************************
void CMCMCManager::validate() {
  try {
    // Validate Processes
    foreach(CMCMC* MCMC, vMCMCList) {
      MCMC->validate();
    }

    // Check For Duplicate Labels
    map<string, int>              mLabelList;
    foreach(CMCMC* MCMC, vMCMCList) {
      mLabelList[MCMC->getLabel()] += 1;
      if (mLabelList[MCMC->getLabel()] > 1)
        CError::errorDuplicate(PARAM_LABEL, MCMC->getLabel());
    }

  } catch(string &Ex) {
    Ex = "CMCMCManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCManager::build()
// Build Our MCMC, And Relationships.
//**********************************************************************
void CMCMCManager::build() {
#ifndef OPTIMIZE
  try {
#endif

    // Loop n Build
    foreach(CMCMC *MCMC, vMCMCList) {
      MCMC->build();
    }

#ifndef OPTIMIZE
  } catch(string &Ex) {
    Ex = "CMCMCManager.build()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMCMCManager::rebuild()
// Rebuild our MCMC
//**********************************************************************
void CMCMCManager::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    // Loop n Build
    foreach(CMCMC *MCMC, vMCMCList) {
      MCMC->rebuild();
    }

#ifndef OPTIMIZE
  } catch(string &Ex) {
    Ex = "CMCMCManager.rebuild()->" + Ex;
    throw Ex;
  }
#endif
}











































