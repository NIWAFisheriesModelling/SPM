//============================================================================
// Name        : CKnifeEdgeSelectivity.cpp
// Author      : A. Dunn
// Date        : 12/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CKnifeEdgeSelectivity.h"

//**********************************************************************
// CKnifeEdgeSelectivity::CKnifeEdgeSelectivity(CKnifeEdgeSelectivity *Selectivity = 0)
// Default Constructor
//**********************************************************************
CKnifeEdgeSelectivity::CKnifeEdgeSelectivity(CKnifeEdgeSelectivity *Selectivity)
: CSelectivity(Selectivity) {

  // Variables
  dC    = 0;

  registerEstimable(PARAM_C, &dC);

  // Copy Construct
  if (Selectivity != 0) {
    dC    = Selectivity->getC();
  }
}

//**********************************************************************
// void CKnifeEdgeSelectivity::validate()
// validate
//**********************************************************************
void CKnifeEdgeSelectivity::validate() {
  try {
    // Nothing to do
  } catch (string Ex) {
    Ex = "CKnifeedgeSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CKnifeEdgeSelectivity::calculateResult(int Age)
// calculate results for our Vector
//**********************************************************************
double CKnifeEdgeSelectivity::calculateResult(int Age) {
  try {
    throw string(ERROR_SUPPORTED_FUNCTION);
  } catch (string Ex) {
    Ex = "CKnifeedgeSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CKnifeEdgeSelectivity::getResult(int Param)
// get Result
//**********************************************************************
double CKnifeEdgeSelectivity::getResult(int Param) {
#ifndef OPTIMISE
  try {
#endif
    // Get the column Index for the passed in Age
    Param = pWorld->getMinAge() + Param;

    if(Param >= dC)
      return (1.0);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CKnifeedgeSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
  return 0.0;
}

//**********************************************************************
// CKnifeEdgeSelectivity::~CKnifeEdgeSelectivity()
// Default De-Constructor
//**********************************************************************
CKnifeEdgeSelectivity::~CKnifeEdgeSelectivity() {
}
