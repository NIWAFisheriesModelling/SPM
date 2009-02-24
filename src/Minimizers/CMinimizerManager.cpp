//============================================================================
// Name        : CMinimizerManager.cpp
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CMinimizerManager.h"
#include "CMinimizer.h"
#include "../RuntimeThread/CRuntimeThread.h"
#include "../CRuntimeController.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Singleton Variable
CMinimizerManager* CMinimizerManager::clInstance = 0;

//**********************************************************************
// CMinimizerManager::CMinimizerManager()
// Default Constructor
//**********************************************************************
CMinimizerManager::CMinimizerManager() {

  // Set Vars
  pMinimizer = 0;
  sMinimizer = "";

  // Register
  pParameterList->registerAllowed(PARAM_MINIMIZER);
}

//**********************************************************************
// CMinimizerManager* CMinimizerManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CMinimizerManager* CMinimizerManager::Instance() {
  if (clInstance == 0)
    clInstance = new CMinimizerManager();
  return clInstance;
}

//**********************************************************************
// void CMinimizerManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CMinimizerManager::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CMinimizerManager::addMinimizer(CMinimizer *value)
// Add A Minimizer to our List
//**********************************************************************
void CMinimizerManager::addMinimizer(CMinimizer *value) {
  vMinimizerList.push_back(value);
}

//**********************************************************************
// void CMinimizerManager::addThread(CRuntimeThread *Thread)
// Add Thread to our Pool
//**********************************************************************
void CMinimizerManager::addThread(CRuntimeThread *Thread) {
  lock lk(mutThread);
  vThreadList.push_back(Thread);
}

//**********************************************************************
// void CMinimizer::validate()
// Validate our MinizerManager
//**********************************************************************
void CMinimizerManager::validate() {
  try {
    if (CRuntimeController::Instance()->getRunMode() == RUN_MODE_BASIC)
      return;

    pParameterList->checkInvalidParameters();

    sMinimizer = pParameterList->getString(PARAM_MINIMIZER);

    // Validate our Minimizers
    foreach(CMinimizer *Minimizer, vMinimizerList) {
      Minimizer->validate();
    }

    // Reset Variable
    pMinimizer = 0;

    // Find and Assign
    foreach(CMinimizer *Minimizer, vMinimizerList) {
      if (Minimizer->getLabel() == sMinimizer)
        pMinimizer = Minimizer;
    }

    if (pMinimizer == 0)
      throw string("TRANSLATE ME: Unknown minimizer: " + sMinimizer); // TODO: Translate this

    pMinimizer->validate();

  } catch (string Ex) {
    Ex = "CMinimizerManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMinimizerManager::build()
// Build our Minimizer
//**********************************************************************
void CMinimizerManager::build() {
  try {
    if (CRuntimeController::Instance()->getRunMode() == RUN_MODE_BASIC)
          return;

    pMinimizer->build();

  } catch (string Ex) {
    Ex = "CMinimizerManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMinimizer::execute()
// Execute Our Minimisation
//**********************************************************************
void CMinimizerManager::execute() {
  try {
    if (pMinimizer == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    pMinimizer->runEstimation();

  } catch (string Ex) {
    Ex = "CMinimizerManager.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMinimizerManager::~CMinimizerManager()
// Default De-Constructor
//**********************************************************************
CMinimizerManager::~CMinimizerManager() {
}
