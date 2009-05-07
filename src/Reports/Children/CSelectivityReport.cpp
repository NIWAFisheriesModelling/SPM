//============================================================================
// Name        : CSelectivityReport.cpp
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSelectivityReport.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Selectivities/CSelectivity.h"

//**********************************************************************
// CSelectivityReport::CSelectivityReport()
// Constructor
//**********************************************************************
CSelectivityReport::CSelectivityReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;
  pSelectivity      = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_SELECTIVITY);
}

//**********************************************************************
// void CSelectivityReport::validate()
// Validate our selectivity
//**********************************************************************
void CSelectivityReport::validate() {
  try {
    // Parent
    CFileReport::validate();

    sSelectivity = pParameterList->getString(PARAM_SELECTIVITY);

  } catch (string ex) {
    ex = "CSelectivityReport.validate(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
// void CSelectivityReport::build()
// Build our Report
//**********************************************************************
void CSelectivityReport::build() {
  try {
    // Parent
    CFileReport::build();

    // Get our selectivity
    CSelectivityManager *pManager = CSelectivityManager::Instance();
    pSelectivity = pManager->getSelectivity(sSelectivity);

  } catch (string ex) {
    ex = "CSelectivityReport.build(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
// void CSelectivityReport::execute()
// Execute
//**********************************************************************
void CSelectivityReport::execute() {
  // Check for correct state
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      return;

  this->start();

  // Work our how many viable ages we have.
  int iSpread = (pWorld->getMaxAge() - pWorld->getMinAge()) + 1;
  int iMinAge = pWorld->getMinAge();

  // Output Header
  cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
  cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
  cout << PARAM_SELECTIVITY << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sSelectivity << "\n";

  cout << PARAM_AGES << CONFIG_RATIO_SEPARATOR << " " << iMinAge;
  for (int i = 1; i < iSpread; ++i)
    cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << " " << (i + iMinAge);
  cout << "\n";

  cout << "values" << CONFIG_RATIO_SEPARATOR << " ";
  cout << pSelectivity->getResult(0);
  for (int i = 1; i < iSpread; ++i)
    cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << " " << pSelectivity->getResult(i);
  cout << "\n";
  cout << "*end\n" << endl;

  this->end();
}

//**********************************************************************
// CSelectivityReport::~CSelectivityReport()
// Destuctor
//**********************************************************************
CSelectivityReport::~CSelectivityReport() {
}
