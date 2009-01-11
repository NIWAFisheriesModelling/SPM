//============================================================================
// Name        : CProcessFactory.h
// Author      : S.Rasmussen
// Date        : 5/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPROCESSFACTORY_H_
#define CPROCESSFACTORY_H_

// Global Headers
#include <string>

// Forward Declaration
class CProcess;

// Namespaces
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CProcessFactory {
public:
  // Functions
  static CProcess*            buildProcess(string type);

private:
  // Functions
  CProcessFactory() { };
  virtual                     ~CProcessFactory() { };
};

#endif /* CPROCESSFACTORY_H_ */
