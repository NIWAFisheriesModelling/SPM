//============================================================================
// Name        : CWorldGridPrintState.cpp
// Author      : S.Rasmussen
// Date        : 18/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "CWorldGridPrintState.h"
#include "../TimeSteps/CTimeStepManager.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CWorldGridPrintState::CWorldGridPrintState()
// Default Constructor
//**********************************************************************
CWorldGridPrintState::CWorldGridPrintState() {
  // Set the State This Runs in
  eState              = STATE_MODELLING; // It's not a state-based print-state by default
  iYear               = -1;
  iStep               = -1;
}

//**********************************************************************
// void CWorldGridPrintState::validate()
// Validate
//**********************************************************************
void CWorldGridPrintState::validate() {
  try {
    // Base
    CPrintState::validate();

    if (eState == STATE_MODELLING) {
      // Local Validation
      if (iYear == -1)
        CError::errorMissing(PARAM_YEAR);
      if (iStep == -1)
        CError::errorMissing(PARAM_TIME_STEP);
    }

  } catch (string Ex) {
    Ex = "CWorldGridPrintState.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CWorldGridPrintState::execute()
// Execute
//**********************************************************************
void CWorldGridPrintState::execute() {
//  try {
//    if (eState == STATE_MODELLING) {
//      CTimeStepManager *pTimeStepManager = CTimeStepManager::Instance();
//      // Check if it's the right time.
//      if (pTimeStepManager->getCurrentYear() == iYear) {
//        if (pTimeStepManager->getCurrentTimeStep() != iStep)
//          return;
//      } else
//        return;
//    }
//
//    // Variables
//    int         iSquareHeight   = -1;
//    int         iSquareWidth    = -1;
//
//    // Open Stream/File
//    openStream();
//
//    // Print Out
//    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
//    cout << PARAM_ROW << CONFIG_SEPERATOR_ESTIMATE_VALUES;
//    cout << PARAM_COLUMN << CONFIG_SEPERATOR_ESTIMATE_VALUES,
//    cout << PARAM_CATEGORY;
//    for(int i = pWorld->getMinAge(); i < pWorld->getMaxAge()+1; i++) {
//      cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << PARAM_AGE;
//      cout << CONFIG_ARRAY_START << i << CONFIG_ARRAY_END;
//    }
//    cout << "\n";
//
//    for (int i = 0; i < iWorldHeight; ++i) {
//      for (int j = 0; j < iWorldWidth; ++j) {
//        // Get Current Square
//        CWorld *pWorld2 = CWorld::Instance();
//        pBase = pWorld2->getBaseSquare(i, j);
//
//        // If not set, Set our SquareHeight/Width
//        if (iSquareHeight == -1) {
//          iSquareHeight = pBase->getHeight();
//          iSquareWidth  = pBase->getWidth();
//        }
//
//        if (!pBase->getEnabled())
//          continue;
//
//        // Loop Through
//        for (int k = 0; k < iSquareHeight; ++k) {
//          cout << i+1 << CONFIG_SEPERATOR_ESTIMATE_VALUES << j+1 << "," << pWorld->getCategoryNameForIndex(k);
//          for (int l = 0; l < iSquareWidth; ++l) {
//            cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << pBase->getValue(k, l);
//          }
//          cout << "\n";
//        }
//      }
//    }
//
//    cout << endl;
//
//    // Close our Stream
//    closeStream();
//
//  } catch (string Ex) {
//    Ex = "CWorldGridPrintState.execute(" + sLabel + ")->" + Ex;
//    throw Ex;
//  }
}

//**********************************************************************
// CWorldGridPrintState::~CWorldGridPrintState()
// Default De-Constructor
//**********************************************************************
CWorldGridPrintState::~CWorldGridPrintState() {
}
