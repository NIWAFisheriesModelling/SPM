//============================================================================
// Name        : CLayer_Fixture.cpp
// Author      : S.Rasmussen
// Date        : 18/02/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Headers
#include <iostream>
#include <boost/test/unit_test.hpp>

// Local headers
#include "CLayer_Fixture.h"
#include "../Layers/CLayerManager.h"
#include "../Layers/Factory/CLayerFactory.h"
#include "../Helpers/CConvertor.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CLayer_Fixture::CLayer_Fixture()
// Constructor
//**********************************************************************
CLayer_Fixture::CLayer_Fixture() {

  // Create a Double Layer
  CLayer *pLayer = CLayerFactory::buildLayer(PARAM_DOUBLE);
  pLayer->addParameter(PARAM_LABEL, "double_layer");
  for (int i = 0; i < 25; ++i)
    pLayer->addParameter(PARAM_DATA, CConvertor::intToString(i+1));
  pLayer->validate();
  pLayer->build();

  // Create a Distance Layer
  pLayer = CLayerFactory::buildLayer(PARAM_DISTANCE);
  pLayer->addParameter(PARAM_LABEL, "distance_layer");
  pLayer->validate();
  pLayer->build();

}

//**********************************************************************
// CLayer_Fixture::~CLayer_Fixture()
// Destructor
//**********************************************************************
CLayer_Fixture::~CLayer_Fixture() {
  CLayerManager::Destroy();
}

#endif
