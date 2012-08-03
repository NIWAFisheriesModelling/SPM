//============================================================================
// Name        : CCategoricalPreferenceFunction.cpp
// Author      : A.Dunn
// Date        : 20/04/2012
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CCategoricalPreferenceFunction.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CCategoricalPreferenceFunction::CCategoricalPreferenceFunction()
// Default Constructor
//**********************************************************************
CCategoricalPreferenceFunction::CCategoricalPreferenceFunction() {

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORY_VALUES);
  pParameterList->registerAllowed(PARAM_CATEGORY_LABELS);
}

//**********************************************************************
// void CCategoricalPreferenceFunction::validate()
// Validate
//**********************************************************************
void CCategoricalPreferenceFunction::validate() {
  try {

    // Assign local variables
    pParameterList->fillVector(vLabels, PARAM_CATEGORY_LABELS);
    pParameterList->fillVector(vValues, PARAM_CATEGORY_VALUES);

    // Validate parent
    CPreferenceFunction::validate();

    //Local validation
    if (vValues.size() != vLabels.size())
      CError::errorListSameSize(PARAM_CATEGORY_VALUES, PARAM_CATEGORY_LABELS);
    // TODO:
    //       Validate that the layer has a number of discrete character values that exactly match CATEGORY_LABELS
    // Check For Duplicate Labels.

    // Register estimables
    for (int i = 0; i < (int)vValues.size(); ++i)
      registerEstimable(PARAM_CATEGORY_VALUES, i, &vValues[i]);


  } catch (string &Ex) {
    Ex = "CCategoricalPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoricalPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CCategoricalPreferenceFunction::build() {
  try {

    // Get our Layer Pointer
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayer = pLayerManager->getStringLayer(sLayerName);

  } catch (string &Ex) {
    Ex = "CCategoricalPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CCategoricalPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CCategoricalPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif
    //TODO: Scott to check code for efficiency
    //Function should identify the label, and then return the corresponding value
    sLayerValue = pLayer->getValue(TRIndex, TCIndex);

    for (int i = 0; i < (int)vLabels.size(); i++) {
      if(vLabels[i] == sLayerValue) {
        dRet = vValues[i];
        break;
      }
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CCategoricalPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CCategoricalPreferenceFunction::~CCategoricalPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CCategoricalPreferenceFunction::~CCategoricalPreferenceFunction() {
}
