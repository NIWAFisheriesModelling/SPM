//============================================================================
// Name        : CMinimizer.cpp
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CMinimizer.h"
#include "CMinimizerManager.h"

//**********************************************************************
// CMinimizer::CMinimizer()
// Default Constructor
//**********************************************************************
CMinimizer::CMinimizer() {
  iMaxIterations      = 300;
  iMaxEvaluations     = 1000;
  dGradientTolerance  = 0.002;
  dStepSize           = 1e-4;
  pHessian            = 0;
  iEstimateCount      = 0;
}

//**********************************************************************
// void CMinimizer::build()
//
//**********************************************************************
void CMinimizer::build() {

  //CMinimizerManager *pManager = CMinimizerManager::Instance();
  iEstimateCount = 0; //pManager->getEnabledEstimateCount();

  pHessian = new double*[iEstimateCount];
  for (int i = 0; i < iEstimateCount; ++i)
    pHessian[i] = new double[iEstimateCount];

  for (int i = 0; i < iEstimateCount; ++i)
    for (int j = 0; j < iEstimateCount; ++j)
      pHessian[i][j] = 0.0;
}

//**********************************************************************
// CMinimizer::~CMinimizer()
// Default De-Constructor
//**********************************************************************
CMinimizer::~CMinimizer() {

  for (int i = 0; i < iEstimateCount; ++i)
    delete [] pHessian[i];
  delete [] pHessian;
}
