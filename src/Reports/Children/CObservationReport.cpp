/*
 * CObservationReport.cpp
 *
 *  Created on: 26/03/2009
 *      Author: Admin
 */

#include "CObservationReport.h"

//**********************************************************************
// CObservationReport::CObservationReport()
// Constructor
//**********************************************************************
CObservationReport::CObservationReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;
}

//**********************************************************************
// void CObservationReport::execute()
// Execute our Print State
//**********************************************************************
void CObservationReport::execute() {
  // Check for correct state
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      return;

  this->start();

  // TODO: Add Observation Writing Stuff Cout
  cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
  cout << "report.type=observation\n";
  cout << "# Not Yet Implemented" << endl;
  cout << "*end\n" << endl;

  this->end();
}

//**********************************************************************
// CObservationReport::~CObservationReport()
// Destructor
//**********************************************************************
CObservationReport::~CObservationReport() {
}
