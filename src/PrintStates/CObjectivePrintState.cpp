//============================================================================
// Name        : CObjectivePrintState.cpp
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
#include "CObjectivePrintState.h"
#include "../ObjectiveFunction/CObjectiveFunction.h"

//**********************************************************************
// CObjectivePrintState::CObjectivePrintState()
// Default Constructor
//**********************************************************************
CObjectivePrintState::CObjectivePrintState() {
  // Set The State
  eState = STATE_FINALIZATION;
}

//**********************************************************************
// void CObjectivePrintState::execute()
// Execute
//**********************************************************************
void CObjectivePrintState::execute() {
  try {
    // We don't call this during run mode.
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;

    // Open stream/file
    openStream();

    // Variables
    CObjectiveFunction  *pObjectiveFunction   = CObjectiveFunction::Instance();

    // Print
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    int iCount = pObjectiveFunction->getScoreListCount();
    for (int i = 0; i < iCount; ++i) {
      SScore *pScore = pObjectiveFunction->getScore(i);
      cout << pScore->Label << ": " << pScore->Score << "\n";
    }

    cout << PARAM_TOTAL_SCORE << pObjectiveFunction->getScore() << endl;

    // Close Stream/File
    closeStream();

  } catch (string Ex) {
    Ex = "CObjectivePrintState.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CObjectivePrintState::~CObjectivePrintState()
// Default De-Constructor
//**********************************************************************
CObjectivePrintState::~CObjectivePrintState() {
}
