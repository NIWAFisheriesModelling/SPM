//============================================================================
// Name        : CNormalPrior.cpp
// Author      : A.Dunn
// Date        : 13/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNormalPrior.h"

//**********************************************************************
// CNormalPrior::CNormalPrior(CNormalPrior *Prior = 0)
// Default Constructor
//**********************************************************************
CNormalPrior::CNormalPrior(CNormalPrior *Prior)
: CPrior(Prior) {

  // Vars
  dMu     = 0.0;
  dCv     = 0.0;

  // Copy Construct
  if (Prior != 0) {
    dMu   = Prior->getMu();
    dCv   = Prior->getCv();
  }
}

//**********************************************************************
// void CNormalPrior::validate()
// validate
//**********************************************************************
void CNormalPrior::validate() {
  try {

  } catch (string Ex) {
    Ex = "CNormalPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalPrior::getResult(double Param)
// get Result
//**********************************************************************
double CNormalPrior::getResult(double Param) {
#ifndef OPTIMISE
  try {
#endif

    return 0.5 * ((Param-dMu)/(dCv*dMu)) * ((Param-dMu)/(dCv*dMu));

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CNormalPrior.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CNormalPrior::~CNormalPrior()
// Default De-Constructor
//**********************************************************************
CNormalPrior::~CNormalPrior() {
}
