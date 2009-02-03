//============================================================================
// Name        : CFileReporter.h
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CFILEREPORTER_H_
#define CFILEREPORTER_H_

// Global Headers
#include <string>
#include <iostream>
#include <fstream>

// Local headers
#include "../../CReporter.h"

// Using
using std::streambuf;
using std::ofstream;
using std::cout;
using std::endl;
using std::ios_base;

//**********************************************************************
//
//
//**********************************************************************
class CFileReporter: public CReporter {
public:
  // Functions
  CFileReporter();
  virtual                     ~CFileReporter();
  virtual void                validate();
  virtual void                build() { CReporter::build(); };
  void                        start();
  void                        end();

protected:
  // Variables
  string                     sFileName;
  bool                       bOverwrite;
  streambuf*                 sCoutBackup;
  ofstream                   *fFile;
  bool                       bStartedWrite;
};

#endif /* CFILEREPORTER_H_ */
