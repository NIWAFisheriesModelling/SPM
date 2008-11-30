//============================================================================
// Name        : CMCMC.cpp
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CMCMC.h"
#include "../ObjectiveFunction/CObjectiveFunction.h"
#include "../CEstimateManager.h"
#include "../RuntimeThread/CRuntimeThread.h"
#include "../Estimates/CEstimate.h"

// Singleton Variable
CMCMC* CMCMC::clInstance = 0;

//**********************************************************************
// CMCMC::CMCMC()
// Default Constructor
//**********************************************************************
CMCMC::CMCMC() {
}

//**********************************************************************
// CMCMC* CMCMC::Instance()
// Instance Method - Singleton
//**********************************************************************
CMCMC* CMCMC::Instance() {
  if (clInstance == 0)
    clInstance = new CMCMC();
  return clInstance;
}

//**********************************************************************
// void CMCMC::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CMCMC::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CMCMC::addThread(CRuntimeThread *Thread)
// Add Thread
//**********************************************************************
void CMCMC::addThread(CRuntimeThread *Thread) {
  lock lk(mutThread);
  vThreadList.push_back(Thread);
}

//**********************************************************************
// void CMCMC::addAdaptAt(int value)
// Add AdaptAt
//**********************************************************************
void CMCMC::addAdaptAt(int value) {
  vAdaptAtList.push_back(value);
}

//**********************************************************************
// void CMCMC::validate()
// Validate our MCMC
//**********************************************************************
void CMCMC::validate() {
  try {

  } catch (string Ex) {
    Ex = "CMCMC.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::build()
// Build our MCMC
//**********************************************************************
void CMCMC::build() {
  try {

  } catch (string Ex) {
    Ex = "CMCMC.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::execute()
// Execute our MCMC
//**********************************************************************
void CMCMC::execute() {
  try {
    // Variables
    int iEstimateCount      = CEstimateManager::Instance()->getEnabledEstimateCount();
    int iThreadCount        = pConfig->getNumberOfThreads();
    int iThreadListSize     = 0;

    // Wait until all threads have subscribed.
    while (iThreadListSize != iThreadCount) {
      if (true) {
        lock lk(mutThread);
        iThreadListSize = (int)vThreadList.size();
      }
      sleep(1);
    }

    // Start MCMC
    for (int i = 0; i < iLength; ++i) {

      foreach(CRuntimeThread *Thread, vThreadList) {
        // Get Handle to target thread's estimate manager
        CEstimateManager *pEstimateManager = Thread->getEstimateManager();

        // Generate new Vars
        for (int j = 0; j < iEstimateCount; ++j) {
          double dValue = 0.0;
          pEstimateManager->getEstimate(j)->setValue(dValue);
        }

        // Un-"Wait" thread
        Thread->setWaiting(false);
      }

      // Wait until all threads are "Waiting"
      foreach(CRuntimeThread *Thread, vThreadList) {
        while(!Thread->getWaiting())
          sleep(1);
      }

      // Work Through and Look For our Match
      /*foreach(CRuntimeThread *Thread, vThreadList) {
        // Print Thread to PrintState
        PrintState->print(thread);
        // Check if We want
        if ( ((Thread->getScore() < dBestScore) || (Thread->getScore() < randomScore)) && (i < iLength) ) {
          bestScore = Thread->getVariables();
          break;
        } else if (i >= iLength)
          break;

        ++i;
      }*/
    }

    // Terminate Threads
    foreach(CRuntimeThread *Thread, vThreadList) {
      Thread->setTerminate(true);
    }

  } catch (string Ex) {
   Ex = "CMCMC.execute()->" + Ex;
   throw Ex;
  }
}

//**********************************************************************
// void CMCMC::sleep(int time)
// Platform-Independent Sleep
//**********************************************************************
void CMCMC::sleep(int milliseconds) {
#ifdef __MINGW32__
  Sleep(milliseconds);
#else
  usleep( milliseconds * 1000);
#endif
}

//**********************************************************************
// CMCMC::~CMCMC()
// Default De-Constructor
//**********************************************************************
CMCMC::~CMCMC() {
  vThreadList.clear();
}
