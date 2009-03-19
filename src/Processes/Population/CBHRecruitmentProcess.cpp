//============================================================================
// Name        : CBHRecruitmentProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>
#include <limits>

// Local headers
#include "CBHRecruitmentProcess.h"
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
// CBHRecruitmentProcess::CBHRecruitmentProcess()
// Default constructor
//**********************************************************************
CBHRecruitmentProcess::CBHRecruitmentProcess() {
    // Default Vars
  pLayer          = 0;

  // Register allowed estimables
  registerEstimable(PARAM_R0, &dR0);
  registerEstimable(PARAM_R0, &dSigmaR);
  registerEstimable(PARAM_R0, &dSteepness);
  registerEstimable(PARAM_R0, &dRho);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_R0);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_AGES);
  pParameterList->registerAllowed(PARAM_STEEPNESS);
  pParameterList->registerAllowed(PARAM_SIGMA_R);
  pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_SSB);
  pParameterList->registerAllowed(PARAM_SSB_OFFSET);
  pParameterList->registerAllowed(PARAM_YCS_VALUES);
  pParameterList->registerAllowed(PARAM_YCS_YEARS);
  pParameterList->registerAllowed(PARAM_STANDARDISE_YCS_YEAR_RANGE);
  pParameterList->registerAllowed(PARAM_LAYER);

}

//**********************************************************************
// void CBHRecruitmentProcess::validate()
// Validate the process
//**********************************************************************
void CBHRecruitmentProcess::validate() {
  try {
    // Validate parent
    CProcess::validate();

    // Assign our variables
    dR0           = pParameterList->getDouble(PARAM_R0);
    dSteepness    = pParameterList->getDouble(PARAM_STEEPNESS,true,1.0);
    dSigmaR       = pParameterList->getDouble(PARAM_SIGMA_R,true,1.0);
    dRho          = pParameterList->getDouble(PARAM_RHO,true,0.0);
    sSSB          = pParameterList->getString(PARAM_SSB);
    iSSBOffset    = pParameterList->getInt(PARAM_SSB_OFFSET);
    sLayer        = pParameterList->getString(PARAM_LAYER, true, "");

    pParameterList->fillVector(vProportionList, PARAM_PROPORTIONS);
    pParameterList->fillVector(vAgesList, PARAM_AGES);
    pParameterList->fillVector(vYCSValues, PARAM_YCS_VALUES);
    pParameterList->fillVector(vYCSYears, PARAM_YCS_YEARS);
    pParameterList->fillVector(vStandardiseYCSYearRange, PARAM_STANDARDISE_YCS_YEAR_RANGE);
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vProportionList, PARAM_PROPORTIONS);
    pParameterList->fillVector(vAgesList, PARAM_AGES);

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

    //Check that exactly 2 values for vStandardiseYCSYearRange supplied
    if(vStandardiseYCSYearRange.size() != 2)
      CError::errorListSameSize(PARAM_STANDARDISE_YCS_YEAR_RANGE, "2"); //TODO: Better error message
      //TODO: vStandardiseYCSYearRange are in range Initial to Current years
      //TODO: set vStandardiseYCSYearRange to default to initial to current

    //Check that a value of YCSValues supplied for each YCSYear
    if(vYCSYears.size() != vYCSValues.size())
      CError::errorListSameSize(PARAM_YCS_YEARS, PARAM_YCS_VALUES);

    // Loop Through YCSYears and "add the offset" //TODO: YCS_YEARS and the SSBOffset ... needs more thought
    for (int i = 0; i < (int)vYCSYears.size(); ++i)
      vYCSYears[i] -= iSSBOffset;

    // Register our YCS as Estimable
    for (int i = 0; i < (int)vYCSValues.size(); ++i)
      registerEstimable(PARAM_YCS_VALUES, i, &vYCSValues[i]);

    // Loop Through YCS. Make Sure They Are >= 0.0
    foreach(double dValue, vYCSValues) {
      if (!CComparer::isNonNegative(dValue))
        CError::errorLessThan(PARAM_PROPORTIONS, PARAM_ZERO);
    }
    //Check SSBOffset is a non-negative int
    if (iSSBOffset < 0)
      CError::errorLessThan(PARAM_SSB_OFFSET, PARAM_ZERO);


  } catch (string Ex) {
    Ex = "CBHRecruitment.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBHRecruitmentProcess::build()
// Build the process
//**********************************************************************
void CBHRecruitmentProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Get our Layer
    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

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

  } catch (string Ex) {
    Ex = "CBHRecruitment.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBHRecruitmentProcess::execute()
// Execute this process
//**********************************************************************
void CBHRecruitmentProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base Execute
    CProcess::execute();

    // Setup Our Variables
    double dAmountPer = dR0; // TODO: multiply this by (a) YCS (b) YCS-MEAN (c) SR relationship

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
          pDiff->addValue(vCategoryIndex[k], vAgesIndex[k], (value * vProportionList[k]) );
      }
    }
#ifndef OPTIMIZE
  } catch(string Ex) {
    Ex = "CBHRecruitment.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CBHRecruitmentProcess::~CBHRecruitmentProcess()
// Destructor
//**********************************************************************
CBHRecruitmentProcess::~CBHRecruitmentProcess() {
}
