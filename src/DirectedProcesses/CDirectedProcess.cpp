//============================================================================
// Name        : CDirectedProcess.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CDirectedProcess.h"
#include "../Layers/CLayerManager.h"
#include "../Layers/Numeric/Base/CNumericLayer.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CDirectedProcess::CDirectedProcess()
// Default Constructor
//**********************************************************************
CDirectedProcess::CDirectedProcess(CDirectedProcess *Process)
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
// void CDirectedProcess::validate()
// Validate
//**********************************************************************
void CDirectedProcess::validate() {
  try {
    // Base Validation
    CBaseExecutableObject::validate();

    // Populate our Parameters.
    sLayerName  = pParameterList->getString(PARAM_LAYER_NAME);
    dAlpha      = pParameterList->getDouble(PARAM_ALPHA);

  } catch (string Ex) {
    Ex = "CDirectedProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDirectedProcess::build()
// Build our Object
//**********************************************************************
void CDirectedProcess::build() {
  try {
    // Get our Layer
    if (pLayer == 0) {
      CLayerManager *pLayerManager = CLayerManager::Instance();
      pLayer = pLayerManager->getNumericLayer(sLayerName);
    }

  } catch (string Ex) {
    Ex = "CDirectedProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDirectedProcess::execute()
// Execute - Should never be called
//**********************************************************************
void CDirectedProcess::execute() {
  try {
    throw string(ERROR_SUPPORTED_FUNCTION);
  } catch (string Ex) {
    Ex = "CDirectedProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDirectedProcess::~CDirectedProcess()
// Default De-Constructor
//**********************************************************************
CDirectedProcess::~CDirectedProcess() {
}
