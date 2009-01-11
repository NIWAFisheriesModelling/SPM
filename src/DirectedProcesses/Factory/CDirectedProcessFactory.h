//============================================================================
// Name        : CDirectedProcessFactory.h
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDIRECTEDPROCESSFACTORY_H_
#define CDIRECTEDPROCESSFACTORY_H_

// Global Includes
#include <string>

// Forward Dec
class CDirectedProcess;

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CDirectedProcessFactory {
public:
  // Functions
  static CDirectedProcess*    buildDirectedProcess(string type);

private:
  // Functions
  CDirectedProcessFactory() { }
  virtual ~CDirectedProcessFactory() { }
};

#endif /* CDIRECTEDPROCESSFACTORY_H_ */
