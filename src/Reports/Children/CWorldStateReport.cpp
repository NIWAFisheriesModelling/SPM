//============================================================================
// Name        : CWorldStateReport.cpp
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local header
#include "CWorldStateReport.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CWorldStateReport::CWorldStateReport()
// Default Constructor
//**********************************************************************
CWorldStateReport::CWorldStateReport() {
  // Variables
  eExecutionState     = STATE_MODELLING;
  pTimeStepManager    = CTimeStepManager::Instance();

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_YEAR);
  pParameterList->registerAllowed(PARAM_TIME_STEP);
}

//**********************************************************************
// void CWorldStateReport::validate()
// Validate this reporter
//**********************************************************************
void CWorldStateReport::validate() {
  try {
    // Base
    CFileReport::validate();

    // Assign Variables
    iYear       = pParameterList->getInt(PARAM_YEAR);
    sTimeStep   = pParameterList->getString(PARAM_TIME_STEP);

  } catch (string Ex) {
    Ex = "CWorldStateReporter.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// void CWorldStateReport::build()
// Build this reporter
//**********************************************************************
void CWorldStateReport::build() {
  try {
    // Base
    CFileReport::build();

    // Populate TimeStepIndex
    iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);

  } catch (string Ex) {
    Ex = "CWorldStateReporter.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CWorldStateReport::execute()
// Execute reporter
//**********************************************************************
void CWorldStateReport::execute() {
  try {
    // Check
    if (iYear != pTimeStepManager->getCurrentYear())
      return;
    if (iTimeStep != pTimeStepManager->getCurrentTimeStep())
      return;

    this->start();

    // Variables
    int         iSquareHeight   = -1;
    int         iSquareWidth    = -1;

    // Print Out
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_ROW << CONFIG_SEPERATOR_ESTIMATE_VALUES;
    cout << PARAM_COLUMN << CONFIG_SEPERATOR_ESTIMATE_VALUES,
    cout << PARAM_CATEGORY;
    for(int i = pWorld->getMinAge(); i < pWorld->getMaxAge()+1; i++) {
      cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << PARAM_AGE;
      cout << CONFIG_ARRAY_START << i << CONFIG_ARRAY_END;
    }
    cout << "\n";

    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square
        pBaseSquare = pWorld->getBaseSquare(i, j);

        // If not set, Set our SquareHeight/Width
        if (iSquareHeight == -1) {
          iSquareHeight = pBaseSquare->getHeight();
          iSquareWidth  = pBaseSquare->getWidth();
        }

        if (!pBaseSquare->getEnabled())
          continue;

        // Loop Through
        for (int k = 0; k < iSquareHeight; ++k) {
          cout << i+1 << CONFIG_SEPERATOR_ESTIMATE_VALUES << j+1 << "," << pWorld->getCategoryNameForIndex(k);
          for (int l = 0; l < iSquareWidth; ++l) {
            cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << pBaseSquare->getValue(k, l);
          }
          cout << "\n";
        }
      }
    }

    cout << "*end\n" << endl;

    this->end();
  } catch (string Ex) {
    Ex = "CWorldStateReporter.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CWorldStateReport::~CWorldStateReport()
// Destructor
//**********************************************************************
CWorldStateReport::~CWorldStateReport() {
}
