//============================================================================
// Name        : CDerivedLayerFactory.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
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
