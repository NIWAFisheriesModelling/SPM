//============================================================================
// Name        : CObservationReport.cpp
// Author      : S.Rasmussen
// Date        : 8/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CObservationReport.h"
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CObservationReport::CObservationReport()
// Constructor
//**********************************************************************
CObservationReport::CObservationReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;

  // Register Allowed
  pParameterList->registerAllowed(PARAM_OBSERVATION);
}

//**********************************************************************
// void CObservationReport::validate()
// Validate our Observation Report
//**********************************************************************
void CObservationReport::validate() {
  try {
    // Base
    CFileReport::validate();

    // Get Params
    sObservation = pParameterList->getString(PARAM_OBSERVATION);

  } catch (string Ex) {
    Ex = "CObservationReport.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationReport::build()
// Build our Observation Report
//**********************************************************************
void CObservationReport::build() {
  try {
    // Base
    CFileReport::build();

    // Get our Obs
    pObservation = CObservationManager::Instance()->getObservation(sObservation);

  } catch (string Ex) {
    Ex = "CObservationReport.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationReport::execute()
// Execute our Print State
//**********************************************************************
void CObservationReport::execute() {
  // Check for correct state
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      if (pRuntimeController->getRunMode() != RUN_MODE_SIMULATION)
        return;

  this->start();

  cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
  cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
  cout << PARAM_OBSERVATION << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pObservation->getLabel()  << "\n";

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  cout << "area,observed,expected,residual,errorvalue,score\n";

  foreach(SComparison *Comparison, vComparisons) {
    double dResidual = Comparison->dObservedValue - Comparison->dExpectedValue;
    cout << Comparison->sKey << CONFIG_SEPERATOR_ESTIMATE_VALUES
         << Comparison->dObservedValue << CONFIG_SEPERATOR_ESTIMATE_VALUES
         << Comparison->dExpectedValue << CONFIG_SEPERATOR_ESTIMATE_VALUES
         << dResidual << CONFIG_SEPERATOR_ESTIMATE_VALUES
         << Comparison->dErrorValue << CONFIG_SEPERATOR_ESTIMATE_VALUES
         << Comparison->dScore << "\n";
  }

  cout << CONFIG_END_REPORT << "\n" << endl;

  this->end();
}

//**********************************************************************
// CObservationReport::~CObservationReport()
// Destructor
//**********************************************************************
CObservationReport::~CObservationReport() {
}
