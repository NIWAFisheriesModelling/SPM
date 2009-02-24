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
  bDependsOnLayer = false;

  // Register allowed estimables
  registerEstimable(PARAM_R0, &dR0);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_R0);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_AGES);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_LAYER_MIN);
  pParameterList->registerAllowed(PARAM_LAYER_MAX);
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
    dR0       = pParameterList->getDouble(PARAM_R0);
    dLayerMin = pParameterList->getDouble(PARAM_LAYER_MIN, true, -numeric_limits<double>::max());
    dLayerMax = pParameterList->getDouble(PARAM_LAYER_MAX, true, numeric_limits<double>::max());

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vProportionList, PARAM_PROPORTIONS);
    pParameterList->fillVector(vAgesList, PARAM_AGES);

    // layer_max and layer_min must be assigned in pairs
    bool bHasLayerMin = pParameterList->hasParameter(PARAM_LAYER_MIN);
    bool bHasLayerMax = pParameterList->hasParameter(PARAM_LAYER_MAX);

    if ((bHasLayerMin) && (!bHasLayerMax))
      CError::errorMissing(PARAM_LAYER_MAX);
    else if ( (!bHasLayerMin) && (bHasLayerMax))
      CError::errorMissing(PARAM_LAYER_MIN);

    // The 3 Vectors must be same size
    unsigned iCategorySize    = vCategoryList.size();
    unsigned iProportionSize  = vProportionList.size();
    unsigned iAgesSize        = vAgesList.size();

    if (iCategorySize != iProportionSize)
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_PROPORTION);
    else if (iCategorySize != iAgesSize)
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_AGES);

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

  } catch(string Ex) {
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

    // Populate Our Ages Index
    if (vAgesIndex.size() <= 0) {
      foreach(int Age, vAgesList) {
        vAgesIndex.push_back(pWorld->getColIndexForAge(Age));
      }
    }

    // Validate our Vectors are all same size
    if (vAgesIndex.size() != vCategoryIndex.size())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_AGES);
    if (vAgesIndex.size() != vProportionList.size())
      CError::errorListSameSize(PARAM_AGES, PARAM_PROPORTIONS);

  } catch(string Ex) {
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
    double        dAmountPer    = dR0;

    // Now, Divide That By The Number of WorldSquares We will be updating
    if (bDependsOnLayer)
      dAmountPer /= iNumberOfValidLayerSpots;
    else
      dAmountPer /= pWorld->getEnabledSquareCount();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        // Check if this square is enabled or not.
        if (!pBaseSquare->getEnabled())
          continue;

        if (bDependsOnLayer) {
          if ( (dLayerMax == numeric_limits<double>::max()) && (!pLayer->checkSpace(i,j)) )
            continue;
          else if (!pLayer->checkSpace(i, j, dLayerMin, dLayerMax))
            continue;
        }

        pDiff       = pWorld->getDifferenceSquare(i, j);

        // Loop Through the Categories and Ages we have and Recruit
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k)
          pDiff->addValue(vCategoryIndex[k], vAgesIndex[k], (dAmountPer * vProportionList[k]) );
      }
    }
#ifndef OPTIMIZE
  } catch(string Ex) {
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
  vAgesList.clear();
  vAgesIndex.clear();
}
