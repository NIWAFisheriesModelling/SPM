//============================================================================
// Name        : CAbundanceObservation.cpp
// Author      : S.Rasmussen
// Date        : 4/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CAbundanceObservation.h"
#include "../../Catchabilities/CCatchabilityManager.h"
#include "../../Catchabilities/CCatchability.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CConvertor.h"

//**********************************************************************
// CAbundanceObservation::CAbundanceObservation()
// Default Constructor
//**********************************************************************
CAbundanceObservation::CAbundanceObservation() {

  // Variables
  sQ              = "";
  pQ              = 0;
  dCVProcessError = 0.0;
  dSigma          = 0.0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_Q);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_OBS);
  pParameterList->registerAllowed(PARAM_CV);
  pParameterList->registerAllowed(PARAM_DIST);
}

//**********************************************************************
// string CAbundanceObservation::getProportionKey(int index)
// Get the proportion key for an index
//**********************************************************************
string CAbundanceObservation::getProportionKey(int index) {

  map<string, double>::iterator ptr = mvProportionMatrix.begin();
  for (int i = 0; i < index; ++i)
    ptr++;
  return (*ptr).first;
}

//**********************************************************************
// double CAbundanceObservation::getProportionValue(string key)
// Get The Proportion value for a key
//**********************************************************************
double CAbundanceObservation::getProportionValue(string key) {
  return mvProportionMatrix[key];
}

//**********************************************************************
// string CAbundanceObservation::getCVKey(int index)
// Get The CV Key for Index
//**********************************************************************
string CAbundanceObservation::getCVKey(int index) {

  map<string, double>::iterator ptr = mvCVMatrix.begin();
  for (int i = 0; i < index; ++i)
    ptr++;
  return (*ptr).first;
}

//**********************************************************************
// double CAbundanceObservation::getCVValue(string key)
// Get the CV Value for Key
//**********************************************************************
double CAbundanceObservation::getCVValue(string key) {
  return mvCVMatrix[key];
}

//**********************************************************************
// void CAbundanceObservation::validate()
// validate
//**********************************************************************
void CAbundanceObservation::validate() {
  try {
    // Base Validate
    CObservation::validate();

    // Get our Parameters
    sQ          = pParameterList->getString(PARAM_Q);
    sLayer      = pParameterList->getString(PARAM_LAYER);
    sDist       = pParameterList->getString(PARAM_DIST);

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    if ((vOBS.size() % 2) != 0)
      CError::errorPairs(PARAM_OBS);

    for (int i = 0; i < (int)vOBS.size(); i+=2)
      mvProportionMatrix[vOBS[i]] = CConvertor::stringToDouble(vOBS[i+1]);

    // Get our CV
    vector<string> vCV;
    pParameterList->fillVector(vCV, PARAM_CV);

    if ((vCV.size() % 2) != 0)
      CError::errorPairs(PARAM_CV);

    for (int i = 0; i < (int)vCV.size(); i+=2)
      mvCVMatrix[vCV[i]] = CConvertor::stringToDouble(vCV[i+1]);

    // Validate our cv's to make sure we have the right amount for our
    // Observations
    bool bMatch = false;
    map<string, double>::iterator mCVPtr      = mvCVMatrix.begin();
    map<string, double>::iterator mPropPtr    = mvProportionMatrix.begin();

    while (mCVPtr != mvCVMatrix.end()) {
      // Reset Vars
      bMatch      = false;
      mPropPtr    = mvProportionMatrix.begin();

      while (mPropPtr != mvProportionMatrix.end()) {
        if ( (*mPropPtr).first == (*mCVPtr).first ) {
          bMatch = true;
          break;
        }
        mPropPtr++;
      }

      if (!bMatch)
        CError::errorNoMatch(PARAM_CV, (*mCVPtr).first, PARAM_OBS);

      mCVPtr++;
    }

  } catch (string Ex) {
    Ex = "CAbundanceObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAbundanceObservation::build()
// build
//**********************************************************************
void CAbundanceObservation::build() {
  try {
    // Base build
    CObservation::build();

    CCatchabilityManager *pQManager = CCatchabilityManager::Instance();
    pQ = pQManager->getCatchability(sQ);

  } catch (string Ex) {
    Ex = "CAbundanceObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAbundanceObservation::execute()
// Execute
//**********************************************************************
void CAbundanceObservation::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Variables
             dScore           = 0.0;
    double   dExpectedTotal   = 0.0;

    // Loop Through Obs
    map<string, double>::iterator mPropPtr = mvProportionMatrix.begin();
    while (mPropPtr != mvProportionMatrix.end()) {
      // Reset Vars
      dExpectedTotal = 0.0;


      // Loop Through Each Square in our Layer
      for (int i = 0; i < pLayer->getHeight(); ++i) {
        for (int j = 0; j < pLayer->getWidth(); ++j) {
          // Check if this matches the key
          if (pLayer->getValue(i, j) == (*mPropPtr).first) {
            // Get our Square and check if it's enabled
            pBaseSquare = pWorld->getBaseSquare(i, j);
            if (!pBaseSquare->getEnabled())
              continue;

            int iColCount = (pWorld->getMaxAge()+1) - pWorld->getMinAge();

            for (int k = 0; k < iColCount; ++k) {
              for (int l = 0; l < (int)vCategories.size(); ++l) {
                double dSelectResult = vSelectivities[l]->getResult(k);
                dExpectedTotal += dSelectResult * pBaseSquare->getPopulationInCategoryForAge(k, l);
              }
            }
          }
        }
      }

      // Note: dExpectedTotal is total number of fish the model has for that
      // Proportion Label across all squares in that layer where that
      // label is used.
      dExpectedTotal *= pQ->getQ();

      double dCV = mvCVMatrix[(*mPropPtr).first];
      //Add in process error if defined
      if(dCVProcessError>0) dCV = sqrt(dCV*dCV + dCVProcessError*dCVProcessError);

      dSigma = sqrt(log(1+ dCV*dCV));
      double dTemp = log((*mPropPtr).second / CMath::zeroFun(dExpectedTotal,DELTA)) / dSigma + 0.5*dSigma;
      dScore += log(dSigma) + 0.5 * dTemp * dTemp;

      mPropPtr++;
    }

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CAbundanceObservation.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAbundanceObservation::~CAbundanceObservation()
// Default De-Constructor
//**********************************************************************
CAbundanceObservation::~CAbundanceObservation() {
}
