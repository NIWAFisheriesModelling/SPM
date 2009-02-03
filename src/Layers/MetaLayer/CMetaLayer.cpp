//============================================================================
// Name        : CMetaLayer.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CMetaLayer.h"

//**********************************************************************
// CMetaLayer::CMetaLayer()
// Default constructor
//**********************************************************************
CMetaLayer::CMetaLayer() {

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_LAYER_NAMES);
}

//**********************************************************************
// void CMetaLayer::validate()
// Validate the layer
//**********************************************************************
void CMetaLayer::validate() {
  try {
    // Base
    CLayer::validate();

    // Populate our variables
    pParameterList->fillVector(vYears, PARAM_YEARS);
    pParameterList->fillVector(vLayerNames, PARAM_LAYER_NAMES);

    // TODO: Add more validation for vector sizes
    throw string("Object not yet implemented");

  } catch (string Ex) {
    Ex = "CMetaLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMetaLayer::build()
// Build the layer
//**********************************************************************
void CMetaLayer::build() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CMetaLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMetaLayer::~CMetaLayer()
// Destructor
//**********************************************************************
CMetaLayer::~CMetaLayer() {
}
