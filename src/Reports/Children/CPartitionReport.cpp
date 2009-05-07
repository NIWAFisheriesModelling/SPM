//============================================================================
// Name        : CPartitionReport.cpp
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local header
#include "CPartitionReport.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CPartitionReport::CPartitionReport()
// Default Constructor
//**********************************************************************
CPartitionReport::CPartitionReport() {
  // Variables
  eExecutionState     = STATE_MODELLING;
  pTimeStepManager    = CTimeStepManager::Instance();

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_YEAR);
  pParameterList->registerAllowed(PARAM_TIME_STEP);
}

//**********************************************************************
// void CPartitionReport::validate()
// Validate this reporter
//**********************************************************************
void CPartitionReport::validate() {
  try {
    // Base
    CFileReport::validate();

    // Assign Variables
    iYear       = pParameterList->getInt(PARAM_YEAR);
    sYear       = pParameterList->getString(PARAM_YEAR); // TODO: Probably better to cast int to string when used (see execute function below)
    sTimeStep   = pParameterList->getString(PARAM_TIME_STEP);

    // ToDO: Validate Year is valid in our run

  } catch (string Ex) {
    Ex = "CPartitionReporter.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// void CPartitionReport::build()
// Build this reporter
//**********************************************************************
void CPartitionReport::build() {
  try {
    // Base
    CFileReport::build();

    // Populate TimeStepIndex
    iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);

  } catch (string Ex) {
    Ex = "CPartitionReporter.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPartitionReport::execute()
// Execute reporter
//**********************************************************************
void CPartitionReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;
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
    cout << PARAM_PARTITION << "." << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << sYear << "\n";
    cout << PARAM_PARTITION << "." << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << sTimeStep << "\n";

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
    Ex = "CPartitionReporter.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPartitionReport::~CPartitionReport()
// Destructor
//**********************************************************************
CPartitionReport::~CPartitionReport() {
}
