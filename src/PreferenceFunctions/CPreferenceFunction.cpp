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
// CPreferenceFunction::CPreferenceFunction(CPreferenceFunction *Process)
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
// Destructor
//**********************************************************************
CPreferenceFunction::~CPreferenceFunction() {
}
