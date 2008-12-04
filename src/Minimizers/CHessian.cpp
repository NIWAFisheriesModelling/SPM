//============================================================================
// Name        : CHessian.cpp
// Author      : S.Rasmussen
// Date        : 2/12/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <math.h>

// Local Headers
#include "CHessian.h"
#include "../CEstimateManager.h"
#include "../Estimates/CEstimate.h"

//**********************************************************************
// CHessian::CHessian()
// Default constructor
//**********************************************************************
CHessian::CHessian() {
  // Vars
  pGrid       = 0;

  // Get number of estimates
  iSize  = CEstimateManager::Instance()->getEnabledEstimateCount();

  pGrid = new double*[iSize];
  for (int i = 0; i < iSize; ++i)
    pGrid[i] = new double[iSize];

  for (int i = 0; i < iSize; ++i)
    for (int j = 0; j < iSize; ++j)
      pGrid[i][j] = 0.0;
}

//**********************************************************************
// void CHessian::constrainMagnitude(double max)
//
//**********************************************************************
void CHessian::constrainMagnitude(double max, double minDifference) {

  // Bring the Magnitude down to Max or -Max
  for (int i = 0; i < iSize; ++i) {
    for (int j = 0; j < i; ++j) {
      double dCovariance = pGrid[i][j] / sqrt(pGrid[i][i] * pGrid[j][j]);
      if (dCovariance > max) {
        pGrid[i][j] = max * sqrt(pGrid[i][i] * pGrid[j][j]);
        pGrid[j][i] = max * sqrt(pGrid[i][i] * pGrid[j][j]);
      } else if (dCovariance < -max) {
        pGrid[i][j] = -max * sqrt(pGrid[i][i] * pGrid[j][j]);
        pGrid[j][i] = -max * sqrt(pGrid[i][i] * pGrid[j][j]);
      }
    }
  }

  // Make sure nothing is less than minDifference
  vector<double> vDifferences;

  CEstimateManager *pEstimateManager  = CEstimateManager::Instance();
  for (int i = 0; i < iSize; ++i) {
    CEstimate *pEstimate = pEstimateManager->getEnabledEstimate(i);
    double dDifference = pEstimate->getUpperBound() - pEstimate->getLowerBound();

    if ( (pGrid[i][i]  < (minDifference * dDifference)) && (!isZero(pGrid[i][i])) ) {
      double dMultiply = (sqrt(minDifference) * dDifference) / sqrt(pGrid[i][i]);
      for (int j = 0; j < iSize; ++j) {
        pGrid[i][j] *= dMultiply;
        pGrid[j][i] *= dMultiply;
      }
    }
  }
}

//**********************************************************************
// CHessian::~CHessian()
// Default destructor
//**********************************************************************
CHessian::~CHessian() {

  for (int i = 0; i < iSize; ++i)
    delete [] pGrid[i];
  delete [] pGrid;
}
