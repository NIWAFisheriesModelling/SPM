//============================================================================
// Name        : CBaseObject.cpp
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <sstream>
#include <iostream>

// Local Includes
#include "CBaseObject.h"

//**********************************************************************
// CBaseObject::CBaseObject()
// Default Constructor
//**********************************************************************
CBaseObject::CBaseObject(CBaseObject *Object) {
  // Assign Pointers
  pConfig               = CConfiguration::Instance();
  pRuntimeController    = CRuntimeController::Instance();

  // Verbose Mode?
  bVerbose              = pConfig->getVerboseMode();

  // Values
  sLabel                = "";

  // Copy-Constructor
  if (Object != 0) {
    sLabel = Object->getLabel();
  }
}

//**********************************************************************
// void CBaseObject::print(string output)
// Print out to Screen
//**********************************************************************
void CBaseObject::print(string output) {
#ifndef OPTIMISE
  if (bVerbose) {
    std::cout << output;
    std::cout.flush();
  }
#endif
}

//**********************************************************************
// void CBaseObject::println(string output)
// Print a line out to Screen
//**********************************************************************
void CBaseObject::println(string output) {
#ifndef OPTIMISE
  if (bVerbose)
    std::cout << output << std::endl;
#endif
}

//**********************************************************************
// string CBaseObject::convertDouble(double value)
// Convert Double To String
//**********************************************************************
string CBaseObject::convertDouble(double value) {
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

//**********************************************************************
// string CBaseObject::convertDouble(int value)
// Convert Double To String
//**********************************************************************
string CBaseObject::convertInt(int value) {
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

//**********************************************************************
// void CBaseObject::registerEstimable(string name, double *variable)
// Register a Variable as Estimable.
//**********************************************************************
void CBaseObject::registerEstimable(string name, double *variable) {
  try {
    mEstimables[name] = variable;
  } catch (string Ex) {
    Ex = "CBaseObject.registerEstimable(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBaseObject::registerEstimable(string name, int index, double *variable)
// Register variable as estimable with an index (used for Vectors)
//**********************************************************************
void CBaseObject::registerEstimable(string name, int index, double *variable) {
  try {
    string newName = name + string("(") + convertInt(index) + string(")");
    mEstimables[name] = variable;

  } catch (string Ex) {
    Ex = "CBaseObject.registerEstimable(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
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
// void CBaseObject::errorMissing(string value)
// Throw Missing Exception
//**********************************************************************
void CBaseObject::errorMissing(string value) {
  string sException = ERROR_MISSING;
  sException += value;
  throw sException;
}

//**********************************************************************
// void CBaseObject::errorLessThan(string less, string more)
// Throw Less Than Exception
//**********************************************************************
void CBaseObject::errorLessThan(string less, string more) {
  string sException = less;
  sException += ERROR_LESS_THAN;
  sException += more;
  throw sException;
}

//**********************************************************************
// void CBaseObject::errorLessThanEqualTo(string less, string more)
// Throw Less Than or Equal To Exception
//**********************************************************************
void CBaseObject::errorLessThanEqualTo(string less, string more) {
  string sException = less;
  sException += ERROR_LESS_EQUAL_TO;
  sException += more;
  throw sException;
}

//**********************************************************************
// void CBaseObject::errorGreaterThan(string more, string less)
// Throw greater than exception
//**********************************************************************
void CBaseObject::errorGreaterThan(string more, string less) {
  string sException = more;
  sException += ERROR_GREATER_THAN;
  sException += less;
  throw sException;
}

//**********************************************************************
// void CBaseObject::errorGreaterThanEqualTo(string more, string less)
// Throw Greater than or equal too exception
//**********************************************************************
void CBaseObject::errorGreaterThanEqualTo(string more, string less) {
  string sException = more;
  sException += ERROR_GREATER_EQUAL_TO;
  sException += less;
  throw sException;
}

//**********************************************************************
// void CBaseObject::errorNotEqual(string value1, string value2)
// Throw not equal exception
//**********************************************************************
void CBaseObject::errorNotEqual(string value1, string value2) {
  string sException = value1;
  sException += ERROR_EQUAL_NOT;
  sException += value1;
  throw sException;
}

//**********************************************************************
// void CBaseObject::errorEqualTo(string value1, string value2)
// Throw equal to exception
//**********************************************************************
void CBaseObject::errorEqualTo(string value1, string value2) {
  string sException = value1;
  sException += ERROR_EQUAL_TO;
  sException += value1;
  throw sException;
}

//**********************************************************************
// void CBaseObject::errorSupported(string value)
// Throw not supported error.
//**********************************************************************
void CBaseObject::errorSupported(string value) {
  string sException = value;
  sException += ERROR_SUPPORTED;
  throw sException;
}

//**********************************************************************
// CBaseObject::~CBaseObject()
// Default De-Constructor
//**********************************************************************
CBaseObject::~CBaseObject() {
  // Blank Pointers
  pConfig               = 0;
  pRuntimeController    = 0;
}
