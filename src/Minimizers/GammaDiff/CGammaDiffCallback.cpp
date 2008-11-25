//============================================================================
// Name        : CGammaDiffCallback.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CGammaDiffCallback.h"
#include "../../ObjectiveFunction/CObjectiveFunction.h"
#include "../../RuntimeThread/CRuntimeThread.h"
#include "../../CEstimateManager.h"
#include "../../Estimates/CEstimate.h"

//**********************************************************************
// CGammaDiffCallback::CGammaDiffCallback()
// Default Constructor
//**********************************************************************
CGammaDiffCallback::CGammaDiffCallback() : CBaseObject(0) {

  // Vars
  pEstimateManager    = CEstimateManager::Instance();
}

//**********************************************************************
// double CGammaDiffCallback::operator()(const vector<double>& Parameters)
// Operatior() for Minimiser CallBack
//**********************************************************************
double CGammaDiffCallback::operator()(const vector<double>& Parameters) {

  // Update our Components with the New Parameters
  int iCount = pEstimateManager->getEnabledEstimateCount();
  for (int i = 0; i < iCount; ++i) {
    pEstimateManager->getEnabledEstimate(i)->setValue(Parameters[i]);
  }

  CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();

#ifndef OPTIMISE
  try {
#endif
    // Re-Run
    CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
    pThread->rebuild();
    pThread->startModel();

    // Workout our Objective Score
    pObjectiveFunction->execute();

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CBetaDiffCallback.operator()->" + Ex;
    cout << Ex << endl;
    throw Ex;
  }
#endif

  // Return Objective Score to Minimiser
  return pObjectiveFunction->getScore();
}

//**********************************************************************
// CGammaDiffCallback::~CGammaDiffCallback()
// Default Destructor
//**********************************************************************
CGammaDiffCallback::~CGammaDiffCallback() {
}
