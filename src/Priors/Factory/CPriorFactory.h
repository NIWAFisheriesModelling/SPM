//============================================================================
// Name        : CPriorFactory.h
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPRIORFACTORY_H_
#define CPRIORFACTORY_H_

// Global headers
#include <string>

// Forward-Dec
class CPrior;

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CPriorFactory {
public:
  // Functions
  static CPrior*              buildPrior(string type);

private:
  // Functions
  CPriorFactory();
  virtual ~CPriorFactory();
};

#endif /* CPRIORFACTORY_H_ */
