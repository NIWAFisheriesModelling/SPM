//============================================================================
// Name        : CRuntimeThread.cpp
// Author      : S.Rasmussen
// Date        : 18/08/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CRuntimeThread.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../DirectedProcesses/CDirectedProcessManager.h"
#include "../Estimates/CEstimateManager.h"
#include "../InitializationPhases/CInitializationPhaseManager.h"
#include "../Layers/CLayerManager.h"
#include "../Observations/CObservationManager.h"
#include "../Penalties/CPenaltyManager.h"
#include "../PrintStates/CPrintStateManager.h"
#include "../Priors/CPriorManager.h"
#include "../Processes/CProcessManager.h"
#include "../Profiles/CProfileManager.h"
#include "../Qs/CQManager.h"
#include "../Selectivities/CSelectivityManager.h"
#include "../TimeSteps/CTimeStepManager.h"
#include "../ObjectiveFunction/CObjectiveFunction.h"
#include "../TimeSteps/CTimeStep.h"
#include "../Helpers/ForEach.h"

//**********************************************************************
// CRuntimeThread::CRuntimeThread()
// Default Constructor
//**********************************************************************
CRuntimeThread::CRuntimeThread() {

  // Create our Instances
  pDirectedProcessManager  = CDirectedProcessManager::Instance();
  pEstimateManager         = CEstimateManager::Instance();
  pInitializationManager   = CInitializationPhaseManager::Instance();
  pLayerManager            = CLayerManager::Instance();
  pObjectiveFunction       = CObjectiveFunction::Instance();
  pObservationManager      = CObservationManager::Instance();
  pPenaltyManager          = CPenaltyManager::Instance();
  pPrintStateManager       = CPrintStateManager::Instance();
  pPriorManager            = CPriorManager::Instance();
  pProcessManager          = CProcessManager::Instance();
  pProfileManager          = CProfileManager::Instance();
  pQManager                = CQManager::Instance();
  pSelectivityManager      = CSelectivityManager::Instance();
  pTimeStepManager         = CTimeStepManager::Instance();
  pWorld                   = CWorld::Instance();

  // Variables
  bWaiting        = false;

  for (int i = 0; i < pConfig->getInitilizationPhaseCount(); ++i)
    vInitializationList.push_back(pConfig->getInitializationPhase(i));
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

  pConfig->validate();
  pDirectedProcessManager->validate();
  pEstimateManager->validate();
  pInitializationManager->validate();
  pLayerManager->validate();
  pObservationManager->validate();
  pPenaltyManager->validate();
  pPrintStateManager->validate();
  pPriorManager->validate();
  pProcessManager->validate();
  pProfileManager->validate();
  pSelectivityManager->validate();
  pTimeStepManager->validate();
}

//**********************************************************************
// void CRuntimeThread::build()
// Build the thread's relationships
//**********************************************************************
void CRuntimeThread::build() {
  eCurrentState = STATE_CONSTRUCTION;

  // Local Building
  vInitializationIndex.clear();
  foreach(string Label, vInitializationList) {
    vInitializationIndex.push_back(pInitializationManager->getTimeStep(Label));
  }

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
  pPrintStateManager->build();
  pSelectivityManager->build();
  pObservationManager->build();
  pTimeStepManager->build();

  // Build our Own Locals
  iNumberOfYears = pConfig->getNumberOfYearsToRun();
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
  pPrintStateManager->execute(eCurrentState);
}

//**********************************************************************
// void CRuntimeThread::executeEstimationRun()
// Execute Estimations
//**********************************************************************
void CRuntimeThread::executeEstimationRun() {
  //CMinimizerManager *pMinimizerManager = CMinimizerManager::Instance();
  //pMinimizerManager->execute();
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
  foreach(CTimeStep *TimeStep, vInitializationIndex) {
    TimeStep->execute();
  }
  pPrintStateManager->execute(eCurrentState);

  // Flag and start modelling
  eCurrentState = STATE_MODELLING;

  int iTimeStepCount = pTimeStepManager->getTimeStepCount();
  // Loop Years and Steps And Execute.
  for (int i = 0; i < iNumberOfYears; ++i) {
    for (int j = 1; j <= iTimeStepCount; ++j) {
      pTimeStepManager->execute(i, j);

      pPrintStateManager->execute();
      pObservationManager->execute(i, j);
    }
  }
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
  CDirectedProcessManager::Destroy();
  CEstimateManager::Destroy();
  CInitializationPhaseManager::Destroy();
  CLayerManager::Destroy();
  CMinimizerManager::Destroy();
  CObjectiveFunction::Destroy();
  CObservationManager::Destroy();
  CPenaltyManager::Destroy();
  CPrintStateManager::Destroy();
  CPriorManager::Destroy();
  CProcessManager::Destroy();
  CProfileManager::Destroy();
  CQManager::Destroy();
  CSelectivityManager::Destroy();
  CTimeStepManager::Destroy();
  CWorld::Destroy();
}
