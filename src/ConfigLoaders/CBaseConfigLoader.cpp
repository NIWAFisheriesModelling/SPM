//============================================================================
// Name        : CBaseConfigLoader.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Global Headers
#include <fstream>
#include <string>

// Local Headers
#include "CBaseConfigLoader.h"

// Using
using std::ifstream;

//**********************************************************************
// CBaseConfigLoader::CBaseConfigLoader()
// Default Constructor
//**********************************************************************
CBaseConfigLoader::CBaseConfigLoader() {
  // Vars
  pWorld                  = CWorld::Instance();
  pRuntimeController      = CRuntimeController::Instance();
  pConfig                 = CConfiguration::Instance();
  pLayerManager           = CLayerManager::Instance();
  sFileName               = "";
  vConfigList.clear();
  vParameterList.clear();
}

//**********************************************************************
// void CBaseConfigLoader::loadConfigFile()
// Load The Config File Into Our Vector
//**********************************************************************
void CBaseConfigLoader::loadConfigFile() {
  try {
    loadFileLines(sDirectory + (sDirectory==""?"":"/") + sFileName.c_str());

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.loadConfigFile()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBaseConfigLoader::loadFileLines(string FileName)
// Load File Lines
//**********************************************************************
void CBaseConfigLoader::loadFileLines(string FileName) {
  try {
    if (sFileName == "")
      throw string(ERROR_INVALID_FILE_NAME);

    ifstream fConfig(FileName.c_str());
    if (!fConfig)
     throw string(ERROR_OPEN_FILE + FileName);

    string sLine = "";
    bool   bInMultiLineComment = false;

    while (getline(fConfig, sLine)) {
      if (sLine.length() == 0)
        continue;

      // Var
      int iIndex = -1;

      // In ML Comment?
      if (bInMultiLineComment) {
        // Check For }
        iIndex = (int)sLine.find_first_of(CONFIG_MULTI_COMMENT_END);
        if (iIndex >= 0) {
         bInMultiLineComment = false; // End Comment Run
         sLine = sLine.substr(iIndex+1, sLine.length()-iIndex); // Remove upto }
        } else
          continue; // Get Next Line and ignore this one
      }

      if (sLine.length() == 0)
        continue;

      // Remove Any # Single Line Comments
      iIndex = (int)sLine.find_first_of(CONFIG_SINGLE_COMMENT);
      if (iIndex >= 0)
        sLine = sLine.substr(0, iIndex);

      // Remove Any { } Multiline Comments
      iIndex = (int)sLine.find_first_of(CONFIG_MULTI_COMMENT_START);
      if (iIndex >= 0) {
        bInMultiLineComment = true;
        sLine = sLine.substr(0, iIndex);
      }

      // Replace \t (Tabs) with Spaces
      iIndex = (int)sLine.find_first_of("\t");
      while (iIndex != -1) {
        sLine.replace(iIndex, 1, " ");
        iIndex = (int)sLine.find_first_of("\t");
      }

      // ToDo: Remove the need for quotes
      if (sLine.substr(0, 8) == CONFIG_INCLUDE) {
        // Find First "
        iIndex = (int)sLine.find_first_of("\"");
        if (iIndex == -1)
          throw string("include_file value should be surrounded by quotes");
        // get line from First " (+1) onwards
        string sIncludeFile = sLine.substr(iIndex+1, sLine.length()-iIndex);

        // Remove last "
        iIndex = (int)sIncludeFile.find_first_of("\"");
        if (iIndex == -1)
          throw string("include_file missing closing quote");
        sIncludeFile = sIncludeFile.substr(0, iIndex);

        // Check if it's absolute or relative
        if ( (sIncludeFile.substr(0, 1) == "/") || (sIncludeFile.substr(1, 1) == ":") )
          loadFileLines(sIncludeFile); // Absolute
        else
          loadFileLines(sDirectory + (sDirectory==""?"":"//") + sIncludeFile); // Relative

        // Blank line so it's not added
        sLine = "";
      }

      if (sLine.length() > 0)
        vConfigList.push_back(sLine);
    }
    fConfig.close();
  } catch (string Ex) {
    Ex = "CBaseConfigLoader.loadFileLines(" + FileName +")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// bool CConfigLoader::checkLine(string Match, int MinParams, int MaxParam)
// Check The The Line (Param Check not Attribute Inclusive)
//**********************************************************************
bool CBaseConfigLoader::checkLine(string Match, int MinParams, int MaxParams) {
  try {
    // Vars
    int     i1CardIndex  = Match.find_first_of(CONFIG_WILDCARD_SINGLE);
    int     iNCardIndex  = Match.find_first_of(CONFIG_WILDCARD_MULTIPLE);
    string  sParam       = (string)vParameterList[0];

    /* ? Wildcard
     * This one can be used to simulate 1 character
     * you can add more than length of the string just to be safe
     */
    if (i1CardIndex >= 0) {
      // Remove The ?'s From Both Strings
      while (i1CardIndex >= 0) {
        Match = Match.erase(i1CardIndex, 1);
        if (i1CardIndex < (int)sParam.length())
          sParam = sParam.erase(i1CardIndex, 1);

        i1CardIndex  = Match.find_first_of(CONFIG_WILDCARD_SINGLE);
      }
    }

    /*
     * * Wildcard
     * This allows for N-number of chars to be removed from that char
     * forward
     */
    if (iNCardIndex >= 0) {
      Match = Match.erase(iNCardIndex, (Match.length()-iNCardIndex+1));
      if (iNCardIndex <= (int)sParam.length())
        sParam = sParam.erase(iNCardIndex, (sParam.length()-iNCardIndex+1));
    }

    // Check For Match Now
    if (sParam == Match) {
      if (MinParams >= 0)
        if ((int)vParameterList.size() < (MinParams+1))
          throw string(ERROR_QTY_LESS_PARAMETERS + Match);

      if (MaxParams >= 0)
        if ((int)vParameterList.size() > (MaxParams+1))
          throw string(ERROR_QTY_MORE_PARAMETERS + Match);

      return true;
    }
  } catch (string Ex) {
    Ex = "CBaseConfigLoader.checkLine()->" + Ex;
    throw Ex;
  }

  return false;
}

//**********************************************************************
// string CBaseConfigLoader::getWildCardMatch(string Match)
// Return The string that is covered by our Wildcard Chars
//**********************************************************************
string CBaseConfigLoader::getWildCardMatch(string Match) {
  try {
    // Vars
    int     i1CardIndex  = Match.find_first_of("?");
    int     iNCardIndex  = Match.find_first_of("*");
    string  sParam       = vParameterList[0];

    if ( (i1CardIndex >= 0) && (iNCardIndex >= 0))
      throw string(ERROR_INVALID_WILDCARDS);

    /* ? Wildcard
     * This one can be used to simulate 1 character
     * you can add more than length of the string just to be safe
     */
    if (i1CardIndex >= 0) {
      // Remove no ?'s From Both Strings
      i1CardIndex = Match.find_last_not_of("?");
      while (i1CardIndex >= 0) {
        Match.erase(i1CardIndex, 1);
        if (i1CardIndex < (int)sParam.length())
          sParam.erase(i1CardIndex, 1);

        i1CardIndex  = Match.find_last_not_of("?");
      }
    }

    /*
     * * Wildcard
     * This allows for N-number of chars to be removed from that char
     * forward
     */
    if (iNCardIndex >= 0) {
      if (iNCardIndex < (int)sParam.length())
        sParam = sParam.erase(0, iNCardIndex);
      else
        sParam = "";

      Match = Match.erase(0, iNCardIndex);
    }

    return sParam;

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.getWildCardMatch()->" + Ex;
    throw Ex;
  }

  return "";
}

//**********************************************************************
// double CBaseConfigLoader::getDoubleValue(int ParameterNumber, bool AllowZero)
// Try and Return Double Value
//**********************************************************************
double CBaseConfigLoader::getDoubleValue(int ParameterNumber, bool AllowZero) {
  try {
    double dRet = atof(vParameterList[ParameterNumber].c_str());
    if ( (dRet == 0) && (!AllowZero))
      throw string(ERROR_INVALID_VALUE_NEGATIVE + vParameterList[ParameterNumber]);

    return dRet;

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.getDoubleValue( " + vParameterList[0] + ")->" + Ex;
    throw Ex;
  }

  return 0;
}
//**********************************************************************
// int CConfigLoader::getIntValue(int ParameterNumber, bool AllowZero)
// Try And Return An Int of Our Value
//**********************************************************************
int CBaseConfigLoader::getIntValue(int ParameterNumber, bool AllowZero) {
  try {
    int iRet = atoi(vParameterList[ParameterNumber].c_str());
    if ( (iRet == 0) && (!AllowZero) )
      throw string(ERROR_INVALID_NUMERIC + vParameterList[ParameterNumber]);

    return iRet;

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.getIntValue(" + vParameterList[0] + ")->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// bool CConfigLoader::getBoolValue(int ParameterNumber)
// Convert String Into Bool
//**********************************************************************
bool CBaseConfigLoader::getBoolValue(int ParameterNumber) {
  try {
    string Value = vParameterList[ParameterNumber];

    if ((Value == CONFIG_TRUE) || (Value == CONFIG_TRUE_SHORT))
      return true;
    if ((Value == CONFIG_FALSE) || (Value == CONFIG_FALSE_SHORT))
      return false;

    throw string(ERROR_INVALID_BOOL + vParameterList[ParameterNumber]);

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.getBoolValue(" + vParameterList[0] + ")->" + Ex;
    throw Ex;
  }

  return false;
}
//**********************************************************************
// void CConfigLoader::populateParameters()
//
//**********************************************************************
void CBaseConfigLoader::populateParameters(string find) {
  try {
    // Clear Our Old Parameters
    vParameterList.clear();

    // Variables
    string  sLine         = upperToLower((*vConfigPtr));
    int     iFirstSpace   = -1;

    iFirstSpace = sLine.find_first_of(find);
    if (iFirstSpace == -1) {
      vParameterList.push_back( sLine );
      return;
    }

    while (iFirstSpace >= 0) {
      // Check Difference Between Our Spaces
      if (iFirstSpace > 0)
        vParameterList.push_back( sLine.substr(0, iFirstSpace));

      sLine = sLine.erase(0, iFirstSpace+1);
      iFirstSpace = sLine.find_first_of(find, 0);
    }
    // If anything is remaining, add it to the list
    if (sLine.length() > 0)
      vParameterList.push_back(sLine);

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.populateParameters()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// string CBaseConfigLoader::upperToLower(string Input)
// Convert String From Uppercase To Lowercase
//**********************************************************************
string CBaseConfigLoader::upperToLower(string Input) {
  try {
    for (int i=0;i< (int)strlen(Input.c_str());i++)
       if (Input[i] >= 0x41 && Input[i] <= 0x5A)
        Input[i] = Input[i] + 0x20;

    return Input;

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.upperToLower()->" + Ex;
    throw Ex;
  }

  return "";
}

//**********************************************************************
// string CBaseConfigLoader::getLabel()
//
//**********************************************************************
string CBaseConfigLoader::getLabel() {
  try {
    // Move Back (We Will be on Type Line)
    if ( (vParameterList[0] != PARAM_TYPE) && (vParameterList[0] != PARAM_METHOD) ) {
      if (vParameterList[0].substr(0, 1) != CONFIG_SECTION_SYMBOL)
        throw string(ERROR_INVALID_GETLABEL_LINE);
    } else
      vConfigPtr--;

    populateParameters();

    if (vParameterList.size() < 2)
      throw string(ERROR_QTY_LESS_PARAMETERS);
    if (vParameterList.size() > 2)
      throw string(ERROR_QTY_MORE_PARAMETERS);

    string sRet       = vParameterList[1];
    vConfigPtr++; // Move To type/method line
    return sRet;

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.getLabel(" + vParameterList[0] + ")->" + Ex;
    throw Ex;
  }
  return "";
}

//**********************************************************************
// bool CBaseConfigLoader::newSection()
// Check For New Section
//**********************************************************************
bool CBaseConfigLoader::newSection() {
  try {
    if (vParameterList[0].substr(0, 1) == CONFIG_SECTION_SYMBOL)
      return true;

  } catch (string Ex) {
    Ex = "CBaseConfigLoader.newSection()->" + Ex;
    throw Ex;
  }

  return false;
}
//**********************************************************************
// CBaseConfigLoader::~CBaseConfigLoader()
// Default De-Cosnstructor
//**********************************************************************
CBaseConfigLoader::~CBaseConfigLoader() {
  pWorld        = 0;
  pLayerManager = 0;
  vConfigList.clear();
  vParameterList.clear();
}
