//============================================================================
// Name        : CObservationReport.cpp
// Author      : S.Rasmussen
// Date        : 8/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CObservationReport.h"
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"
#include "../../Observations/Children/CProportionsAtAgeObservation.h"
#include "../../Observations/Children/CProportionsByCategoryObservation.h"
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

    // Get Params
    sObservation = pParameterList->getString(PARAM_OBSERVATION);

    // Validate parent
    CFileReport::validate();

    // Local validation

  } catch (string &Ex) {
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

  } catch (string &Ex) {
    Ex = "CObservationReport.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationReport::execute()
// Execute our Print State
//**********************************************************************
void CObservationReport::execute() {

  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      //if (pRuntimeController->getRunMode() != RUN_MODE_SIMULATION)
        return;

    CProportionsAtAgeObservation *pProportionsAtAge = dynamic_cast<CProportionsAtAgeObservation*>(pObservation);
    CProportionsByCategoryObservation *pProportionsByCategory = dynamic_cast<CProportionsByCategoryObservation*>(pObservation);

    this->start();

    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_OBSERVATION << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pObservation->getLabel()  << "\n";

    cout << PARAM_OBSERVATION << "." << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pObservation->getYear()  << "\n";
    cout << PARAM_OBSERVATION << "." << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << pObservation->getTimeStepString()  << "\n";

    vector<SComparison*> vComparisons;
    pObservation->fillComparisons(vComparisons);

    if (pProportionsAtAge != 0) {
      cout << PARAM_OBSERVATION << "." << PARAM_MIN_AGE << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtAge->getMinAge()  << "\n";
      cout << PARAM_OBSERVATION << "." << PARAM_MAX_AGE << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtAge->getMaxAge()  << "\n";
      cout << PARAM_OBSERVATION << "." << PARAM_AGE_PLUS_GROUP << CONFIG_RATIO_SEPARATOR << " " << string(pProportionsAtAge->getAgePlusGroup()?CONFIG_TRUE:CONFIG_FALSE) << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "category" << CONFIG_SPACE_SEPARATOR
           << "age"  << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR
           << "expected" << CONFIG_SPACE_SEPARATOR << "residual" << CONFIG_SPACE_SEPARATOR
           << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR
           << "totalerror" << CONFIG_SPACE_SEPARATOR << "score\n";
    } else if (pProportionsByCategory != 0) {
      cout << PARAM_OBSERVATION << "." << PARAM_MIN_AGE << CONFIG_RATIO_SEPARATOR << " " << pProportionsByCategory->getMinAge()  << "\n";
      cout << PARAM_OBSERVATION << "." << PARAM_MAX_AGE << CONFIG_RATIO_SEPARATOR << " " << pProportionsByCategory->getMaxAge()  << "\n";
      cout << PARAM_OBSERVATION << "." << PARAM_AGE_PLUS_GROUP << CONFIG_RATIO_SEPARATOR << " " << string(pProportionsByCategory->getAgePlusGroup()?CONFIG_TRUE:CONFIG_FALSE) << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "age" << CONFIG_SPACE_SEPARATOR
           << "observed" << CONFIG_SPACE_SEPARATOR << "expected" << CONFIG_SPACE_SEPARATOR
           << "residual" << CONFIG_SPACE_SEPARATOR << "errorvalue" << CONFIG_SPACE_SEPARATOR
           << "processerror" << CONFIG_SPACE_SEPARATOR << "totalerror" << CONFIG_SPACE_SEPARATOR
           << "score\n";
    } else {
      cout << "area" << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR
           << "expected" << CONFIG_SPACE_SEPARATOR << "residual" << CONFIG_SPACE_SEPARATOR
           << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR
           << "totalerror" << CONFIG_SPACE_SEPARATOR << "score\n";
    }

    foreach(SComparison *Comparison, vComparisons) {
      double dResidual = Comparison->dObservedValue - Comparison->dExpectedValue;
      cout << Comparison->sKey << CONFIG_SPACE_SEPARATOR;
      if (pProportionsAtAge != 0) {
        cout << Comparison->sGroup << CONFIG_SPACE_SEPARATOR;
        cout << Comparison->iAge << CONFIG_SPACE_SEPARATOR;
      } else if (pProportionsByCategory != 0) {
        cout << Comparison->iAge << CONFIG_SPACE_SEPARATOR;
      }
      cout << Comparison->dObservedValue << CONFIG_SPACE_SEPARATOR
           << Comparison->dExpectedValue << CONFIG_SPACE_SEPARATOR
           << dResidual << CONFIG_SPACE_SEPARATOR
           << Comparison->dErrorValue << CONFIG_SPACE_SEPARATOR
           << Comparison->dProcessError << CONFIG_SPACE_SEPARATOR
           << Comparison->dTotalError << CONFIG_SPACE_SEPARATOR
           << Comparison->dScore << "\n";
    }

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();

  } catch (string &Ex) {
    Ex = "CObservationReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CObservationReport::~CObservationReport()
// Destructor
//**********************************************************************
CObservationReport::~CObservationReport() {
}
