//============================================================================
// Name        : CConstantRecruitmentProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Global headers
#include <iostream>
#include <limits>

// Local Headers
#include "CConstantRecruitmentProcess.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CComparer.h"

// Using
using std::cout;
using std::endl;
using std::numeric_limits;

//**********************************************************************
// CConstantRecruitmentProcess::CConstantRecruitmentProcess(CConstantRecruitmentProcess *Process)
// Default Constructor
//**********************************************************************
CConstantRecruitmentProcess::CConstantRecruitmentProcess() {
  // Default Vars
  pLayer          = 0;

  // Register allowed estimables
  registerEstimable(PARAM_R0, &dR0);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_R0);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_AGE);
  pParameterList->registerAllowed(PARAM_LAYER);

}

//**********************************************************************
// void CConstantRecruitmentProcess::validate()
// Validate Our Parameters
//**********************************************************************
void CConstantRecruitmentProcess::validate() {
  try {
    // Base Validation
    CProcess::validate();

    // Populate our Variables
    dR0         = pParameterList->getDouble(PARAM_R0);
    dAge        = pParameterList->getInt(PARAM_AGE);
    sLayer      = pParameterList->getString(PARAM_LAYER, true, "");

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vProportionList, PARAM_PROPORTIONS);

    // The 2 Vectors must be same size
    unsigned iCategorySize    = vCategoryList.size();
    unsigned iProportionSize  = vProportionList.size();

    if (iCategorySize != iProportionSize)
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_PROPORTION);

    // Register our Proportions as Estimable
    for (int i = 0; i < (int)vProportionList.size(); ++i)
      registerEstimable(PARAM_PROPORTION, i, &vProportionList[i]);

    // Loop Through Proportions. Make Sure They Equal 1.0
    double dRunningTotal = 0.0;
    foreach(double Prop, vProportionList) {
      dRunningTotal += Prop;
    }
    // See If It is close enough to 1.0
    if (!CComparer::isEqual(dRunningTotal, 1.0))
      CError::errorNotEqual(PARAM_PROPORTIONS, PARAM_ONE);

  } catch(string &Ex) {
    Ex = "CRecruitmentProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantRecruitmentProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CConstantRecruitmentProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Get our Layer
    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Populate Our Age Index
    dAgeIndex = pWorld->getColIndexForAge(dAge);

    // Validate our Vectors are all same size
    if (vProportionList.size() != vCategoryIndex.size())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_PROPORTIONS);

  } catch(string &Ex) {
    Ex = "CRecruitmentProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantRecruitmentProcess::execute()
// Execute
//**********************************************************************
void CConstantRecruitmentProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base Execute
    CProcess::execute();

    // Setup Our Variables
    double dAmountPer = dR0;

    if (pLayer != 0) {
      double dTotal = 0.0;

      for (int i = 0; i < iWorldHeight; ++i)
        for (int j = 0; j < iWorldWidth; ++j)
          dTotal += pLayer->getValue(i, j);

      if (!CComparer::isZero(dTotal))
        dAmountPer /= dTotal;
    } else
      dAmountPer /= pWorld->getEnabledSquareCount();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        // Check if this square is enabled or not.
        if (!pBaseSquare->getEnabled())
          continue;

        double value = dAmountPer;
        if (pLayer != 0)
          value *= pLayer->getValue(i, j);

        pDiff       = pWorld->getDifferenceSquare(i, j);

        // Loop Through the Categories and Ages we have and Recruit
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k)
          pDiff->addValue(vCategoryIndex[k], dAgeIndex, (value * vProportionList[k]) );
      }
    }
#ifndef OPTIMIZE
  } catch(string &Ex) {
    Ex = "CRecruitmentProcess.execute(" + getLabel() +")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CConstantRecruitmentProcess::~CConstantRecruitmentProcess()
// Default De-Constructor
//**********************************************************************
CConstantRecruitmentProcess::~CConstantRecruitmentProcess() {
  vProportionList.clear();
}
