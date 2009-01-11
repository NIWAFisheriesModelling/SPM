//============================================================================
// Name        : CLayerFactory.cpp
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CLayerFactory.h"
#include "../../Translations/Translations.h"
#include "../Numeric/CAbundanceLayer.h"
#include "../Numeric/CDistanceLayer.h"
#include "../Numeric/CDoubleLayer.h"
#include "../String/CStringLayer.h"

//**********************************************************************
// CLayer* CLayerFactory::buildLayer(string type)
// Build us a layer based on type
//**********************************************************************
CLayer* CLayerFactory::buildLayer(string type) {

  if (type == PARAM_ABUNDANCE)
    return new CAbundanceLayer();
  else if (type == PARAM_DISTANCE)
    return new CDistanceLayer();
  else if (type == PARAM_NUMERIC)
    return new CDoubleLayer();
  else if (type == PARAM_CATEGORY)
    return new CStringLayer();
  else
    throw string("UNKNOWN LAYER");

  return 0;
}
