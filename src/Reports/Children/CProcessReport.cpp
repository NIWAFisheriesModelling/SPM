//============================================================================
// Name        : CProcessReport.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CProcessReport.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Processes/CProcessManager.h"
#include "../../Processes/CProcess.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Selectivities/CSelectivity.h"

//**********************************************************************
// CProcessReport::CProcessReport()
// Constructor
//**********************************************************************
CProcessReport::CProcessReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;

  // Reg
  pParameterList->registerAllowed(PARAM_PROCESS);
}

//**********************************************************************
// void CProcessReport::validate()
// Validate our Parameter List
//**********************************************************************
void CProcessReport::validate() {
  try {
    // Base
    CFileReport::validate();

    // Get var
    sParameter = pParameterList->getString(PARAM_PROCESS);

  } catch (string &Ex) {
    Ex = "CProcessReport.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
//
//
//**********************************************************************
void CProcessReport::build() {
  try {
    // Base
    CFileReport::build();

    // Now grab our variable
    pTarget = CProcessManager::Instance()->getProcess(sParameter);

  } catch (string &Ex) {
    Ex = "CProcessReport.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProcessReport::execute()
// Execute our Report
//**********************************************************************
void CProcessReport::execute() {

  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();

    CParameterList *pList = pTarget->getParameterList();

    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_PROCESS << CONFIG_RATIO_SEPARATOR << " " << sParameter << "\n";

    vector<string> vDefinedParameters;
    pList->fillDefinedParameterVector(vDefinedParameters);

    vector<string> vValues;
    foreach(string Parameter, vDefinedParameters) {
      pList->fillVector(vValues, Parameter);

      cout << Parameter << " ";
      foreach(string Value, vValues) {
        cout << Value << " ";
      }
      cout << endl;
    }

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();

  } catch (string &Ex) {
    Ex = "CProcessReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// CProcessReport::~CProcessReport()
// Destructor
//**********************************************************************
CProcessReport::~CProcessReport() {
}
