//============================================================================
// Name        : CDESolverInterface.cpp
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CDESolverInterface.h"
#include "CDESolverCallback.h"
#include "../../CEstimateManager.h"
#include "../../Estimates/CEstimate.h"

//**********************************************************************
// CDESolverInterface::CDESolverInterface()
// Default Constructor
//**********************************************************************
CDESolverInterface::CDESolverInterface() {
}

//**********************************************************************
// void CDESolverInterface::runEstimation()
// run our Estimation
//**********************************************************************
void CDESolverInterface::runEstimation() {
  // Variables
  CEstimateManager      *pEstimateManager    = CEstimateManager::Instance();
  int                   iCount               = 0;

  try {
    // Get Number of Estimate Variables.
    iCount = pEstimateManager->getEnabledEstimateCount();

    if (iCount == 0)
      throw string(ERROR_ENABLED_ESTIMATES);

    // Setup our Solver
    CDESolverCallback     clDESolver = CDESolverCallback(iCount, 5);

    // Setup Lower, Upper Bounds
    double dLowerBounds[iCount];
    double dUpperBounds[iCount];

    for (int i = 0; i < iCount; ++i) {
      CEstimate *pEstimate = pEstimateManager->getEnabledEstimate(i);
      dLowerBounds[i] = pEstimate->getLowerBound();
      dUpperBounds[i] = pEstimate->getUpperBound();
    }

    clDESolver.Setup(dLowerBounds, dUpperBounds, stBest1Exp, 0.01, 0.5);

    clDESolver.Solve(100); // Max Generations

  } catch (string Ex) {
    Ex = "CDESolverInterface.runEstimation()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDESolverInterface::~CDESolverInterface()
// Default De-Constructor
//**********************************************************************
CDESolverInterface::~CDESolverInterface() {
}
