//============================================================================
// Name        : CBaseObject.cpp
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Includes
#include "CBaseObject.h"
#include "../Helpers/CConvertor.h"
#include "../Helpers/CComparer.h"

//**********************************************************************
// CBaseObject::CBaseObject()
// Default Constructor
//**********************************************************************
CBaseObject::CBaseObject(CBaseObject *Object) {
  // Assign Pointers
  pConfig               = CConfiguration::Instance();
  pRuntimeController    = CRuntimeController::Instance();
  pParameterList        = new CParameterList();

  // Values
  sLabel                = "";

  // Register the user defined variables
  pParameterList->registerAllowed(PARAM_LABEL);

  // Copy-Constructor
  if (Object != 0) {
    sLabel = Object->getLabel();
  }
}

//**********************************************************************
// void CBaseObject::registerEstimable(string name, double *variable)
// Register a Variable as Estimable.
//**********************************************************************
void CBaseObject::registerEstimable(string name, double *variable) {
  mEstimables[name] = variable;
}

//**********************************************************************
// void CBaseObject::registerEstimable(string name, int index, double *variable)
// Register variable as estimable with an index (used for Vectors)
//**********************************************************************
void CBaseObject::registerEstimable(string name, int index, double *variable) {
  string newName = name + string("(") + CConvertor::intToString(index) + string(")");
  mEstimables[newName] = variable;
}

//**********************************************************************
// double* CBaseObject::getEstimableVariable(string name)
// Get Our Estimable Variable
//**********************************************************************
double* CBaseObject::getEstimableVariable(string name) {
#ifndef OPTIMISE
  try {
#endif

    if (mEstimables[name] != 0)
      return mEstimables[name];
    else
      throw string(ERROR_UNKNOWN_ESTIMABLE + name);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CBaseObject.getEstimableVariable(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return 0;
}

//**********************************************************************
// void CBaseObject::addParameter(string name, string value)
// Add A Parameters
//**********************************************************************
void CBaseObject::addParameter(string name, string value) {
  pParameterList->addParameter(name, value);
}


//**********************************************************************
// CBaseObject::~CBaseObject()
// Default De-Constructor
//**********************************************************************
CBaseObject::~CBaseObject() {
  // Blank Pointers
  pConfig               = 0;
  pRuntimeController    = 0;

  delete pParameterList;
  pParameterList        = 0;
}
