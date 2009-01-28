//============================================================================
// Name        : CCachedSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CCachedSelectivity.h"

//**********************************************************************
// CCachedSelectivity::CCachedSelectivity()
// Default constructor
//**********************************************************************
CCachedSelectivity::CCachedSelectivity() {
}

//**********************************************************************
// void CCachedSelectivity::build()
// Build the selectivity
//**********************************************************************
void CCachedSelectivity::build() {
  try {
    // Call Rebuild
    rebuild();

  } catch (string Ex) {
    Ex = "CCachedSelectivity.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCachedSelectivity::rebuild()
// Rebuild the selectivity
//**********************************************************************
void CCachedSelectivity::rebuild() {
  try {
    vResults.clear();

    // Get Age Range
    int iMinAge = pWorld->getMinAge();
    int iTop    = pWorld->getMaxAge() - iMinAge;

    // Build Vector of our Results
    for (int i = 0; i <= iTop; ++i) {
      vResults.push_back(calculateResult(i+iMinAge));
    }
  } catch (string Ex) {
    Ex = "CCachedSelectivity.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CCachedSelectivity::getResult(int index)
// Get the result from our Cache
//**********************************************************************
double CCachedSelectivity::getResult(int index) {
  return vResults[index];
}

//**********************************************************************
// CCachedSelectivity::~CCachedSelectivity()
// Destructor
//**********************************************************************
CCachedSelectivity::~CCachedSelectivity() {
}
