//============================================================================
// Name        : CMCMCFactory.h
// Author      : S.Rasmussen
// Date        : 10/11/2014
// Copyright   : Copyright NIWA Science ©2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CMCMCFACTORY_H_
#define CMCMCFACTORY_H_

// Global Headers
#include <string>

// Local headers
#include "../CMCMC.h"

// Namespaces
using std::string;

/**
 * Class definition
 */
class CMCMCFactory {
public:
  // Functions
  static CMCMC*            buildMCMC(string type, bool registerWithManager = true);

private:
  CMCMCFactory() {};
  virtual ~CMCMCFactory() {};
};

#endif /* CMCMCFACTORY_H_ */
