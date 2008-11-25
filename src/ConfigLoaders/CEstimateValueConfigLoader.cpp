//============================================================================
// Name        : CEstimateValueConfigLoader.cpp
// Author      : S.Rasmussen
// Date        : 12/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CEstimateValueConfigLoader.h"

//**********************************************************************
// CEstimateValueConfigLoader::CEstimateValueConfigLoader()
// Constructor
//**********************************************************************
CEstimateValueConfigLoader::CEstimateValueConfigLoader(string Directory) {
  setDirectory(Directory);
  setFileName(CONFIG_FILE_ESTIMATE_VALUES);
  loadConfigFile();

  // Variables
  pEstimateManager = CEstimateManager::Instance();
}

//**********************************************************************
// void CEstimateValueConfigLoader::processConfigFile()
// Process our Configuration File
//**********************************************************************
void CEstimateValueConfigLoader::processConfigFile() {
  try {
    if (vConfigList.size() == 0)
      return; // File Was Empty

    // Read the first line, this contains the names of the variables.
    vConfigPtr = vConfigList.begin();
    populateParameters(CONFIG_SEPERATOR_ESTIMATE_VALUES); // , is separator

    // Get the Names of Our Estimates
    vector<string> vEstimateList;
    for (unsigned int i = 0; i < vParameterList.size(); ++i)
      vEstimateList.push_back(vParameterList[i]);

    // Loop Through Our Lines
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      // Populate Our Parameters
      populateParameters(CONFIG_SEPERATOR_ESTIMATE_VALUES);

      if (vParameterList.size() != vEstimateList.size())
        throw string(ERROR_EQUAL_VALUE_ESTIMATE);

      for (unsigned int i = 0; i < vEstimateList.size(); ++i) {
        pEstimateManager->addEstimateValue(vEstimateList[i], getDoubleValue(i, true));
      }

      vConfigPtr++;
    }
  } catch (string Ex) {
    Ex = "CEstimateValueConfigLoader.processConfigFile()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CEstimateValueConfigLoader::~CEstimateValueConfigLoader()
// Destructor
//**********************************************************************
CEstimateValueConfigLoader::~CEstimateValueConfigLoader() {

}
