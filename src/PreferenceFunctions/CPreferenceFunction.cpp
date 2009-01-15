c//============================================================================
// Name        : CPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2009-01-12 11:44:49 +1300 (Mon, 12 Jan 2009) $
//============================================================================

// Local Headers
#include "CPreferenceFunction.h"
#include "../Layers/CLayerManager.h"
#include "../Layers/Numeric/Base/CNumericLayer.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CPreferenceFunction::CPreferenceFunction()
// Default Constructor
//**********************************************************************
CPreferenceFunction::CPreferenceFunction(CPreferenceFunction *Process)
: CBaseExecutableObject(Process) {

  // Variables
  dAlpha                 = -1.0;
  sLayerName             = "";
  pLayer                 = 0;
  dLayerValue            = 0.0;
  bIsStaticLookup        = false;
  dRet                   = 0.0;

  // Register our Estimables
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register User Allowed Parameters
  pParameterList->registerAllowed(PARAM_LAYER_NAME);
  pParameterList->registerAllowed(PARAM_ALPHA);

  // Copy Constructor
  if (Process != 0) {
    dAlpha        = Process->getAlpha();
    sLayerName    = Process->getLayerName();
  }
}

//**********************************************************************
// void CPreferenceFunction::validate()
// Validate
//**********************************************************************
void CPreferenceFunction::validate() {
  try {
    // Base Validation
    CBaseExecutableObject::validate();

    // Populate our Parameters.
    sLayerName  = pParameterList->getString(PARAM_LAYER_NAME);
    dAlpha      = pParameterList->getDouble(PARAM_ALPHA);

  } catch (string Ex) {
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
    if (pLayer == 0) {
      CLayerManager *pLayerManager = CLayerManager::Instance();
      pLayer = pLayerManager->getNumericLayer(sLayerName);
    }

  } catch (string Ex) {
    Ex = "CPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceFunction::execute()
// Execute - Should never be called
//**********************************************************************
void CPreferenceFunction::execute() {
  try {
    throw string(ERROR_SUPPORTED_FUNCTION);
  } catch (string Ex) {
    Ex = "CPreferenceFunction.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPreferenceFunction::~CPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CPreferenceFunction::~CPreferenceFunction() {
}
