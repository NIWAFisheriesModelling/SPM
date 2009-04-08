//============================================================================
// Name        : CDESolver.cpp
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "CDESolver.h"
#include "CDESolverCallback.h"
#include "../../Estimates/CEstimateManager.h"
#include "../../Estimates/CEstimate.h"

// Namespaces
using std::cout;
using std::endl;

//**********************************************************************
// CDESolverInterface::CDESolverInterface()
// Default Constructor
//**********************************************************************
CDESolver::CDESolver() {
}

//**********************************************************************
// void CDESolver::runEstimation()
// run our Estimation
//**********************************************************************
void CDESolver::runEstimation() {
  // Variables
  CEstimateManager      *pEstimateManager    = CEstimateManager::Instance();
  int                   iCount               = 0;

  try {
    // Get Number of Estimate Variables.
    iCount = pEstimateManager->getEnabledEstimateCount();

    if (iCount == 0)
      throw string(ERROR_ENABLED_ESTIMATES);

    // Setup our Solver
    CDESolverCallback     clDESolver = CDESolverCallback(iCount, 30);

    // Setup Lower, Upper Bounds
    vector<double> vLowerBounds;
    vector<double> vUpperBounds;
    vector<double> vStartValues;

    for (int i = 0; i < iCount; ++i) {
      CEstimate *pEstimate = pEstimateManager->getEnabledEstimate(i);
      vLowerBounds.push_back(pEstimate->getLowerBound());
      vUpperBounds.push_back(pEstimate->getUpperBound());
      vStartValues.push_back(pEstimate->getValue());
    }

    clDESolver.Setup(vStartValues, vLowerBounds, vUpperBounds, stBest1Exp, 0.8, 1.1);

    if (clDESolver.Solve(500)) {
      cout << "Convergence was successful" << endl;
      cout << "Final Score: " << clDESolver.getEnergy() << endl;
      cout << "Score took " << clDESolver.getGenerations() << " generations to find" << endl;
    } else
      cout << "Failed to converge, ran out of generations" << endl;

  } catch (string Ex) {
    Ex = "CDESolverInterface.runEstimation()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDESolver::~CDESolver()
// Default De-Constructor
//**********************************************************************
CDESolver::~CDESolver() {
}
