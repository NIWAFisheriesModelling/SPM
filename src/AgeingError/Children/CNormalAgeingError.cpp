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

  // Register our variables as estimable
  registerEstimable(PARAM_CV,&dCV);
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
    if (dCV <= 0)
      throw("CV must be a non-negative value"); //TODO: Better error message
    if (iK > iMaxAge)
      throw("k cannot be larger that the maximum age in the model"); //TODO: Better error message

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
// void CNormalAgeingError::getExpected(vector<double> &expected)
// Apply ageing error
//**********************************************************************
void CNormalAgeingError::getExpected(vector<double> &expected) {

  try {
    vector<double> vResult(expected.size(),0);

    for (int i = 0; i < (int)mMisMatrix.size(); ++i) {
      for (int j = 0; j < (int)mMisMatrix[i].size(); ++j) {
        vResult[j] += expected[i] * mMisMatrix[i][j];
      }
    }

    for (int i = 0; i < (int)expected.size(); ++i)
      expected[i] = vResult[i];

  } catch (string Ex) {
    Ex = "CNormalAgeingError.getExpected(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// CNormalAgeingError::~CNormalAgeingError()
// Destructor
//**********************************************************************
CNormalAgeingError::~CNormalAgeingError() {
}


