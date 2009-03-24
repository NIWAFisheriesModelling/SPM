//============================================================================
// Name        : CObjectiveFunctionReporter.cpp
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CObjectiveFunctionReporter.h"
#include "../../ObjectiveFunction/CObjectiveFunction.h"

//**********************************************************************
// CObjectiveFunctionReporter::CObjectiveFunctionReporter()
// Default Constructor
//**********************************************************************
CObjectiveFunctionReporter::CObjectiveFunctionReporter() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;
}

//**********************************************************************
// void CObjectiveFunctionReporter::execute()
// Execute
//**********************************************************************
void CObjectiveFunctionReporter::execute() {
  // Check for correct state
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      return;

  this->start();

  // Variables
  CObjectiveFunction  *pObjectiveFunction   = CObjectiveFunction::Instance();

  // Print
  cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
  int iCount = pObjectiveFunction->getScoreListCount();
  for (int i = 0; i < iCount; ++i) {
    SScore *pScore = pObjectiveFunction->getScore(i);
    cout << pScore->Label << ": " << pScore->Score << "\n";
  }

  cout << PARAM_TOTAL_SCORE << ": " << pObjectiveFunction->getScore() << endl;
  cout << endl;
  this->end();
}

//**********************************************************************
// CObjectiveFunctionReporter::~CObjectiveFunctionReporter()
// Destructor
//**********************************************************************
CObjectiveFunctionReporter::~CObjectiveFunctionReporter() {
}
