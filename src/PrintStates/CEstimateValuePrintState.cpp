//============================================================================
// Name        : CEstimateValuePrintState.cpp
// Author      : S.Rasmussen
// Date        : 12/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CEstimateValuePrintState.h"
#include "../CEstimateManager.h"
#include "../Estimates/CEstimate.h"

//**********************************************************************
// CEstimateValuePrintState::CEstimateValuePrintState()
// Default Constructor
//**********************************************************************
CEstimateValuePrintState::CEstimateValuePrintState() {
  // Vars
  eState          = STATE_FINALIZATION;
  bHeaderWritten  = false;
  bOverwrite      = false;
}

//**********************************************************************
// void CEstimateValuePrintState::execute()
// Execute our Print State
//**********************************************************************
void CEstimateValuePrintState::execute() {
  try {
    // Open Stream
    openStream();

    // Variables
    CEstimateManager *pEstimateManager = CEstimateManager::Instance();
    int              iCount            = pEstimateManager->getEstimateCount();

    if (!bHeaderWritten) {
      for (int i = 0; i < iCount; ++i) {
        CEstimate *pEstimate = pEstimateManager->getEstimate(i);
        cout << pEstimate->getParameter();

        if((i+1)<iCount)
          cout << CONFIG_SEPERATOR_ESTIMATE_VALUES;
      }
      cout << "\n";

      bHeaderWritten = true;
    }

    for (int i = 0; i < iCount; ++i) {
      CEstimate *pEstimate = pEstimateManager->getEstimate(i);
      cout << pEstimate->getValue();
      if((i+1)<iCount) cout << CONFIG_SEPERATOR_ESTIMATE_VALUES;
    }
    cout << endl;

    // Close stream
    closeStream();

  } catch (string Ex) {
    Ex = "CEstimateValuePrintState.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CEstimateValuePrintState::~CEstimateValuePrintState()
// Destructor
//**********************************************************************
CEstimateValuePrintState::~CEstimateValuePrintState() {
}
