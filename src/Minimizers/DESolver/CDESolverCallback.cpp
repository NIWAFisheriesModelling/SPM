//============================================================================
// Name        : CDESolverCallback.cpp
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CDESolverCallback.h"
#include "../../ObjectiveFunction/CObjectiveFunction.h"
#include "../../CPrintStateManager.h"
#include "../../RuntimeThread/CRuntimeThread.h"
#include "../../CEstimateManager.h"
#include "../../Estimates/CEstimate.h"

//**********************************************************************
// CDESolverCallback::CDESolverCallback()
// Default Constructor
//**********************************************************************
CDESolverCallback::CDESolverCallback(int dim,int pop) : CBaseObject(0), DESolver(dim,pop) {
  // Vars
  pEstimateManager    = CEstimateManager::Instance();
}

//**********************************************************************
// double CDESolverCallback::EnergyFunction(double trial[],bool &bAtSolution)
// Our CallBack Function. Returns our Score
//**********************************************************************
double CDESolverCallback::EnergyFunction(double trial[],bool &bAtSolution) {

  // Update our Components with the New Parameters
  int iCount = pEstimateManager->getEnabledEstimateCount();
  for (int i = 0; i < iCount; ++i) {
    pEstimateManager->getEnabledEstimate(i)->setValue(trial[i]);
  }

  CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();

  try {
    // Rebuild and Run
    CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
    pThread->rebuild();
    pThread->startModel();

    // Workout our Objective Score
    pObjectiveFunction->execute();

  } catch (string Ex) {
    Ex = "CDESolverCallback.EnergyFunction()->" + Ex;
    throw Ex;
  }

  return pObjectiveFunction->getScore();
}

//**********************************************************************
// CDESolverCallback::~CDESolverCallback()
// Default De-Constructor
//**********************************************************************
CDESolverCallback::~CDESolverCallback() {
}
