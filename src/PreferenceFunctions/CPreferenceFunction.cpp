//============================================================================
// Name        : CPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPreferenceFunction.h"
#include "../Layers/CLayerManager.h"
#include "../Layers/Numeric/Base/CNumericLayer.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CPreferenceFunction::CPreferenceFunction()
// Default Constructor
//**********************************************************************
CPreferenceFunction::CPreferenceFunction() {
  // Layer
  pLayer = 0;

  // Register our Estimables
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register User Allowed Parameters
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_ALPHA);
}

//**********************************************************************
// void CPreferenceFunction::validate()
// Validate
//**********************************************************************
void CPreferenceFunction::validate() {
  try {
    // Base Validation
    CBaseBuild::validate();

    // Populate our Parameters.
    sLayerName  = pParameterList->getString(PARAM_LAYER);
    dAlpha      = pParameterList->getDouble(PARAM_ALPHA,true,1.0);

  } catch (string &Ex) {
    Ex = "CPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CPreferenceFunction::build() {
  try {
    // Get our Layer
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayer = pLayerManager->getNumericLayer(sLayerName);

  } catch (string &Ex) {
    Ex = "CPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// CPreferenceFunction::~CPreferenceFunction()
// Destructor
//**********************************************************************
bool CPreferenceFunction::getIsStatic() {
  if (pLayer == 0)
    return true;

  return pLayer->getIsStatic();
}

//**********************************************************************
// CPreferenceFunction::~CPreferenceFunction()
// Destructor
//**********************************************************************
CPreferenceFunction::~CPreferenceFunction() {
}
