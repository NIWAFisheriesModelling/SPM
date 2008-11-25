//============================================================================
// Name        : CLayer.cpp
// Author      : S.Rasmussen
// Date        : 11/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CLayer.h"
#include "../CWorld.h"

//**********************************************************************
// CLayer::CLayer(CLayer *Layer = 0)
// Default Constructor
//**********************************************************************
CLayer::CLayer(CLayer *Layer)
: CBaseBuildableObject(Layer) {

  // Default Our Layer Vars
  sLabel      = "";
  sType       = "";
  bNormalize  = false;

  CWorld *pWorld    = CWorld::Instance();
  iWidth            = pWorld->getWidth();
  iHeight           = pWorld->getHeight();

  // Copy Construct
  if (Layer != 0) {
    sLabel          = Layer->getLabel();
    sType           = Layer->getType();
    bNormalize      = Layer->getNormalize();
    iWidth          = Layer->getWidth();
    iHeight         = Layer->getHeight();
  }
}

//**********************************************************************
// void CLayer::validate()
// Validate
//**********************************************************************
void CLayer::validate() {
  try {
    if (sLabel == "")
      errorMissing(PARAM_LABEL);
    if (sType == "")
      errorMissing(PARAM_TYPE);

  } catch (string Ex) {
    Ex = "CLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CLayer::~CLayer()
// Default De-Constructor
//**********************************************************************
CLayer::~CLayer() {
}
