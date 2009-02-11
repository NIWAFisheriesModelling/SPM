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
#include "../Estimates/CEstimateManager.h"

//**********************************************************************
// CMinimizer::CMinimizer()
// Default Constructor
//**********************************************************************
CMinimizer::CMinimizer() {
  // Default Variables
  pHessian  = 0;

  // Register user allowed Parameters
  pParameterList->registerAllowed(PARAM_MAX_ITERS);
  pParameterList->registerAllowed(PARAM_MAX_EVALS);
  pParameterList->registerAllowed(PARAM_GRAD_TOL);
  pParameterList->registerAllowed(PARAM_STEP_SIZE);
}

//**********************************************************************
// void CMinimizer::validate()
//
//**********************************************************************
void CMinimizer::validate() {
  try {
    // Base
    CBaseBuild::validate();

    // Assign our param
    iMaxIterations      = pParameterList->getInt(PARAM_MAX_ITERS);
    iMaxEvaluations     = pParameterList->getInt(PARAM_MAX_EVALS);
    dGradientTolerance  = pParameterList->getDouble(PARAM_GRAD_TOL);
    dStepSize           = pParameterList->getDouble(PARAM_STEP_SIZE);

  } catch (string Ex) {
    Ex = "CMinimizer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMinimizer::build()
//
//**********************************************************************
void CMinimizer::build() {

  CEstimateManager *pManager = CEstimateManager::Instance();
  iEstimateCount = pManager->getEnabledEstimateCount();

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
  if (pHessian != 0) {
    for (int i = 0; i < iEstimateCount; ++i)
      delete [] pHessian[i];
    delete [] pHessian;
  }
}
