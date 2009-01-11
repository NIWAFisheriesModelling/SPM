//============================================================================
// Name        : CConfigurationLoader.cpp
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <fstream>

// Local Headers
#include "CConfigurationLoader.h"
#include "../Translations/Translations.h"

// Using
using std::ifstream;

//**********************************************************************
// CConfigurationLoader::CConfigurationLoader()
// Default Constructor
//**********************************************************************
CConfigurationLoader::CConfigurationLoader() {
  // Variables
  sFileName           = "";
}

//**********************************************************************
// void CConfigurationLoader::loadConfigFile()
// Entry Point to load our configuration file
//**********************************************************************
void CConfigurationLoader::loadConfigFile() {
  try {
    // Load file to memory
    loadConfigIntoCache();

    // Verify file had contents
    if ((int)vLines.size() == 0)
      throw string("Empty configuration file");

    if (vLines[0].substr(0, 1) != CONFIG_SECTION_SYMBOL)
      throw string("First statement (ex comments) must be a section header");

    vCurrentSection.push_back(vLines[0]);
    for (int i = 1; i < (int)vLines.size(); ++i) {

      // New Section? Process It
      if (vLines[i].substr(0,1) == CONFIG_SECTION_SYMBOL) {
        processSection();
        vCurrentSection.clear();
      }

      vCurrentSection.push_back(vLines[i]);
    }

    processSection();
  } catch (string Ex) {
    // TODO: Add Exception
  }
}

//**********************************************************************
// void CConfigurationLoader::processSection()
// Process Our Section
//**********************************************************************
void CConfigurationLoader::processSection() {

}

//**********************************************************************
// void CConfigurationLoader::loadConfigIntoCache()
// Load the configuration file into memory
//**********************************************************************
void CConfigurationLoader::loadConfigIntoCache() {
  try {
    if (sFileName == "")
      throw string(ERROR_INVALID_FILE_NAME);

    ifstream fConfig(sFileName.c_str());
    if (!fConfig)
     throw string(ERROR_OPEN_FILE + sFileName);

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
       // if ( (sIncludeFile.substr(0, 1) == "/") || (sIncludeFile.substr(1, 1) == ":") )
        //  loadConfigIntoCache(sIncludeFile); // Absolute
       // else
       //   loadConfigIntoCache(sDirectory + (sDirectory==""?"":"//") + sIncludeFile); // Relative

        // Blank line so it's not added
        sLine = "";
      }

      if (sLine.length() > 0)
        vLines.push_back(sLine);
    }
    fConfig.close();
  } catch (string Ex) {
    Ex = "CConfigurationLoader.loadConfigIntoCache(" + sFileName +")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CConfigurationLoader::~CConfigurationLoader()
// Destructor
//**********************************************************************
CConfigurationLoader::~CConfigurationLoader() {

}
