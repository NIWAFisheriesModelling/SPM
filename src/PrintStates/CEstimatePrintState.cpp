//============================================================================
// Name        : CEstimatePrintState.cpp
// Author      : S.Rasmussen
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>
#include <fstream>

// Local Headers
#include "CEstimatePrintState.h"
#include "../CEstimateManager.h"
#include "../Estimates/CEstimate.h"

//**********************************************************************
// CEstimatePrintState::CEstimatePrintState()
// Default Constructor
//**********************************************************************
CEstimatePrintState::CEstimatePrintState() {
  eState = STATE_FINALIZATION;
}

//**********************************************************************
// void CEstimatePrintState::execute()
// Execute our Print State
//**********************************************************************
void CEstimatePrintState::execute() {
  try {
    // Variables
    CEstimateManager    *pEstimateManager     = CEstimateManager::Instance();

    // Open Stream
    openStream();

    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    int iCount = pEstimateManager->getEnabledEstimateCount();
    for (int i = 0; i < iCount; ++i) {
      CEstimate *pEstimate = pEstimateManager->getEnabledEstimate(i);

      cout << pEstimate->getParameter() << "\n";
      cout << PARAM_LOWER_BOUND << ": " << pEstimate->getLowerBound() << "\n";
      cout << PARAM_UPPER_BOUND << ": " << pEstimate->getUpperBound() << "\n";

      if (pEstimate->getPrior() != "")
        cout << PARAM_PRIOR << ": " << pEstimate->getPrior() << "\n";

      cout << PARAM_VALUE<< ": " << pEstimate->getValue() << "\n" << endl;
    }

    // close stream
    closeStream();

  } catch (string Ex) {
    Ex = "CEstimatePrintState.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CEstimatePrintState::~CEstimatePrintState()
// Default De-Constructor
//**********************************************************************
CEstimatePrintState::~CEstimatePrintState() {
}
