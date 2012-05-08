//============================================================================
// Name        : CBaseObject.cpp
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CBaseObject.h"
#include "../Helpers/CConvertor.h"
#include "../Helpers/CComparer.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CBaseObject::CBaseObject()
// Default Constructor
//**********************************************************************
CBaseObject::CBaseObject() {
  // Assign Pointers
  pConfig               = CConfiguration::Instance();
  pRuntimeController    = CRuntimeController::Instance();
  pParameterList        = new CParameterList();
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
  string newName = name + string("(") + boost::lexical_cast<string>(index) + string(")");
  mEstimables[newName] = variable;
}

//**********************************************************************
// double* CBaseObject::getEstimableVariable(string name)
// Get Our Estimable Variable
//**********************************************************************
double* CBaseObject::getEstimableVariable(string name) {
#ifndef OPTIMIZE
  try {
    name = CConvertor::stringToLowercase(name);

    if (mEstimables[name] == 0)
      CError::errorUnknown(PARAM_ESTIMABLE, name);

  } catch (string &Ex) {
    Ex = "CBaseObject.getEstimableVariable()->" + Ex;
    throw Ex;
  }
#endif

  return mEstimables[name];
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
