//============================================================================
// Name        : CAgeingError.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAgeingError.h"

//**********************************************************************
// CAgeingError::CAgeingError()
// Default Constructor
//**********************************************************************
CAgeingError::CAgeingError() {
}

//**********************************************************************
// void CLayer::validate()
// Validate
//**********************************************************************
void CAgeingError::validate() {
  try {

    // Get Variables from World
    CWorld *pWorld    = CWorld::Instance();
    iMinAge           = pWorld->getMinAge();
    iMaxAge           = pWorld->getMaxAge();
    bAgePlusGroup     = pWorld->getAgePlusGroup();
    iNAges            = iMaxAge - iMinAge + 1;

    vector<double> vTemp(iNAges,0);

    for (int i = 0; i < iNAges; ++i) {
      mMisMatrix.push_back(vTemp);
    }

    for (int i = 0; i < iNAges; ++i) {
      for (int j = 0; j < iNAges; ++j) {
        if(i==j)
          mMisMatrix[i][j] = 1;
      }
    }

  } catch (string Ex) {
    Ex = "CAgeingError.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CAgeingError::~CAgeingError()
// Destructor
//**********************************************************************
CAgeingError::~CAgeingError() {
}
