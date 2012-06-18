//============================================================================
// Name        : CEstimate.h
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// $Date: 2012-06-08 17:29:15 +1200 (Fri, 08 Jun 2012) $
//============================================================================

// Headers
#include "CEstimateInfo.h"

//**********************************************************************
// CEstimateInfo::CEstimateInfo()
// Default Constructor
//**********************************************************************
CEstimateInfo::CEstimateInfo() {

}

//**********************************************************************
// CEstimateInfo::~CEstimateInfo()
// Destructor
//**********************************************************************
CEstimateInfo::~CEstimateInfo() {
}

//**********************************************************************
// void CEstimateInfo::fillSameVector(vector<string> &sames)
// Fill a Vector with our "Same" parameters
//**********************************************************************
void CEstimateInfo::fillSameVector(vector<string> &sames) {
  sames.assign(vSameList.begin(), vSameList.end());
}

//**********************************************************************
// void CEstimateInfo::validate()
// Validate the parameters loaded by the configuration file
//**********************************************************************
void CEstimateInfo::validate() {
  try {
//    // Base
//    CBaseBuild::validate();
//
//    // Populate our Variables
//    sParameter        = pParameterList->getString(PARAM_PARAMETER);
//    dLowerBound       = pParameterList->getDouble(PARAM_LOWER_BOUND);
//    dUpperBound       = pParameterList->getDouble(PARAM_UPPER_BOUND);
//    sPrior            = pParameterList->getString(PARAM_PRIOR, true, "");
//    iEstimationPhase  = pParameterList->getInt(PARAM_ESTIMATION_PHASE, true, 1);
//
//    pParameterList->fillVector(vSameList, PARAM_SAME, true);
//
//    // Validate
//    if (dUpperBound < dLowerBound)
//      CError::errorLessThan(PARAM_UPPER_BOUND, PARAM_LOWER_BOUND);
//
//    // Check For Duplicate Sames
//    map<string, int>  mSames;
//    foreach(string Same, vSameList) {
//      mSames[Same]++;
//      if (mSames[Same] > 1)
//        CError::errorDuplicate(PARAM_SAME, Same);
//    }

  } catch (string &Ex) {
    Ex = "CEstimateInfo.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimateInfo::build()
// Build the CEstimate objects from this object
//**********************************************************************
void CEstimateInfo::build() {

}
