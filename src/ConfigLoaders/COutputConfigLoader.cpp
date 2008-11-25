//============================================================================
// Name        : COutputConfigLoader.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "COutputConfigLoader.h"
#include "../PrintStates/CWorldGridPrintState.h"
#include "../PrintStates/CObjectivePrintState.h"
#include "../PrintStates/CEstimatePrintState.h"
#include "../PrintStates/CEstimateValuePrintState.h"

//**********************************************************************
// COutputConfigLoader::COutputConfigLoader()
// Default Constructor
//**********************************************************************
COutputConfigLoader::COutputConfigLoader(string Directory) {
  setDirectory(Directory);
  setFileName(CONFIG_FILE_OUTPUT);
  loadConfigFile();

  pPrintStateManager  = CPrintStateManager::Instance();
}

//**********************************************************************
// void COutputConfigLoader::ProcessConfigFile()
// Process Config File
//**********************************************************************
void COutputConfigLoader::processConfigFile() {
  try {
    if (vConfigList.size() == 0)
      return; // File Was Empty

    // Loop Through Our Lines
    vConfigPtr = vConfigList.begin();
    while(vConfigPtr != vConfigList.end()) {
      if ((int)(*vConfigPtr).find(CONFIG_SECTION_SYMBOL) >= 0) {

        // Populate Our Parameters
        populateParameters();
        if (vParameterList.size() == 0)
          throw string(ERROR_EMPTY_PARAMETER);

        // Check What Section we are in
        if (vParameterList[0] == CONFIG_SECTION_PRINT_STATE)
          loadPrintState();
        else
          throw string(ERROR_UNKNOWN_SECTION + vParameterList[0]);

        continue; // We Incremented Elsewhere
      } else
        throw string(ERROR_UNKNOWN_SYNTAX + (*vConfigPtr));

      vConfigPtr++;
    }

  } catch (string Ex) {
    Ex = "COutputConfigLoader.ProcessConfigFile()->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// void COutputConfigLoader::loadPrintState()
// Load @print_state
//**********************************************************************
void COutputConfigLoader::loadPrintState() {
  try {
    // @print_state should have 1 parameter (Label)
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Inc
    vConfigPtr++;

    // Populate Parameters
    populateParameters();

    if (vParameterList.size() == 0)
      throw string(ERROR_EMPTY_PARAMETER);
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Must Be Type
    if (vParameterList[0] != PARAM_TYPE)
      throw string(ERROR_MISSING_SECTION_TYPE);

    if (vParameterList[1] == PARAM_INITIAL)
      loadPrintState_WorldGrid();
    else if (vParameterList[1] == PARAM_FINAL)
      loadPrintState_WorldGrid();
    else if (vParameterList[1] == PARAM_CURRENT)
      loadPrintState_WorldGrid();
    else if (vParameterList[1] == PARAM_OBJECTIVE)
      loadPrintState_Objective();
    else if (vParameterList[1] == PARAM_ESTIMATE)
      loadPrintState_Estimate();
    else if (vParameterList[1] == PARAM_ESTIMATE_VALUE)
      loadPrintState_EstimateValue();
    else
      throw string(ERROR_UNKNOWN_TYPE + vParameterList[1]);

  } catch (string Ex) {
    Ex = "COutputConfigLoader.loadPrintState()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void COutputConfigLoader::loadPrintState_WorldGrid()
//
//**********************************************************************
void COutputConfigLoader::loadPrintState_WorldGrid() {
  try {
    CWorldGridPrintState *pPrintState = new CWorldGridPrintState();
    pPrintState->setLabel(getLabel());

    // Populate Type
    populateParameters();

    if (vParameterList[1] == PARAM_INITIAL)
      pPrintState->setState(STATE_INITIALIZATION);
    else if (vParameterList[1] == PARAM_FINAL)
      pPrintState->setState(STATE_FINALIZATION);

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_YEAR))
          pPrintState->setYear(getIntValue(1));
        else if (checkLine(PARAM_TIME_STEP))
          pPrintState->setStep(getIntValue(1));
        else if (!loadBasePrintStateAttributes(pPrintState)) {
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pPrintStateManager->addPrintState(pPrintState);
  } catch (string Ex) {
    Ex = "COutputConfigLoader.loadPrintState_WorldGrid()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void COutputConfigLoader::loadPrintState_Objective()
// Load Objective Print State
//**********************************************************************
void COutputConfigLoader::loadPrintState_Objective() {
  try {
    CObjectivePrintState *pPrintState = new CObjectivePrintState();
    pPrintState->setLabel(getLabel());

    // Populate Type
    populateParameters();

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBasePrintStateAttributes(pPrintState)) {
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pPrintStateManager->addPrintState(pPrintState);
  } catch (string Ex) {
    Ex = "COutputConfigLoader.loadPrintState_Objective()" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void COutputConfigLoader::loadPrintState_Estimate()
// Load an Estimate Print State
//**********************************************************************
void COutputConfigLoader::loadPrintState_Estimate() {
  try {
    CEstimatePrintState *pPrintState = new CEstimatePrintState();
    pPrintState->setLabel(getLabel());

    // Populate Type
    populateParameters();

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBasePrintStateAttributes(pPrintState)) {
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pPrintStateManager->addPrintState(pPrintState);
  } catch (string Ex) {
    Ex = "COutputConfigLoader.loadPrintState_Estimate()" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void COutputConfigLoader::loadPrintState_EstimateValue()
// Load Estimate Value Print State
//**********************************************************************
void COutputConfigLoader::loadPrintState_EstimateValue() {
  try {
    CEstimateValuePrintState *pPrintState = new CEstimateValuePrintState();
    pPrintState->setLabel(getLabel());

    // Populate Type
    populateParameters();

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBasePrintStateAttributes(pPrintState)) {
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pPrintStateManager->addPrintState(pPrintState);
  } catch (string Ex) {
    Ex = "COutputConfigLoader.loadPrintState_EstimateValue()" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// bool COutputConfigLoader::loadBasePrintStateAttributes(CPrintState *PrintState)
// Load Base (Common) Print State Attributes
//**********************************************************************
bool COutputConfigLoader::loadBasePrintStateAttributes(CPrintState *PrintState) {
  try {
    if (checkLine(PARAM_FILE_NAME)) {
     string sFileName = "";
     for (int i = 1; i < (int)vParameterList.size(); ++i)
       sFileName += vParameterList[i] + " ";
      PrintState->setFileName(sFileName);
    } else if (checkLine(PARAM_OVERWRITE))
      PrintState->setOverwrite(getBoolValue(1));
    else
      return false;

  } catch (string Ex) {
    Ex = "COutputConfigLoader.loadBasePrintStateAttributes()->" + Ex;
    throw Ex;
  }

  return true;
}
//**********************************************************************
// COutputConfigLoader::~COutputConfigLoader()
// Default De-Constructor
//**********************************************************************
COutputConfigLoader::~COutputConfigLoader() {
  pPrintStateManager    = 0;
}
