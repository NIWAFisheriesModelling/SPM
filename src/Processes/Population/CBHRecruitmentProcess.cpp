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
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../DerivedQuantities/CDerivedQuantityManager.h"
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
  pTimeStepManager = CTimeStepManager::Instance();
    // Default Vars
  pLayer          = 0;
  // Register allowed estimables
  registerEstimable(PARAM_R0, &dR0);
  registerEstimable(PARAM_SIGMA_R, &dSigmaR);
  registerEstimable(PARAM_STEEPNESS, &dSteepness);
  registerEstimable(PARAM_RHO, &dRho);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_R0);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_AGE);
  pParameterList->registerAllowed(PARAM_STEEPNESS);
  pParameterList->registerAllowed(PARAM_SIGMA_R);
  pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_SSB);
  pParameterList->registerAllowed(PARAM_SSB_OFFSET);
  pParameterList->registerAllowed(PARAM_YCS_VALUES);
  pParameterList->registerAllowed(PARAM_STANDARDISE_YCS_YEARS);
  pParameterList->registerAllowed(PARAM_LAYER);

}

//**********************************************************************
// void CBHRecruitmentProcess::validate()
// Validate the process
//**********************************************************************
void CBHRecruitmentProcess::validate() {
  try {

    // Assign our variables
    dR0           = pParameterList->getDouble(PARAM_R0);
    iAge          = pParameterList->getInt(PARAM_AGE);
    dSteepness    = pParameterList->getDouble(PARAM_STEEPNESS,true,1.0);
    dSigmaR       = pParameterList->getDouble(PARAM_SIGMA_R,true,1.0);
    dRho          = pParameterList->getDouble(PARAM_RHO,true,0.0);
    sSSB          = pParameterList->getString(PARAM_SSB);
    iSSBOffset    = pParameterList->getInt(PARAM_SSB_OFFSET);
    sLayer        = pParameterList->getString(PARAM_LAYER, true, "");

    pParameterList->fillVector(vProportions, PARAM_PROPORTIONS);
    pParameterList->fillVector(vYCSValues, PARAM_YCS_VALUES);
    pParameterList->fillVector(vStandardiseYCSYears, PARAM_STANDARDISE_YCS_YEARS, true);
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);

    // Validate parent
    CProcess::validate();

    // local validation
    // iAge must be a valid age
    if (iAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_AGE,PARAM_MIN_AGE);
    if (iAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_AGE,PARAM_MAX_AGE);

    // The 2 Vectors must be same size
    if (getCategoryCount() != (int)vProportions.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_PROPORTIONS);

    // Register our Proportions as Estimable
    for (int i = 0; i < (int)vProportions.size(); ++i)
      registerEstimable(PARAM_PROPORTIONS, i, &vProportions[i]);

    // Loop Through Proportions. Make Sure They Equal 1.0
    double dRunningTotal = 0.0;
    foreach(double Prop, vProportions) {
      dRunningTotal += Prop;
    }
    // See If It is close enough to 1.0
    if (!CComparer::isEqual(dRunningTotal, 1.0))
      CError::errorNotEqual(PARAM_PROPORTIONS, PARAM_ONE);

    //***************************************************
    // Validate the Standardise YCS Year Range
    if(vStandardiseYCSYears.size() == 0) {
      for (int i = pWorld->getInitialYear(); i < (pWorld->getCurrentYear() + 1); ++i ) {
        vStandardiseYCSYears.push_back(i);
      }
    }

    if(vStandardiseYCSYears.size() > 1) {
      for (int i = 1; i < (int)vStandardiseYCSYears.size(); ++i ) {
        if(vStandardiseYCSYears[i-1] >= vStandardiseYCSYears[i] )
          CError::error(PARAM_YCS_YEARS + string(" is not in numeric order"));
      }
    }

    if (vStandardiseYCSYears[0] < pWorld->getInitialYear())
      CError::errorLessThan(PARAM_STANDARDISE_YCS_YEARS, PARAM_INITIAL_YEAR);
    if (vStandardiseYCSYears[vStandardiseYCSYears.size()-1] > pWorld->getCurrentYear())
      CError::errorGreaterThan(PARAM_STANDARDISE_YCS_YEARS, PARAM_CURRENT_YEAR);

    //Check that a value of YCSValues supplied for each YCSYear
    if(vYCSValues.size() != (pWorld->getCurrentYear() - pWorld->getInitialYear() + 1))
      CError::errorListSameSize(PARAM_YCS_VALUES, string("model years"));

    // Register our YCS as Estimable
    for (int i = 0; i < (int)vYCSValues.size(); ++i)
      registerEstimable(PARAM_YCS_VALUES, i, &vYCSValues[i]);

    // Loop Through YCS. Make Sure They Are >= 0.0
    foreach(double dValue, vYCSValues) {
      if (!CComparer::isNonNegative(dValue))
        CError::errorLessThan(PARAM_YCS_VALUES, PARAM_ZERO);
    }
    //Check SSBOffset is a non-negative int
    if (iSSBOffset < 0)
      CError::errorLessThan(PARAM_SSB_OFFSET, PARAM_ZERO);

  } catch (string &Ex) {
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


    // TODO: Get our derived quantity
    //pDerivedQuantity = CDerivedQuantityManager::Instance()->getDerivedQuantity(sSSB);

    // Populate Our Ages Index
    iAgeIndex = pWorld->getColIndexForAge(iAge);

    // Validate our Vectors are all same size
    if (getCategoryCount() != (int)vProportions.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_PROPORTIONS);

  } catch (string &Ex) {
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

    // TODO: sort this mess out!

    // Setup Our Variables
    double dYCS = vYCSValues[pTimeStepManager->getCurrentYear() - pWorld->getInitialYear()];
    double dMeanYCS=0;
    // Get men YCS
    for ( int i = 0; i < (int)vYCSValues.size(); ++i ) {
      dMeanYCS += vYCSValues[i];
    }
    dMeanYCS /= ( vYCSValues.size() + 1 );
    // standardise YCS
    dYCS /= dMeanYCS;
    // Get SSB (and B0)
    double dSSBRatio = 1;// pDerivedQuantity->getValue(iSSBOffset)/pDerivedQuantity->getFirstValue();


    double dTrueYCS =  dYCS * dSSBRatio / (1 - ((5 * dSteepness - 1) / (4 * dSteepness) ) * (1 - dSSBRatio));
    double dAmountPer = dR0 * dTrueYCS;

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

        pDiff = pWorld->getDifferenceSquare(i, j);

        // Loop Through the Categories and Ages we have and Recruit
        for (int k = 0; k < getCategoryCount(); ++k)
          pDiff->addValue(vCategoryIndex[k], iAgeIndex, (value * vProportions[k]) );
      }
    }
#ifndef OPTIMIZE
  } catch(string &Ex) {
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
    vProportions.clear();
  }
