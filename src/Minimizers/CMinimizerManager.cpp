//============================================================================
// Name        : CMinimizerManager.cpp
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CMinimizerManager.h"
#include "CMinimizer.h"
#include "../RuntimeThread/CRuntimeThread.h"
#include "../Estimates/CEstimateManager.h"
#include "../Estimates/CEstimate.h"
#include "../Reports/CReportManager.h"
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
    if ( (CRuntimeController::Instance()->getRunMode() == RUN_MODE_BASIC)
        || (CRuntimeController::Instance()->getRunMode() == RUN_MODE_SIMULATION) )
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

    // See if we have a valid minimizer defined
    if (pMinimizer == 0)
      CError::errorUnknown(PARAM_MINIMIZER, sMinimizer);

  } catch (string &Ex) {
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
    if ( (CRuntimeController::Instance()->getRunMode() == RUN_MODE_BASIC)
        || (CRuntimeController::Instance()->getRunMode() == RUN_MODE_SIMULATION) )
      return;

    pMinimizer->build();

  } catch (string &Ex) {
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

    /*
     * We need to go through each of the estimates now and check out what phases
     * that have been given. This will allow us to determine how many minimisation
     * phases we need to run.
     */
    int estimationPhases = 1;

    CEstimateManager *pEstimateManager = CEstimateManager::Instance();
    int enabledEstimates = pEstimateManager->getEnabledEstimateCount();
    for (int i = 0; i < enabledEstimates; ++i) {
      int estimationPhase = pEstimateManager->getEnabledEstimate(i)->getEstimationPhase();
      estimationPhases = estimationPhases > estimationPhase ? estimationPhases : estimationPhase;
    }

    /**
     * Now we do X estimations where X is the highest number
     * of phases we found in the configuration file.
     */
    for (int i = 0; i < estimationPhases; ++i) {
      string reportPrefix = "estimation_" + boost::lexical_cast<string>(i) + "_";
      CReportManager::Instance()->setReportPrefix(reportPrefix);

      pEstimateManager->setCurrentPhase(i);

      pMinimizer->runEstimation();
      if(pMinimizer->getBuildCovariance())
        pMinimizer->buildCovarianceMatrix();
    }

  } catch (string &Ex) {
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
