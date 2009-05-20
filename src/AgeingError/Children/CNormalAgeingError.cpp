//============================================================================
// Name        : CNormalAgeingError.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CNormalAgeingError.h"

//**********************************************************************
// CNormalAgeingError::CNormalAgeingError()
// Default Constructor
//**********************************************************************
CNormalAgeingError::CNormalAgeingError() {

    // Register user allowed parameters
    pParameterList->registerAllowed(PARAM_CV);
    pParameterList->registerAllowed(PARAM_K);

}

//**********************************************************************
// voidCNormalError::validate()
// Validate the ageing error
//**********************************************************************
void CNormalAgeingError::validate() {
  try {
    // Base
    CAgeingError::validate();

    // Get our variables
    dCV      = pParameterList->getDouble(PARAM_CV);
    iK       = pParameterList->getInt(PARAM_K,true,0);

    // TODO: Complete validation - error messages need to be better phrased
    if (iK < iMinAge)
      throw("k needs to be a value at least the same as the minimum age in the model"); //TODO: Better error message
    if (iK > iMaxAge)
      throw("k cannot be larger that the maximum age in the model"); //TODO: Better error message

    // Register our variables as estimable
    //registerEstimable(PARAM_P1,dCV);

  } catch (string Ex) {
    Ex = "CNormalError.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCNormalAgeingError::build()
// Validate the ageing error
//**********************************************************************
void CNormalAgeingError::build() {

  try {

  } catch (string Ex) {
    Ex = "CNormalAgeingError.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNormalAgeingError::execute()
// Apply ageing error
//**********************************************************************
void CNormalAgeingError::execute(vector<double> vExpected) {

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
    Ex = "CNormalAgeingError.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// CNormalAgeingError::~CNormalAgeingError()
// Destructor
//**********************************************************************
CNormalAgeingError::~CNormalAgeingError() {
}
