//============================================================================
// Name        : CConfigHandlerFactory.h
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONFIGHANDLERFACTORY_H_
#define CCONFIGHANDLERFACTORY_H_

// Global Headers
#include <string>

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CConfigHandlerFactory {
public:
//  static CConfigurationLoader*      buildLoader(string type);
private:
  // Functions
  CConfigHandlerFactory() { };
  virtual ~CConfigHandlerFactory() { };
};

#endif /* CCONFIGHANDLERFACTORY_H_ */
