//============================================================================
// Name        : CParamParser.cpp
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local headers
#include "CParamParser.h"
#include "../Processes/CProcessManager.h"
#include "../Processes/CProcess.h"
#include "../PreferenceFunctions/CPreferenceFunctionManager.h"
#include "../PreferenceFunctions/CPreferenceFunction.h"
#include "../Selectivities/CSelectivityManager.h"
#include "../Selectivities/CSelectivity.h"
#include "../Catchabilities/CCatchabilityManager.h"
#include "../Catchabilities/CCatchability.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CParamParser::CParamParser()
// Default Constructor
//**********************************************************************
CParamParser::CParamParser() {
  // Vars
  sCommand    = "";
  pRet        = 0;
}

//**********************************************************************
// double* CParamParser::parseCommand(string Command)
// Parse our String And Return the Resulting Pointer
//**********************************************************************
double* CParamParser::parseCommand(string Command) {
  try {
    // Set Local Cmd
    sCommand = UpperToLower(Command);

    // Parse
    parseAbsoluteCommand();

    if (pRet == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    return pRet;

  } catch (string Ex) {
    Ex = "CParamParser.parseCommand(" + sCommand + ")->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CParamParser::parseAbsoluteCommand()
// Absolute Command: type[label].variable
//**********************************************************************
void CParamParser::parseAbsoluteCommand() {
  try {
    // Variables
    int             iIndex            = -1;
    int             iIndex2           = -1;
    string          sType             = "";
    string          sLabel            = "";
    string          sVariable         = "";


    // Find the . between the label and variable
    iIndex  = (int)sCommand.find_first_of(CONFIG_ARRAY_START);
    iIndex2 = (int)sCommand.find_first_of(CONFIG_ARRAY_END);
    if (iIndex == 0)
      throw string(ERROR_FORMAT_PARAMETER);
    if (iIndex == -1)
      CError::errorMissing(CONFIG_ARRAY_START);
    if (iIndex2 == -1)
      CError::errorMissing(CONFIG_ARRAY_END);

    sType       = sCommand.substr(0, iIndex);
    iIndex++; // move past "["
    sLabel      = sCommand.substr(iIndex, (iIndex2-iIndex));
    iIndex2 += 2; // Move past "]."
    sVariable   = sCommand.substr( iIndex2, (sCommand.length() - iIndex2) );

    // Processes
    if (sType == PARAM_PROCESS) {
      CProcessManager *pProcessManager  = CProcessManager::Instance();
      CProcess        *pProcess         = pProcessManager->getProcess(sLabel);

      pRet = pProcess->getEstimableVariable(sVariable);
      return;
    }

    // Directed Process
    if (sType == PARAM_PREFERENCE_FUNCTION) {
      CPreferenceFunctionManager *pDirectedProcessManager = CPreferenceFunctionManager::Instance();
      CPreferenceFunction *pProcess = pDirectedProcessManager->getProcess(sLabel);

      pRet = pProcess->getEstimableVariable(sVariable);
      return;
    }

    // Selectivity
    if (sType == PARAM_SELECTIVITY) {
      CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
      CSelectivity *pSelectivity = pSelectivityManager->getSelectivity(sLabel);

      pRet = pSelectivity->getEstimableVariable(sVariable);
      return;
    }

    if (sType == PARAM_CATCHABILITY) {
      CCatchabilityManager *pQManager = CCatchabilityManager::Instance();
      CCatchability *pQ = pQManager->getCatchability(sLabel);

      pRet = pQ->getEstimableVariable(sVariable);
      return;
    }
    throw string(ERROR_INVALID_FORMAT + sCommand);

  } catch (string Ex) {
    Ex = "CParamParser.parseAbsoluteCommand()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// string CParamParser::UpperToLower(string Input)
// Convert String From Uppercase To Lowercase
//**********************************************************************
string CParamParser::UpperToLower(string Input) {

  for (int i=0;i< (int)strlen(Input.c_str());i++)
     if (Input[i] >= 0x41 && Input[i] <= 0x5A)
      Input[i] = Input[i] + 0x20;

  return Input;
}

//**********************************************************************
// CParamParser::~CParamParser()
// Default De-Constructor
//**********************************************************************
CParamParser::~CParamParser() {
}
