//============================================================================
// Name        : CReporterFactory.h
// Author      : S.Rasmussen
// Date        : 9/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CREPORTERFACTORY_H_
#define CREPORTERFACTORY_H_

// Global Headers
#include <string>

// Forward Dec
class CReporter;

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CReporterFactory {
public:
  // Functions
  static CReporter*           buildReporter(string type);
private:
  // Functions
  CReporterFactory();
  virtual ~CReporterFactory();
};

#endif /* CREPORTERFACTORY_H_ */
