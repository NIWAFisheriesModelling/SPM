//============================================================================
// Name        : CLayerFactory.h
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLAYERFACTORY_H_
#define CLAYERFACTORY_H_

// Global Headers
#include <string>

// Forward Dec.
class CLayer;

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CLayerFactory {
public:
  // Functions
  static CLayer*         buildLayer(string type);

private:
  // Functions
  CLayerFactory();
  virtual ~CLayerFactory();
};

#endif /* CLAYERFACTORY_H_ */
