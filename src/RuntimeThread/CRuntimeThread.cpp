//============================================================================
// Name        : CRuntimeThread.cpp
// Author      : S.Rasmussen
// Date        : 18/08/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "CRuntimeThread.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../PreferenceFunctions/CPreferenceFunctionManager.h"
#include "../Estimates/CEstimateManager.h"
#include "../InitializationPhases/CInitializationPhaseManager.h"
#include "../Layers/CLayerManager.h"
#include "../Observations/CObservationManager.h"
#include "../Penalties/CPenaltyManager.h"
#include "../Priors/CPriorManager.h"
#include "../Processes/CProcessManager.h"
#include "../Profiles/CProfileManager.h"
#include "../Catchabilities/CCatchabilityManager.h"
#include "../Selectivities/CSelectivityManager.h"
#include "../TimeSteps/CTimeStepManager.h"
#include "../ObjectiveFunction/CObjectiveFunction.h"
#include "../TimeSteps/CTimeStep.h"
#include "../Helpers/ForEach.h"
#include "../InitializationPhases/CInitializationPhase.h"
#include "../Catchabilities/CCatchabilityManager.h"
#include "../Reporters/CReporterManager.h"
#include "../CRuntimeController.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CRuntimeThread::CRuntimeThread()
// Default Constructor
//**********************************************************************
CRuntimeThread::CRuntimeThread() {

  // Create our Instances
  pDirectedProcessManager  = CPreferenceFunctionManager::Instance();
  pEstimateManager         = CEstimateManager::Instance();
  pInitializationManager   = CInitializationPhaseManager::Instance();
  pLayerManager            = CLayerManager::Instance();
  pObjectiveFunction       = CObjectiveFunction::Instance();
  pObservationManager      = CObservationManager::Instance();
  pPenaltyManager          = CPenaltyManager::Instance();
  pPriorManager            = CPriorManager::Instance();
  pProcessManager          = CProcessManager::Instance();
  pProfileManager          = CProfileManager::Instance();
  pQManager                = CCatchabilityManager::Instance();
  pReporterManager         = CReporterManager::Instance();
  pSelectivityManager      = CSelectivityManager::Instance();
  pTimeStepManager         = CTimeStepManager::Instance();
  pWorld                   = CWorld::Instance();

  // Variables
  bWaiting        = false;
}

//**********************************************************************
// void CRuntimeThread::setWaiting(bool value)
// Set our Waiting Variable
//**********************************************************************
void CRuntimeThread::setWaiting(bool value) {
  lock lk(mutWaiting);
  bWaiting = value;
}

//**********************************************************************
// bool CRuntimeThread::getWaiting()
// Return our Waiting Variable.
//**********************************************************************
bool CRuntimeThread::getWaiting() {
  lock lk(mutWaiting);
  return bWaiting;
}

//**********************************************************************
// void CRuntimeThread::setTerminate(bool value)
// Set our Terminate Value
//**********************************************************************
void CRuntimeThread::setTerminate(bool value) {
  lock lk(mutTerminate);
  bTerminate = value;
}

//**********************************************************************
// bool CRuntimeThread::getTerminate()
// Return out Terminate Variable
//**********************************************************************
bool CRuntimeThread::getTerminate() {
  lock lk(mutTerminate);
  return bTerminate;
}

//**********************************************************************
// void CRuntimeThread::validate()
// Validate This Thread
//**********************************************************************
void CRuntimeThread::validate() {
  eCurrentState = STATE_VALIDATION;

  // Validate Them in Alphabetical Order, After World
  pWorld->validate(); // First because it's our Base
  pDirectedProcessManager->validate();
  pEstimateManager->validate();
  pInitializationManager->validate();
  pLayerManager->validate();
  pObservationManager->validate();
  pPenaltyManager->validate();
  pPriorManager->validate();
  pProcessManager->validate();
  pProfileManager->validate();
  pReporterManager->validate();
  pSelectivityManager->validate();
  pTimeStepManager->validate();
  CCatchabilityManager::Instance()->validate(); // TODO: FIX THIS
}

//**********************************************************************
// void CRuntimeThread::build()
// Build the thread's relationships
//**********************************************************************
void CRuntimeThread::build() {
  eCurrentState = STATE_CONSTRUCTION;

  // do not fuck with this order
  // There are dependencies based on the build order.
  pWorld->build();
  pProcessManager->build();

  // Build Rest that rely on the Above.
  pDirectedProcessManager->build();
  pEstimateManager->build();
  pPenaltyManager->build();
  pInitializationManager->build();
  pLayerManager->build();
  pProfileManager->build();
  pSelectivityManager->build();
  pObservationManager->build();
  pTimeStepManager->build();
  pReporterManager->build();

  // Build our Own Locals
  iNumberOfYears = pWorld->getCurrentYear() - pWorld->getInitialYear();
}

//**********************************************************************
// void CRuntimeThread::rebuild()
// Re-Build the components with caches.
//**********************************************************************
void CRuntimeThread::rebuild() {
  pWorld->zeroGrid();

  pProcessManager->rebuild();
  pSelectivityManager->rebuild();
  pPenaltyManager->clearFlaggedPenaltyList();
}

//**********************************************************************
// void CRuntimeThread::executeBasicRun()
// Start our Basic Run
//**********************************************************************
void CRuntimeThread::executeBasicRun() {
  // Validate, Build, Start
  startModel();

  // Execute Objective
  pObjectiveFunction->execute();
  dScore = pObjectiveFunction->getScore();

  // Change State
  eCurrentState = STATE_FINALIZATION;
  pReporterManager->execute(eCurrentState);
}

//**********************************************************************
// void CRuntimeThread::executeEstimationRun()
// Execute Estimations
//**********************************************************************
void CRuntimeThread::executeEstimationRun() {
  CMinimizerManager *pMinimizerManager = CMinimizerManager::Instance();
  pMinimizerManager->execute();
}

//**********************************************************************
// void CRuntimeThread::executeMCMC()
// Execute the MCMC path for this thread. Basically, become an MCMC subscriber
//**********************************************************************
void CRuntimeThread::executeMCMC() {

  // Variables
  boost::xtime xt;

  while (!getTerminate()) {

    // Wait Until We Are not Waiting
    while ( (getWaiting()) && (!getTerminate()) ) {
      boost::xtime_get(&xt, boost::TIME_UTC);
      xt.nsec += 10;
      boost::thread::sleep(xt);
    }

    if (getTerminate())
      return;

    // We are not waiting, this means we have our variables and are
    // ready to execute a run
    rebuild();
    startModel();

    // Execute Objective
    pObjectiveFunction->execute();
    dScore = pObjectiveFunction->getScore();

    // Now, we wait for the MCMC to publish new variables
    setWaiting(true);
  }
}

//**********************************************************************
// void CRuntimeThread::startModel()
// Start The Model
//**********************************************************************
void CRuntimeThread::startModel() {

  // Set State To Burn-In (Initialisation) & Execute
  eCurrentState = STATE_INITIALIZATION;
  pInitializationManager->execute();

  pReporterManager->execute(eCurrentState);

  // Flag and start modelling
  eCurrentState = STATE_MODELLING;
  pTimeStepManager->execute();

  pWorld->debugToScreen();
}

//**********************************************************************
// void CRuntimeThread::clone(CRuntimeThread *Thread)
// Clone our Parameter
//**********************************************************************
void CRuntimeThread::clone(CRuntimeThread *Thread) {

  pDirectedProcessManager->clone(Thread->pDirectedProcessManager);
  pEstimateManager->clone(Thread->pEstimateManager);
  pLayerManager->clone(Thread->pLayerManager);
  pObservationManager->clone(Thread->pObservationManager);
  pReporterManager->clone(Thread->pReporterManager);
  pPenaltyManager->clone(Thread->pPenaltyManager);
  pPriorManager->clone(Thread->pPriorManager);
  pProcessManager->clone(Thread->pProcessManager);
  pProfileManager->clone(Thread->pProfileManager);
  pQManager->clone(Thread->pQManager);
  pSelectivityManager->clone(Thread->pSelectivityManager);
  pInitializationManager->clone(Thread->pInitializationManager);
  pTimeStepManager->clone(Thread->pTimeStepManager);
  pWorld->clone(Thread->pWorld);
}

//**********************************************************************
// CRuntimeThread::~CRuntimeThread()
// Destructor
//**********************************************************************
CRuntimeThread::~CRuntimeThread() {
  // Destroy Singleton Classes
  CReporterManager::Destroy();
  CPreferenceFunctionManager::Destroy();
  CEstimateManager::Destroy();
  CInitializationPhaseManager::Destroy();
  CLayerManager::Destroy();
  CMinimizerManager::Destroy();
  CObjectiveFunction::Destroy();
  CObservationManager::Destroy();
  CPenaltyManager::Destroy();
  CPriorManager::Destroy();
  CProcessManager::Destroy();
  CProfileManager::Destroy();
  CCatchabilityManager::Destroy();
  CSelectivityManager::Destroy();
  CTimeStepManager::Destroy();
  CWorld::Destroy();
}
