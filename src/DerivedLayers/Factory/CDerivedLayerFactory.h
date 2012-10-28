//============================================================================
// Name        : CDerivedLayerFactory.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
//============================================================================
#ifndef CDERIVEDLAYERFACTORY_H_
#define CDERIVEDLAYERFACTORY_H_

// Global Includes
#include <string>

// Local includes
#include "../CDerivedLayer.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedLayerFactory {
public:
  static CDerivedLayer*    buildDerivedLayer(string type, bool registerWithManager = true);

private:
  // Functions
  CDerivedLayerFactory() { };
  virtual ~CDerivedLayerFactory() { };
};

#endif /* CDERIVEDLAYERFACTORY_H_ */
