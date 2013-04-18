//============================================================================
// Name        : CSizeWeightReport.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSizeWeightReport.h"
#include "../../SizeWeight/CSizeWeightManager.h"
#include "../../SizeWeight/CSizeWeight.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CSizeWeightReport::CSizeWeightReport()
// Constructor
//**********************************************************************
CSizeWeightReport::CSizeWeightReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;
  pSizeWeight      = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHT);
  pParameterList->registerAllowed(PARAM_SIZES);

}

//**********************************************************************
// void CSizeWeightReport::validate()
// Validate our selectivity
//**********************************************************************
void CSizeWeightReport::validate() {
  try {

    sSizeWeight = pParameterList->getString(PARAM_SIZE_WEIGHT);
    // Get our list of sizes to evaluate
    pParameterList->fillVector(vSizeList, PARAM_SIZES);

    // Validate parent
    CFileReport::validate();

    // Local validation
    for (int i = 0; i < (int)vSizeList.size(); ++i ) {
      if(vSizeList[i] < 0)
        CError::errorLessThan(PARAM_SIZES, PARAM_ZERO);
    }

  } catch (string &Ex) {
    Ex = "CSizeWeightReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSizeWeightReport::build()
// Build our Report
//**********************************************************************
void CSizeWeightReport::build() {
  try {
    // Parent
    CFileReport::build();

    // Get our selectivity
    CSizeWeightManager *pManager = CSizeWeightManager::Instance();
    pSizeWeight = pManager->getSizeWeight(sSizeWeight);

  } catch (string &Ex) {
    Ex = "CSizeWeightReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSizeWeightReport::execute()
// Execute
//**********************************************************************
void CSizeWeightReport::execute() {
  try {

    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;

    this->start();

    // Output Header
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_SIZE_WEIGHT << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sSizeWeight << "\n";

    cout << PARAM_SIZES << CONFIG_RATIO_SEPARATOR << " ";
    for (int i = 0; i < ((int)vSizeList.size()-1); ++i) {
      cout << vSizeList[i] << CONFIG_SPACE_SEPERATOR;
    }
    cout << vSizeList[vSizeList.size()-1] << "\n";

    cout << PARAM_WEIGHTS << CONFIG_RATIO_SEPARATOR << " ";
    for (int i = 0; i < ((int)vSizeList.size()-1); ++i) {
      cout << pSizeWeight->getMeanWeight(vSizeList[i]) << CONFIG_SPACE_SEPERATOR;
    }
    cout << pSizeWeight->getMeanWeight(vSizeList[vSizeList.size()-1]) << "\n";
    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();

  } catch (string &Ex) {
    Ex = "CSizeWeightReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSizeWeightReport::~CSizeWeightReport()
// Destuctor
//**********************************************************************
CSizeWeightReport::~CSizeWeightReport() {
}
