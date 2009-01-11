//============================================================================
// Name        : CEstimateFactory.h
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CESTIMATEFACTORY_H_
#define CESTIMATEFACTORY_H_

// Global headers
#include <string>

// Forward-Dec
class CEstimate;

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CEstimateFactory {
public:
  // Functions
  CEstimate*                  buildEstimate(string type);

private:
  // Functions
  CEstimateFactory();
  virtual ~CEstimateFactory();
};

#endif /* CESTIMATEFACTORY_H_ */
