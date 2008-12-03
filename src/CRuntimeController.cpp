
// Name        : CRuntimeController.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "Translations/Translations.h"
#include "CRuntimeController.h"
#include "CConfiguration.h"
#include "CEstimateManager.h"
#include "CProfileManager.h"
#include "ConfigLoaders/CEstimationConfigLoader.h"
#include "ConfigLoaders/COutputConfigLoader.h"
#include "ConfigLoaders/CPopulationConfigLoader.h"
#include "ConfigLoaders/CEstimateValueConfigLoader.h"
#include "RuntimeThread/CRuntimeThread.h"
#include "MCMC/CMCMC.h"
#include "CMinimizerManager.h"

// Singleton Variable
CRuntimeController* CRuntimeController::clInstance = 0;

// Typedefs
typedef boost::mutex::scoped_lock lock;

//**********************************************************************
// CRuntimeController::CRuntimeController()
// Default Constructor
//**********************************************************************
CRuntimeController::CRuntimeController() {
  // Setup Variables
  eRunMode                = RUN_MODE_INVALID;
  iCurrentEstimateValue   = 0;
  runtimeBarrier          = new boost::barrier(2);
}

//**********************************************************************
// CRuntimeController* CRuntimeController::Instance()
// Instance Method - Singleton
//**********************************************************************
CRuntimeController* CRuntimeController::Instance() {
  if (clInstance == 0)
    clInstance = new CRuntimeController();

  return clInstance;
}

//**********************************************************************
// void CRuntimeController::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CRuntimeController::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CRuntimeController::setRunMode(string value)
// Set The Run Mode with a String
//**********************************************************************
void CRuntimeController::setRunMode(string value) {
  try {
    if (value == MODE_BASIC_RUN)
      eRunMode = RUN_MODE_BASIC;
    else if (value == MODE_ESTIMATION)
      eRunMode = RUN_MODE_ESTIMATION;
    else if (value == MODE_PROFILE)
      eRunMode = RUN_MODE_PROFILE;
    else if (value == MODE_MCMC)
      eRunMode = RUN_MODE_MARKOV_CHAIN_MONTE_CARLO;
    else if (value == MODE_FORWARD_PROJECTION)
      eRunMode = RUN_MODE_FORWARD_PROJECTION;
    else
      throw string(ERROR_UNKNOWN_RUN_MODE + value);

  } catch (string Ex) {
    Ex = "CRuntimeController.setRunMode()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// EState CRuntimeController::getCurrentState()
//
//**********************************************************************
EState CRuntimeController::getCurrentState() {
  return pBaseThread->getCurrentState();
}

//**********************************************************************
// CRuntimeThread* CRuntimeController::getCurrentThread()
// Return the Current Thread
//**********************************************************************
CRuntimeThread* CRuntimeController::getCurrentThread() {
  return pBaseThread;
}

//**********************************************************************
// void CRuntimeController::loadConfiguration()
// Load our Configurations
//**********************************************************************
void CRuntimeController::loadConfiguration() {
  try {
    // Estimation
    CConfiguration *pConfig = CConfiguration::Instance();
    string sConfigPath = pConfig->getConfigPath();

    CEstimationConfigLoader clEstimationConfigLoader = CEstimationConfigLoader(sConfigPath);
    clEstimationConfigLoader.processConfigFile();

    // Output
    COutputConfigLoader clOutputConfigLoader = COutputConfigLoader(sConfigPath);
    clOutputConfigLoader.processConfigFile();

    // Population
    CPopulationConfigLoader clPopulationConfigLoader = CPopulationConfigLoader(sConfigPath);
    clPopulationConfigLoader.processConfigFile();

    // Estimate Values
    if (pConfig->getUseEstimateValues()) {
      CEstimateValueConfigLoader clEstimateValueConfigLoader = CEstimateValueConfigLoader(sConfigPath);
      clEstimateValueConfigLoader.processConfigFile();
    }

  } catch (string Ex) {
    Ex = "CRuntimeController.loadConfiguration()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CRuntimeController::run()
// Run our Model. Break up Flow into Correct Functions
//**********************************************************************
void CRuntimeController::run() {
  try {
    CConfiguration    *pConfig          = CConfiguration::Instance();
    CEstimateManager  *pEstimateManager = CEstimateManager::Instance();
    CProfileManager   *pProfileManager  = CProfileManager::Instance();

    // Validate our Configuration
    pConfig->validate();

    // Create our Base Thread
    pBaseThread = new CRuntimeThread();
    pBaseThread->validate();
    pBaseThread->build();

    CMinimizerManager *pMinimizer = CMinimizerManager::Instance();
    pMinimizer->validate();
    pMinimizer->build();

    // Set a default number of estimate values we want to run
    // the model for. This defaults to 1, because we always
    // want to run atleast 1 iteration of the model
    int iEstimateValueCount = 1;

    // If we are using pre-loaded estimate values, how many?
    if (pConfig->getUseEstimateValues())
      iEstimateValueCount = pEstimateManager->getEstimateValueCount();

    for (int i = 0; i < iEstimateValueCount; ++i) {
      // If we are using loaded estimate values, set them now.
      if (pConfig->getUseEstimateValues())
        pEstimateManager->loadEstimateValues(i);

      // Run the model.
      switch(eRunMode) {
        case RUN_MODE_BASIC:
          pBaseThread->executeBasicRun();
          break;
        case RUN_MODE_ESTIMATION:
          startEstimation();
          break;
        case RUN_MODE_PROFILE:
          // Get Minimizer Manager
          pProfileManager->execute();
          break;
        case RUN_MODE_MARKOV_CHAIN_MONTE_CARLO:
          startEstimation();
          startMCMC();
          break;
        default:
          throw string(ERROR_UNKNOWN_RUN_MODE);
      }
    }

  } catch (string Ex) {
    Ex = "CRuntimeController.run()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CRuntimeController::startEstimation()
// Start Estimation Run
//**********************************************************************
void CRuntimeController::startEstimation() {
  try {
    // Get Minimizer Manager
    CMinimizerManager *pMinimizer = CMinimizerManager::Instance();

    // Get Configuration
    // CConfiguration *pConfig = CConfiguration::Instance();
    // int iNumberOfThreads = pConfig->getNumberOfThreads();

    // Create Threads
   /* boost::thread_group threads;
    for (int i = 0; i < iNumberOfThreads; ++i)
      threads.create_thread(&CRuntimeController::initEstimationThread);*/

    // Start the Minimizer.
    pMinimizer->execute();

    // Wait for all threads to finish.
//    threads.join_all();

  } catch (string Ex) {
    Ex = "CRuntimeController.startEstimation()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// static void CRuntimeController::initEstimationThread()
// Initialise an Estimation Thread
//**********************************************************************
void CRuntimeController::initEstimationThread() {

  CRuntimeController  *pThis    = CRuntimeController::Instance();
  CRuntimeThread      *pThread  = 0;
  pThread             = new CRuntimeThread();

  if (true) {
    // Clone
    lock lk(pThis->runtimeLock);
    pThread->clone(pThis->pBaseThread);

    // Register with Publisher (CMinimizerManager)
    CMinimizerManager *pMinimizer = CMinimizerManager::Instance();
    pMinimizer->addThread(pThread);
  }

  // Validate and Build
  pThread->validate();
  pThread->build();

  // Setup Vars
  pThread->setWaiting(true);
  pThread->setTerminate(false);

  // Execute
  // ToDo: Complete Minimizer Pool
  //pThread->executeEstimation();

  delete pThread;
}

//**********************************************************************
// void CRuntimeController::startMCMC()
// Start MCMC
//**********************************************************************
void CRuntimeController::startMCMC() {
  try {
    // Setup the MCMC Controller.
    CMCMC *pMCMC = CMCMC::Instance();
    pMCMC->validate();
    pMCMC->build();

    // Get Configuration
    CConfiguration *pConfig = CConfiguration::Instance();
    int iNumberOfThreads = pConfig->getNumberOfThreads();

    // Create Threads
    boost::thread_group threads;
    for (int i = 0; i < iNumberOfThreads; ++i)
        threads.create_thread(&CRuntimeController::initMCMCThread);

    // Start the MCMC
    pMCMC->execute();

    // Wait for Threads to finish.
    threads.join_all();

  } catch (string Ex) {
    Ex = "CRuntimeController.startMCMC()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// static void CRuntimeController::initMCMCThread()
// Init an MCMC Thread
//**********************************************************************
void CRuntimeController::initMCMCThread() {

  CRuntimeController  *pThis    = CRuntimeController::Instance();
  CRuntimeThread      *pThread  = 0;
  pThread             = new CRuntimeThread();

  if (true) {
    // Clone
    lock lk(pThis->runtimeLock);
    pThread->clone(pThis->pBaseThread);

    // Register with Publisher (MCMC)
    CMCMC *pMCMC = CMCMC::Instance();
    pMCMC->addThread(pThread);
  }

  // Validate and Build
  pThread->validate();
  pThread->build();

  // Setup Vars
  pThread->setWaiting(true);
  pThread->setTerminate(false);

  // Execute
  pThread->executeMCMC();

  delete pThread;
}

//**********************************************************************
// CRuntimeController::~CRuntimeController()
// Default De-Constructor
//**********************************************************************
CRuntimeController::~CRuntimeController() {
  CMCMC::Destroy();
  CMinimizerManager::Destroy();
}
