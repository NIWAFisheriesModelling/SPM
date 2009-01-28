//============================================================================
// Name        : CPrintState.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CPrintState.h"

//**********************************************************************
// CPrintState::CPrintState()
// Default Constructor
//**********************************************************************
CPrintState::CPrintState() {
  sFileName           = "";
  bOverwrite          = true;
  bWriteToFile        = false;
  sFullFileName       = "";
  eState              = STATE_INVALID;
}

//**********************************************************************
// void CPrintState::openStream()
// Open the Stream to Write
//**********************************************************************
void CPrintState::openStream() {
  try {
    if (bWriteToFile) {
      // Variables
      sCoutBackup     = cout.rdbuf();

      // Set our Open Flag
      ios_base::openmode mode = ios_base::out;
      if (!getOverwrite())
        mode = ios_base::app;

      // Try to Open our File
      fFile.open(sFullFileName.c_str(), mode);
      if (!fFile)
        throw string(ERROR_OPEN_FILE + sFullFileName);

      // Redirect Standard Output
      cout.rdbuf(fFile.rdbuf());
    }
  } catch (string Ex) {
    Ex = "CPrintState.openStream(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPrintState::closeStream()
// Close The Stream
//**********************************************************************
void CPrintState::closeStream() {
  try {
    if (bWriteToFile) {
      // Close File if we used it.
      if (sFullFileName != "")
        fFile.close();

      // Reset Cout
      cout.rdbuf(sCoutBackup);
    }
  } catch (string Ex) {
    Ex = "CPrintState.closeStream(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPrintState::validate()
// Validate
//**********************************************************************
void CPrintState::validate() {
  try {
    // Base Validation


  } catch (string Ex) {
    Ex = "CPrintState.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPrintState::build()
// Build
//**********************************************************************
void CPrintState::build() {
  try {
    if ((sFileName != "") && (!bWriteToFile))
      bWriteToFile = true;

    // If we are using a file for output. Temp Redirect cout
    if ((bWriteToFile) && (sFullFileName == "")) {
      // Make sure it's surrounded by ""
      int iFirstIndex = sFileName.find_first_of("\"");
      int iLastIndex  = sFileName.find_last_of("\"");
      int iOtherIndex = sFileName.find_first_of("\"", iFirstIndex+1);

      if (iOtherIndex != iLastIndex)
        throw string(ERROR_CONTAIN_QUOTES);
      if ( (iFirstIndex == -1) || (iLastIndex == -1) || (iFirstIndex == iLastIndex) )
        throw string(ERROR_MISSING_QUOTES);

      // Remove Quotes From File Name
      sFileName = sFileName.substr(iFirstIndex+1, iLastIndex-1);

      // Check for Relative or Absolute File Name
      if ( (sFileName.substr(0, 1) == "/") || (sFileName.substr(1,1) == ":") )
        sFullFileName = sFileName; // Absolute
      else {
        //if (pConfig->getConfigPath() != "")
         // sFullFileName = pConfig->getConfigPath() + "/" + sFileName; // Relative
        //else
          sFullFileName = sFileName; // Relative, no Config Path attached.
      }
    }

  } catch (string Ex) {
    Ex = "CPrintState.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPrintState::~CPrintState()
// Default De-Constructor
//**********************************************************************
CPrintState::~CPrintState() {
}
