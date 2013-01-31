//============================================================================
// Name        : CHollingMortalityRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CHollingMortalityRateProcess.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/CBiomassLayer.h"
#include "../../Layers/Numeric/CAbundanceLayer.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Penalties/CPenaltyManager.h"
#include "../../Penalties/CPenalty.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CHollingMortalityRateProcess::CHollingMortalityRateProcess()
// Default Constructor
//**********************************************************************
CHollingMortalityRateProcess::CHollingMortalityRateProcess() {
  // Variables
  pGrid            = 0;
  pLayer           = 0;
  sType = PARAM_HOLLING_MORTALITY_RATE;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_HOLLING_TYPE);
  pParameterList->registerAllowed(PARAM_A);
  pParameterList->registerAllowed(PARAM_B);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_U_MAX);
  pParameterList->registerAllowed(PARAM_PENALTY);
}

//**********************************************************************
// void CHollingMortalityRateProcess::validate()
// Validate our process
//**********************************************************************
void CHollingMortalityRateProcess::validate() {
  try {

    // Get our parameters
    bHollingType2 = pParameterList->getBool(PARAM_HOLLING_TYPE, true, true);
    dA = pParameterList->getDouble(PARAM_A);
    dB = pParameterList->getDouble(PARAM_B);
    sLayer  = pParameterList->getString(PARAM_LAYER);
    dUMax = pParameterList->getDouble(PARAM_U_MAX,true,0.99);

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    sPenalty  = pParameterList->getString(PARAM_PENALTY, true, "");

    // Base Validation
    CProcess::validate();

    // Register Estimables
    registerEstimable(PARAM_A,&dA);
    registerEstimable(PARAM_B,&dB);

    // Local Validation
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

    if (dUMax >= ONE)
      CError::errorGreaterThanEqualTo(PARAM_U_MAX, PARAM_ONE);
    if (dUMax <= TRUE_ZERO)
      CError::errorLessThanEqualTo(PARAM_U_MAX, PARAM_ZERO);

    if (dA < ZERO)
      CError::errorLessThanEqualTo(PARAM_A, PARAM_ZERO);

    if (dB < ZERO)
      CError::errorLessThanEqualTo(PARAM_B, PARAM_ZERO);

  } catch (string &Ex) {
    Ex = "CHollingMortalityRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CHollingMortalityRateProcess::build()
// Build our process
//**********************************************************************
void CHollingMortalityRateProcess::build() {
  try {
    // Base Build
    CProcess::build();

    bIsAbundance = false;
    pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);
    CNumericLayer* pTempLayer = pLayer;
    CBiomassLayer *pBiomassPtr = dynamic_cast<CBiomassLayer*>(pTempLayer);
    if (pBiomassPtr == 0) {
      // Not biomass
      bIsAbundance = true;
      pTempLayer = pLayer;
      CAbundanceLayer *pAbundancePtr = dynamic_cast<CAbundanceLayer*>(pTempLayer);
      if (pAbundancePtr == 0) {
        // Not abundance and not biomass
        throw string("Layer '" + sLayer + "' is not of type abundance or biomass.");
      }
    }

    // Build Refs
    pTimeStepManager = CTimeStepManager::Instance();

    // Build Penalty
    if (sPenalty != "")
      pPenalty = CPenaltyManager::Instance()->getPenalty(sPenalty);

    // Rebuild
    rebuild();

  } catch (string &Ex) {
    Ex = "CHollingMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CHollingMortalityProcess::rebuild()
// Rebuild
//**********************************************************************
void CHollingMortalityRateProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    dASquared = dA * dA;
    dBSquared = dB * dB;
    vMortalityRate.resize(0);
    vMortalityN.resize(0);
    vMortalityBiomass.resize(0);
    vMortalityYears.resize(0);

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CHollingMortalityRateProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CHollingMortalityRateProcess::execute()
// Execute our process
//**********************************************************************
void CHollingMortalityRateProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base execute
    CProcess::execute();

    double dSumMortality = 0;
    double dSumAbundance = 0;
    double dSumMortalityBiomass = 0;

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        // Check Square Ok
        if (!pBaseSquare->getEnabled())
          continue;
        pDiff = pWorld->getDifferenceSquare(i, j);
        // Loop Through Categories and Ages
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Current Value
            // If predator layer is a biomass, then use prey as a biomass
            if(!bIsAbundance) {
              dCurrent = pBaseSquare->getValue( vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l) * pWorld->getMeanWeight(l,vCategoryIndex[k]);
            } else {
              dCurrent = pBaseSquare->getValue( vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l);
            }
            // Holling function type 2 or 3
            if(bHollingType2)
              dMortality = pLayer->getValue(i, j) * (dA * dCurrent)/(dB + dCurrent);
            else
              dMortality = pLayer->getValue(i, j) * (dASquared * dCurrent * dCurrent)/(dBSquared + dCurrent * dCurrent);

            // Work out exploitation rate to remove
            double dExploitation = dMortality / CMath::zeroFun(dCurrent,ZERO);
            // Check against Umax
            if (dExploitation > dUMax){
              dExploitation = dUMax;
              if (pPenalty != 0) // Throw Penalty
                pPenalty->trigger(sLabel, dMortality, (dCurrent * dUMax));
            } else if (dExploitation < 0.0) {
              dExploitation = 0.0;
            }

            dCurrent = pBaseSquare->getValue( vCategoryIndex[k], l) * dExploitation;

            // Check 0
            if (dCurrent <= 0.0)
               continue;

            // Do Add/Subs
            pDiff->subValue( vCategoryIndex[k], l, dCurrent);
            dSumMortality += dCurrent;
            dSumAbundance += pBaseSquare->getValue( vCategoryIndex[k], l);
            if(!bIsAbundance) dSumMortalityBiomass += dCurrent * pWorld->getMeanWeight(l,vCategoryIndex[k]);
          }
        }
      }
    }
    if ( pRuntimeController->getCurrentState() != STATE_INITIALIZATION ) {
      vMortalityYears.push_back(pTimeStepManager->getCurrentYear());
      vMortalityRate.push_back(dSumMortality / dSumAbundance);
      vMortalityN.push_back(dSumMortality);
      if(!bIsAbundance) vMortalityBiomass.push_back(dSumMortalityBiomass);
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CHollingMortalityRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CHollingMortalityRateProcess::~CHollingMortalityRateProcess()
// Destructor
//**********************************************************************
CHollingMortalityRateProcess::~CHollingMortalityRateProcess() {

  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iWorldHeight; ++i) {
      delete [] pGrid[i];
      pGrid[i] = 0;
    }
    delete [] pGrid;
  }
}
