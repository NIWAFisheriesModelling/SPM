//============================================================================
// Name        : CFileReporter.cpp
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CFileReporter.h"

//**********************************************************************
// CFileReporter::CFileReporter()
// Default constructor
//**********************************************************************
CFileReporter::CFileReporter() {
  // Default Values
  sFileName           = "";
  bOverwrite          = true;
  bStartedWrite       = false;
  fFile               = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FILE_NAME);
  pParameterList->registerAllowed(PARAM_OVERWRITE);
}

//**********************************************************************
// void CFileReporter::validate()
// Validate file reporter
//**********************************************************************
void CFileReporter::validate() {
  try {
    // Base
    CReporter::validate();

    // Assign variables
    sFileName   = pParameterList->getString(PARAM_FILE_NAME, true, "");
    bOverwrite  = pParameterList->getBool(PARAM_OVERWRITE, true, false);

    fFile = new ofstream();
  } catch (string Ex) {
    Ex = "CFileReporter.validate(" + getLabel() + ")->" + Ex;

  }
}

//**********************************************************************
// void CFileReporter::start()
// Start the Reporting
//**********************************************************************
void CFileReporter::start() {
  if (sFileName != "") {
    // Variables
    sCoutBackup     = cout.rdbuf();

    // Set our Open Flag
    ios_base::openmode mode = ios_base::out;
    if (!bOverwrite )
      mode = ios_base::app;

    // Try to Open our File

    fFile->open(sFileName.c_str(), mode);
    if (!(*fFile))
      throw string(ERROR_OPEN_FILE + sFileName); // TODO: CError

    // Redirect Standard Output
    cout.rdbuf(fFile->rdbuf());
  }

  // Now we want to Append
  bOverwrite = false;
}

//**********************************************************************
// void CFileReporter::end()
// End the Reporting
//**********************************************************************
void CFileReporter::end() {
  if (sFileName != "") {
    fFile->close();
    cout.rdbuf(sCoutBackup);
  }
}


//**********************************************************************
// CFileReporter::~CFileReporter()
// Destructor
//**********************************************************************
CFileReporter::~CFileReporter() {
  if (fFile != 0)
    delete fFile;
}
