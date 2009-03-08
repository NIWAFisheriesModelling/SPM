//============================================================================
// Name        : CStandardHeaderReporter.h
// Author      : S.Rasmussen
// Date        : 5/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSTANDARDHEADERREPORTER_H_
#define CSTANDARDHEADERREPORTER_H_

// Global Headers
#include <string>

#ifdef __MINGW32__
  #include <process.h>
#else
  #include <sys/utsname.h>
  #include <sys/times.h>
  #include <unistd.h>
#endif

// Local headers
#include "../CReporter.h"

// Namespace
using std::string;

// Version number
#define VERSION "1.00"

//**********************************************************************
//
//
//**********************************************************************
class CStandardHeaderReporter: public CReporter {
public:
  // Functions
  CStandardHeaderReporter();
  virtual                     ~CStandardHeaderReporter();
  CReporter*                  clone() { return new CStandardHeaderReporter(*this); }
  void                        start();
  void                        execute();
  void                        end();

protected:
  // Variables
  string                      sHeader;
  string                      sVersion;
  time_t                      tmeStart;

  // Linux Vars
#ifndef __MINGW32__
  tms                         cpu_start;
  tms                         cpu_stop;
#endif
};

#endif /* CSTANDARDHEADERREPORTER_H_ */
