//============================================================================
// Name        : CAgeSizeReport.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAgeSizeReport.h"
#include "../../AgeSize/CAgeSizeManager.h"
#include "../../AgeSize/CAgeSize.h"

//**********************************************************************
// CAgeSizeReport::CAgeSizeReport()
// Constructor
//**********************************************************************
CAgeSizeReport::CAgeSizeReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;
  pAgeSize      = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_AGE_SIZE);
  pParameterList->registerAllowed(PARAM_AGES);

}

//**********************************************************************
// void CAgeSizeReport::validate()
// Validate our selectivity
//**********************************************************************
void CAgeSizeReport::validate() {
  try {
    // Parent
    CFileReport::validate();

     sAgeSize = pParameterList->getString(PARAM_AGE_SIZE);

    // Get our list of sizes to evaluate
    pParameterList->fillVector(vAgeList, PARAM_AGES);

  } catch (string ex) {
    ex = "CAgeSizeReport.validate(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
// void CAgeSizeReport::build()
// Build our Report
//**********************************************************************
void CAgeSizeReport::build() {
  try {
    // Parent
    CFileReport::build();

    // Get our selectivity
    CAgeSizeManager *pManager = CAgeSizeManager::Instance();
    pAgeSize = pManager->getAgeSize(sAgeSize);

  } catch (string ex) {
    ex = "CAgeSizeReport.build(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
// void CAgeSizeReport::execute()
// Execute
//**********************************************************************
void CAgeSizeReport::execute() {
  // Check for correct state
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    return;

  this->start();

  // Output Header
  cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
  cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
  cout << PARAM_AGE_SIZE << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sAgeSize << "\n";

  cout << PARAM_AGES << CONFIG_RATIO_SEPARATOR;
  for (int i = 0; i < ((int)vAgeList.size()-1); ++i) {
    cout << " " << vAgeList[i] << CONFIG_SEPERATOR_ESTIMATE_VALUES;
  }
  cout << " " << vAgeList[vAgeList.size()-1] << "\n";

  cout << PARAM_SIZES << CONFIG_RATIO_SEPARATOR;
  for (int i = 0; i < ((int)vAgeList.size()-1); ++i) {
    cout << " " << pAgeSize->getMeanSize(vAgeList[i]) << CONFIG_SEPERATOR_ESTIMATE_VALUES;
  }
  cout << " " << pAgeSize->getMeanSize(vAgeList[vAgeList.size()-1]) << "\n";
  cout << "*end\n" << endl;


  this->end();
}

//**********************************************************************
// CAgeSizeReport::~CAgeSizeReport()
// Destuctor
//**********************************************************************
CAgeSizeReport::~CAgeSizeReport() {
}
