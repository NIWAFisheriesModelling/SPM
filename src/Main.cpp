//============================================================================
// Name        : Main.cpp
// Author      : S.Rasmussen
// Date        : 10/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This is our application entry point (int main()).
//       From here we collect the variables and command line parameters for
//       passing off to the CWorld for it's running.
//
//       The majority of this code is for parsing command line options
//       and flagging the variables associated with each.
//
// $Date$
//============================================================================
#ifdef TEST
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_MODULE SPM_Unit_Tests

// Global Includes
#include <boost/test/included/unit_test.hpp>
#else


// Global Headers
#include <iostream>

// Local Headers
#include "CRuntimeController.h"
#include "CConfiguration.h"
#include "License.txt"
#include "Reports/Children/CStandardHeaderReport.h"
#include "Version.h"
// Namespaces
using namespace std;

//**********************************************************************
// int main(int argc,char * argv[])
// Application Entry Point
//**********************************************************************
//test_suite* init_unit_test_suite( int argc, char* argv[] ) {
int main(int argc, char * argv[]) {

  // Load Command Line into Configuration
  CConfiguration *pConfig = CConfiguration::Instance();
  for (int i = 0; i < argc; ++i)
    pConfig->addCommandLineParameter(argv[i]);

  // Create Reporter
  CStandardHeaderReport clReporter;

  // Create Runtime Controller
  CRuntimeController  *pRuntime = 0;
  pRuntime = CRuntimeController::Instance();

  // Try to Parse the command line.
  try {
    pRuntime->parseCommandLine(argc, argv);

  } catch(string &Ex) {
    clReporter.start();
    cout << "[ERROR] " << Ex << endl;
    clReporter.end();
    return 0;
  }

  // If we are just printing the Version, then do so.
  std::stringstream sRevisionNumber;
  sRevisionNumber << SOURCE_CONTROL_REVISION;
  if (pRuntime->getRunMode() == RUN_MODE_VERSION) {
    cout << string(VERSION) << "-" << string(SOURCE_CONTROL_DATE) << " (rev. " << sRevisionNumber.str() << ")" << endl;
    return 0;
  }

  try {
    clReporter.start();

    // Check Run-Mode
    if (pRuntime->getRunMode() == RUN_MODE_LICENSE) {
      cout << sLicense << endl;
    } else if (pRuntime->getRunMode() == RUN_MODE_HELP) {
      cout << pRuntime->getCommandLineOptions() << endl;
    } else {
      pRuntime->loadConfiguration();
      pRuntime->run();
    }

  } catch (string Ex) {
    cout << "[ERROR] SPM has encountered a problem" << endl;

    // Un-Wind our Exception Stack
    int iLastLocation = 0;
    while (iLastLocation != -1) {
      int iLoc = Ex.find_first_of(">", iLastLocation+1);
      cout << Ex.substr(iLastLocation+1, (iLoc-iLastLocation)) << endl;
      iLastLocation = iLoc;
    }
    cout << endl;
  } catch(exception &Ex) {
    // Do Nothing
    cout << "[ERROR] SPM encountered an exception" << endl;
    cout << "[EXCEPTION] " << Ex.what() << endl;
  }

  // Clean Up our Model
  CRuntimeController::Destroy();

  clReporter.end();

  return 0;
}
#endif
