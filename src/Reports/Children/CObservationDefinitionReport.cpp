//============================================================================
// Name        : CObservationDefinitionReport.cpp
// Author      : S.Rasmussen
// Date        : 13/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CObservationDefinitionReport.h"
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CConvertor.h"

//**********************************************************************
// CObservationDefinitionReport::CObservationDefinitionReport()
// Default Constructor
//**********************************************************************
CObservationDefinitionReport::CObservationDefinitionReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;

  // Register Allowed
  pParameterList->registerAllowed(PARAM_OBSERVATION);
}

//**********************************************************************
// void CObservationDefinitionReport::validate()
// Validate our Observation Report
//**********************************************************************
void CObservationDefinitionReport::validate() {
  try {
    // Base
    CFileReport::validate();

    // Get Params
    sObservation = pParameterList->getString(PARAM_OBSERVATION);

  } catch (string &Ex) {
    Ex = "CObservationDefinitionReport.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationDefinitionReport::execute()
// Execute our Print State
//**********************************************************************
void CObservationDefinitionReport::execute() {
  // Check for correct state
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      if (pRuntimeController->getRunMode() != RUN_MODE_SIMULATION)
        return;

  this->start();

  cout << "#" << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
  cout << "#" << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
  cout << "#" << PARAM_OBSERVATION << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pObservation->getLabel()  << "\n";

  CParameterList *pList = pObservation->getParameterList();

  // Get the parameters that have been defined.
  vector<string> vDefinedParameters;
  pList->fillDefinedParameterVector(vDefinedParameters);

  cout << "@observation" << " " << pList->getString(PARAM_LABEL) << "\n";

  // Loop through and print values
  vector<string> vValues;
  foreach(string Parameter, vDefinedParameters) {
    if ( (Parameter == PARAM_OBS) || (Parameter == PARAM_ERROR_VALUE) || (Parameter == PARAM_LABEL))
      continue;

    pList->fillVector(vValues, Parameter);

    cout << Parameter << " ";
    foreach(string Value, vValues) {
      cout << Value << " ";
    }
    cout << endl;
  }

  // Now, Print our Observations
  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  // Print OBS
  string sLastKey = "";
  foreach(SComparison *Comparison, vComparisons) {
    if (sLastKey != Comparison->sKey) {
      if (sLastKey != "")
        cout << "\n";
      cout << PARAM_OBS << " " << Comparison->sKey << " ";
      sLastKey = Comparison->sKey;
    }

    cout << boost::lexical_cast<string>(Comparison->dObservedValue) << " ";
  }

  // Print Error Values
  sLastKey = "";
  bool bWriteErrorValue = false;
  foreach(SComparison *Comparison, vComparisons) {
    if (sLastKey != Comparison->sKey) {
      cout << "\n" << PARAM_ERROR_VALUE << " " << Comparison->sKey << " ";
      sLastKey = Comparison->sKey;
      bWriteErrorValue = true;
    }

    if (bWriteErrorValue)
      cout << boost::lexical_cast<string>(Comparison->dErrorValue) << " ";

    if (pList->getString(PARAM_TYPE) == PARAM_PROPORTIONS_AT_AGE)
      bWriteErrorValue = false;
  }

  cout << "\n";
  cout << "#end\n" << endl;

  this->end();
}

//**********************************************************************
// void CObservationDefinitionReport::build()
// Build our Observation Report
//**********************************************************************
void CObservationDefinitionReport::build() {
  try {
    // Base
    CFileReport::build();

    // Get our Obs
    pObservation = CObservationManager::Instance()->getObservation(sObservation);

  } catch (string &Ex) {
    Ex = "CObservationDefinitionReport.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CObservationDefinitionReport::~CObservationDefinitionReport()
// Destructor
//**********************************************************************
CObservationDefinitionReport::~CObservationDefinitionReport() {
}
