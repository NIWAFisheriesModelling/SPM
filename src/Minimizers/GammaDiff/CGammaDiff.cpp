//============================================================================
// Name        : CGammaDiff.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CGammaDiff.h"
#include "CGammaDiffCallback.h"
#include "Engine/GammaDiffEngine.h"
#include "../../Estimates/CEstimateManager.h"
#include "../../Estimates/CEstimate.h"

//**********************************************************************
// CGammaDiff::CGammaDiff()
// Default Constructor
//**********************************************************************
CGammaDiff::CGammaDiff() {

}

//**********************************************************************
//
//
//**********************************************************************
void CGammaDiff::runEstimation() {
  try {
    // Variables
    CGammaDiffCallback    clGammaDiffCallback;
    CEstimateManager      *pEstimateManager    = CEstimateManager::Instance();
    vector<double>        vStartValues;
    vector<double>        vLowerBounds;
    vector<double>        vUpperBounds;

    // Get our Variables, Upper and Lower Bounds From
    // The EstimateManager
    int iCount = pEstimateManager->getEnabledEstimateCount();

    for (int i = 0; i < iCount; ++i) {
      CEstimate *pEstimate = pEstimateManager->getEnabledEstimate(i);

      vStartValues.push_back(pEstimate->getValue());
      vLowerBounds.push_back(pEstimate->getLowerBound());
      vUpperBounds.push_back(pEstimate->getUpperBound());
    }

    int status = 0;

    GammaDiffEngine clGammaDiff;
    clGammaDiff.optimise_finite_differences(clGammaDiffCallback,
        vStartValues, vLowerBounds, vUpperBounds,
        status, true, iMaxIterations, iMaxEvaluations, dGradientTolerance,
        pHessian,1,dStepSize);

    /*cout << "Hessian: " << endl;
    for (int i = 0; i < iCount; ++i) {
      for (int j = 0; j < iCount; ++j)
        cout << pHessian[i][j] << "\t";
      cout << endl;
    }*/

  } catch (string Ex) {
    Ex = "CGammaDiff.runEstimation()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CGammaDiff::~CGammaDiff()
// Default Destructor
//**********************************************************************
CGammaDiff::~CGammaDiff() {

}
