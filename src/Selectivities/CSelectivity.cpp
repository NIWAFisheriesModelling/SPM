//============================================================================
// Name        : CSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CSelectivity.h"

//**********************************************************************
// CSelectivity::CSelectivity(CSelectivity *Selectivity = 0);
// Default Constructor
//**********************************************************************
CSelectivity::CSelectivity(CSelectivity *Selectivity)
: CBaseExecutableObject(Selectivity) {

  // Vars
  pWorld            = CWorld::Instance();

}

//**********************************************************************
// void CSelectivity::validate()
// Validate
//**********************************************************************
void CSelectivity::validate() {
  try {
    // Base
    CBaseExecutableObject::validate();

  } catch (string Ex) {
    Ex = "CSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSelectivity::build()
// build
//**********************************************************************
void CSelectivity::build() {
  try {
    rebuild();

  } catch (string Ex) {
    Ex = "CSelectivity.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSelectivity::rebuild()
// Rebuild
//**********************************************************************
void CSelectivity::rebuild() {
#ifndef OPTIMISE
  try {
#endif

    // Have we done this before?
    vResults.clear();

    // Get Age Range
    int iMinAge = pWorld->getMinAge();
    int iTop    = pWorld->getMaxAge() - iMinAge;

    // Build Vector of our Results
    for (int i = 0; i <= iTop; ++i) {
      vResults.push_back(calculateResult(i+iMinAge));
    }

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CSelectivity.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// double CSelectivity::getResult(int Index)
// Get our Result
//**********************************************************************
double CSelectivity::getResult(int Index) {
#ifndef OPTIMISE
  try {
    if (Index > (int)vResults.size())
      throw string("Invalid Index");
#endif

    return vResults[Index];

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CSelectivity::~CSelectivity()
// Default De-Constructor
//**********************************************************************
CSelectivity::~CSelectivity() {
  vResults.clear();
}
