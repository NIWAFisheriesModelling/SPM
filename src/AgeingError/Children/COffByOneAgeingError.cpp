//============================================================================
// Name        : COffByOneAgeingError.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "COffByOneAgeingError.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// COffByOneAgeingError::COffByOneAgeingError()
// Default Constructor
//**********************************************************************
COffByOneAgeingError::COffByOneAgeingError() {

    // Register user allowed parameters
    pParameterList->registerAllowed(PARAM_P1);
    pParameterList->registerAllowed(PARAM_P2);
    pParameterList->registerAllowed(PARAM_K);

}

//**********************************************************************
// voidCOffByOneAgeingError::validate()
// Validate the ageing error
//**********************************************************************
void COffByOneAgeingError::validate() {
  try {
    // Base
    CAgeingError::validate();

    // Get our variables
    dP1      = pParameterList->getDouble(PARAM_P1);
    dP2      = pParameterList->getDouble(PARAM_P2);
    iK       = pParameterList->getInt(PARAM_K,true,0);

    // TODO: Complete validation - error messages need to be better phrased
    if (iK < iMinAge)
      throw("k needs to be a value at least the same as the minimum age in the model"); //TODO: Better error message
    if (iK > iMaxAge)
      throw("k cannot be larger that the maximum age in the model"); //TODO: Better error message
    if ((dP1+dP2) > 1.0)
       throw("The sum of p1 and p2 combined must be less than 1.0"); //TODO: Better error message

    // Register our variables as estimable
    //registerEstimable(PARAM_P1,dP1);
    //registerEstimable(PARAM_P2,dP2);

  } catch (string Ex) {
    Ex = "COffByOneAgeingError.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCOffByOneAgeingError::build()
// Validate the ageing error
//**********************************************************************
void COffByOneAgeingError::build() {

  try {
    mMisMatrix[0][0] = 1 - dP2;
    mMisMatrix[0][1] = dP2;

    for (int i = 1; i < iNAges; ++i) {
      mMisMatrix[i][i-1] = 1 - dP2;
      mMisMatrix[i][i]   = 1 - (dP1 + dP2);
      mMisMatrix[i][i+1] = dP2;
    }

    mMisMatrix[iNAges][iNAges - 1] = dP1;

    if(bAgePlusGroup) {
      mMisMatrix[iNAges][iNAges] = 1 - dP1;
    } else {
      mMisMatrix[iNAges][iNAges] = 1 - (dP1 + dP2);
    }

    if (iK > 0) {
      for (int i = 0; i < iK; ++i) {
        for(int j = 0; j < iK; ++j) {
          mMisMatrix[i][j] <- 0;
        }
        mMisMatrix[i][i]<-1;
      }
    }
  } catch (string Ex) {
    Ex = "COffByOneAgeingError.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// COffByOneAgeingError::execute()
// Apply ageing error
//**********************************************************************
void COffByOneAgeingError::execute(vector<double> vExpected) {

  try {
    vector<double> vResult(vExpected.size(),0);

    for (int i = 0; i < (int)mMisMatrix.size(); ++i) {
      for (int j = 0; j < (int)mMisMatrix[i].size(); ++j) {
        vResult[j] += vExpected[i] * mMisMatrix[i][j];
      }
    }

    for (int i = 0; i < (int)vExpected.size(); ++i)
      vExpected[i] = vResult[i];

  } catch (string Ex) {
    Ex = "COffByOneAgeingError.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// COffByOneAgeingError::~COffByOneAgeingError()
// Destructor
//**********************************************************************
COffByOneAgeingError::~COffByOneAgeingError() {
}
