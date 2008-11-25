//============================================================================
// Name        : CBaseExecutableObject.cpp
// Author      : S.Rasmussen
// Date        : 31/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <sstream>

// Local Headers
#include "CBaseExecutableObject.h"

//**********************************************************************
// CBaseExecutableObject::CBaseExecutableObject()
// Default Constructor
//**********************************************************************
CBaseExecutableObject::CBaseExecutableObject(CBaseExecutableObject *Object)
: CBaseBuildableObject(Object) {

  // Assign Our Variables
  pWorld               = CWorld::Instance();
  pBase                = 0;
  iWorldWidth          = -1;
  iWorldHeight         = -1;
}

//**********************************************************************
// void CBaseExecutableObject::validate()
// Validate
//**********************************************************************
void CBaseExecutableObject::validate() {
  try {
    // Assign
    iWorldWidth          = pWorld->getWidth();
    iWorldHeight         = pWorld->getHeight();

    // Validate
    if (sLabel == "")
      errorMissing(PARAM_LABEL);

  } catch (string Ex) {
    Ex = "CBaseExecutableObject.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CBaseExecutableObject::lngamma(double t)
//
//**********************************************************************
double CBaseExecutableObject::lnGamma(double t) {
  int j;
  double x,y,tmp,ser;
  double cof[6] = {76.18009172947146,-86.50532032941677,24.01409824083091,-1.231739572450155,0.1208650973866179e-2,-0.5395239384953e-5};
  y = x = t;
  tmp = x + 5.5 - (x + 0.5) * log(x + 5.5);
  ser = 1.000000000190015;
  for (j=0;j<=5;j++)
    ser += (cof[j] / ++y);
  return(log(2.5066282746310005 * ser / x) - tmp);
}

//**********************************************************************
// double CBaseExecutableObject::lnFactorial(double t)
//
//**********************************************************************
double CBaseExecutableObject::lnFactorial(double t) {
  return(lnGamma(t+1.0));
}

//**********************************************************************
// double CBaseExecutableObject::zerofun(double x, double delta)
//
//**********************************************************************
double CBaseExecutableObject::zeroFun(double x, double delta) {
  if (x>=delta){
    return x;
  } else {
    return delta/(2-(x/delta));
  }
}

//**********************************************************************
// string CBaseExecutableObject::convertDouble(double value)
// Convert Double to String
//**********************************************************************
string CBaseExecutableObject::convertDouble(double value) {
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

//**********************************************************************
// CBaseExecutableObject::~CBaseExecutableObject()
// Default De-Constructor
//**********************************************************************
CBaseExecutableObject::~CBaseExecutableObject() {
  // Clear Pts
  pBase  = 0;
}
