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
#ifndef UNITTEST

//SPM Version Number
#define VERSION "0.2"

// Global Headers
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <math.h>
#ifdef __MINGW32__
#include <process.h>
#else
  #include <sys/utsname.h>
  #include <sys/times.h>
  #include <unistd.h>
#endif

#ifdef TIMING
#include <windows.h>
#endif

// Local Headers
#include "CRuntimeController.h"
#include "CConfiguration.h"
#include "Version.h"
#include "License.txt"

// Namespaces
using namespace std;
using namespace boost::program_options;

//**********************************************************************
// int main(int argc,char * argv[])
// Application Entry Point
//**********************************************************************
//test_suite* init_unit_test_suite( int argc, char* argv[] ) {
int main(int argc,char * argv[]) {

#ifdef TIMING
  DWORD tickStart = GetTickCount();
#endif

  // Create The Header For Output
  string    sHeader    = "SPM (Spatial Population Model)\n";
  string    sVersion   = "";
  time_t    tmeStart   = time(NULL);

  #ifndef __MINGW32__
    // Non-Windows, Generate CPU Time
    tms cpu_start, cpu_stop;
    times(&cpu_start);
  #endif

  // Add Parameters
  sHeader += "Call: ";
  for (int i=0; i<argc; i++)
    sHeader += argv[i] + string(" ");

  sHeader += "\nDate: "+ string(ctime(&tmeStart));
  sVersion = "v" + string(VERSION) + "-" + string(SOURCE_CONTROL_VERSION);
  sHeader += sVersion + ". Copyright (c) 2008-" + string(SOURCE_CONTROL_YEAR) +", NIWA/MFish\n";

  #ifdef __MINGW32__
    sHeader += "User name: " + string(getenv("USERNAME")) + "\n";
    sHeader += "Machine name: " + string(getenv("COMPUTERNAME")) + " (";
    sHeader += string(getenv("OS")) + ", ";
    ostringstream PID;
    PID << _getpid();
    sHeader += "PID=" + PID.str() + ")\n\n";
  #else
    char* cUsername = getenv("LOGNAME");
    if (cUsername != NULL)
      sHeader += "User name: " + string(cUsername) + "\n";
    else {
      sHeader += "User name: -----\n";
    }
    sHeader += "\nMachine name: ";
    struct utsname names;
    uname(&names);
    sHeader += static_cast<string>(names.nodename) + " (" + static_cast<string>(names.sysname) + " " + static_cast<string>(names.release) + " " + static_cast<string>(names.machine);
    ostringstream PID;
    PID << getpid();
    sHeader += "PID=" + PID.str() + ")\n\n";
  #endif

  // Create Model Variables
  CRuntimeController  *pRuntime = CRuntimeController::Instance();
  CConfiguration      *pConfig  = CConfiguration::Instance();

  try {
    // Setup our Boost Command Line Arguments
    options_description oDesc("Usage");
    oDesc.add_options()
        ("help", "Print help (this screen")
        ("version", "display single line summarising the version")
        ("license", "display source code license")
        ("mode", value<string>(), "mode of execution for the model")
        ("values", "load estimate values from configuration file")
        //("threads", value<int>(), "number of threads to run, default = 1")
        ("path", value<string>(), "path for configuration files")
        ("verbose", "extended output to count");

    // Read our Parameters
    variables_map vmParams;
    store(parse_command_line(argc, argv, oDesc), vmParams);
    notify(vmParams);

    // Check our Params
    if (vmParams.count("version")) {
      cout << sVersion << endl;
      return 0;
    }
    // Print our Our Header
    cout << sHeader;

    if (vmParams.count("license")) {
      cout << sLicense << endl;
      return 0;
    }
    if ( (vmParams.count("help")) || (vmParams.size() == 0) ) {
      cout << oDesc << endl;
      return 0;
    }
    if (vmParams.count("verbose"))
      pConfig->setVerboseMode(true);
    if (vmParams.count("path"))
      pConfig->setConfigPath(vmParams["path"].as<string>());
    //if (vmParams.count("threads"))
      //pConfig->setNumberOfThreads(vmParams["threads"].as<int>());
    if (vmParams.count("mode"))
      pRuntime->setRunMode(vmParams["mode"].as<string>());
    else {
      cout << "Error: missing required parameter (mode)" << endl;
      vmParams.clear();
    }
    if (vmParams.count("values")) {
      pConfig->setUseEstimateValues(true);
    }

    pRuntime->loadConfiguration();
    pRuntime->run();

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
    cout << "[EXCEPTION]" << Ex.what() << endl;
  }

  // Clean Up our Model
  CRuntimeController::Destroy();
  cout << "Done." << endl;


  #ifndef __MINGW32__
    times(&cpu_stop);
    double cpu_time=(static_cast<double>(cpu_stop.tms_utime)+static_cast<double>(cpu_stop.tms_stime))-(static_cast<double>(cpu_start.tms_utime) + static_cast<double>(cpu_start.tms_stime));
    // Turn into seconds
    cpu_time /= static_cast<double>(sysconf(_SC_CLK_TCK));
    // Turn into hours
    cpu_time = cpu_time / 3600.0;
    int P = (int) floor(log10(cpu_time))+4;
    cout << "Total CPU time: " << std::setprecision(P) << cpu_time << (cpu_time==1?" hour":" hours") << ".\n";
  #endif
  double elapsed_time = static_cast<double>(time(NULL)-tmeStart);
  if(elapsed_time < 60) {
    int P = (int) floor(log10(elapsed_time))+4;
    cout << "Total elapsed time: " << std::setprecision(P) << elapsed_time << (elapsed_time==1?" second":" seconds") << endl;
  } else if((elapsed_time/60.0) < 60) {
    elapsed_time /= 60.0;
    int P = (int) floor(log10(elapsed_time))+4;
    cout << "Total elapsed time: " << std::setprecision(P) << elapsed_time << (elapsed_time==1?" minute":" minutes") << endl;
  } else {
    elapsed_time /= 3600.0;
    int P = (int) floor(log10(elapsed_time))+4;
    cout << "Total elapsed time: " << std::setprecision(P) << elapsed_time << (elapsed_time==1?" hour":" hours") << endl;
  }

#ifdef TIMING
  cout << (GetTickCount() - tickStart) << "ms" << endl;
#endif


  return 0;
}
#endif
