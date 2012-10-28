//============================================================================
// Name        : CDerivedLayerFactory.cpp
// Author      : S.Rasmussen
// Date        : 23/10/2012
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
//============================================================================

// Local includes
#include "CDerivedLayerFactory.h"
#include "../CDerivedLayerManager.h"
#include "../../Helpers/CError.h"
#include "../Children/CAbundanceDerivedLayer.h"
#include "../Children/CBiomassDerivedLayer.h"

//**********************************************************************
// CDerivedLayer* CDerivedLayerFactory::buildDerivedLayer(string type, bool registerWithManager)
// Build a Derived Layer
//**********************************************************************
CDerivedLayer* CDerivedLayerFactory::buildDerivedLayer(string type, bool registerWithManager) {

  CDerivedLayer *pLayer = 0;

  if (type == PARAM_ABUNDANCE)
    pLayer = new CAbundanceDerivedLayer();
  else if (type == PARAM_BIOMASS)
    pLayer = new CBiomassDerivedLayer();
  else
    CError::errorUnknown(PARAM_DERIVED_LAYER, type);

  if (registerWithManager)
    CDerivedLayerManager::Instance()->addDerivedLayer(pLayer);

  return pLayer;
}
