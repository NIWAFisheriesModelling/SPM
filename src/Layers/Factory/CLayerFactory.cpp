//============================================================================
// Name        : CLayerFactory.cpp
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : << See CLayerFactory.h >>
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CLayerFactory.h"
#include "../CLayerManager.h"
#include "../../Helpers/CError.h"
#include "../../Translations/Translations.h"
#include "../MetaLayer/CMetaLayer.h"
#include "../Numeric/CAbundanceDensityLayer.h"
#include "../Numeric/CAbundanceLayer.h"
#include "../Numeric/CBiomassDensityLayer.h"
#include "../Numeric/CBiomassLayer.h"
#include "../Numeric/CDistanceLayer.h"
#include "../Numeric/CDoubleLayer.h"
#include "../String/CStringLayer.h"

//**********************************************************************
// CLayer* CLayerFactory::buildLayer(string type)
// Build us a layer based on type
//**********************************************************************
CLayer* CLayerFactory::buildLayer(string type, bool registerWithManager) {

  CLayer *pLayer = 0;

  if (type == PARAM_META)
    pLayer = new CMetaLayer();
  else if (type == PARAM_ABUNDANCE_DENSITY)
    pLayer = new CAbundanceDensityLayer();
  else if (type == PARAM_ABUNDANCE)
    pLayer = new CAbundanceLayer();
  else if (type == PARAM_BIOMASS_DENSITY)
    pLayer = new CBiomassDensityLayer();
  else if (type == PARAM_BIOMASS)
    pLayer = new CBiomassLayer();
  else if (type == PARAM_DISTANCE)
    pLayer = new CDistanceLayer();
  else if (type == PARAM_DOUBLE)
    pLayer = new CDoubleLayer();
  else if (type == PARAM_STRING)
    pLayer = new CStringLayer();
  else
    CError::errorUnknown(PARAM_TYPE, type);

  // Register the layer with the manager if required
  if (registerWithManager)
    CLayerManager::Instance()->addLayer(pLayer);

  return pLayer;
}
