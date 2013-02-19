//============================================================================
// Name        : CPreySwitchPredationProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CPreySwitchPredationProcess.h"
#include "../../Penalties/CPenaltyManager.h"
#include "../../Penalties/CPenalty.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CPreySwitchPredationProcess::CPreySwitchPredationProcess()
// Default Constructor
//**********************************************************************
CPreySwitchPredationProcess::CPreySwitchPredationProcess() {
  // Variables
  pGrid            = 0;
  sType = PARAM_PREY_SWITCH_PREDATION;
  pWorldSquare     = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_IS_ABUNDANCE);
  pParameterList->registerAllowed(PARAM_CONSUMPTION_RATE);
  pParameterList->registerAllowed(PARAM_PREY);
  pParameterList->registerAllowed(PARAM_ELECTIVITIES);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_PREY_GROUPS);
  //pParameterList->registerAllowed(PARAM_A);
  //pParameterList->registerAllowed(PARAM_B);
  //pParameterList->registerAllowed(PARAM_X);
  pParameterList->registerAllowed(PARAM_PREDATOR_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PREDATOR_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_U_MAX);
  pParameterList->registerAllowed(PARAM_PENALTY);
}

//**********************************************************************
// void CPreySwitchPredationProcess::validate()
// Validate our process
//**********************************************************************
void CPreySwitchPredationProcess::validate() {
  try {

    // Get our parameters
    bIsAbundance = pParameterList->getBool(PARAM_IS_ABUNDANCE);
    //dA = pParameterList->getDouble(PARAM_A);
    //dB = pParameterList->getDouble(PARAM_B);
    //dX = pParameterList->getDouble(PARAM_X,true,2.0);

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    pParameterList->fillVector(vPredatorCategoryList, PARAM_PREDATOR_CATEGORIES);
    pParameterList->fillVector(vPredatorSelectivityList, PARAM_PREDATOR_SELECTIVITIES);

    dUMax = pParameterList->getDouble(PARAM_U_MAX,true,0.99);
    sPenalty  = pParameterList->getString(PARAM_PENALTY, true, "");

    // Base Validation
    CProcess::validate();

    // Register Estimables
    registerEstimable(PARAM_A,&dA);
    registerEstimable(PARAM_B,&dB);
    registerEstimable(PARAM_X,&dX);

    // Local Validation
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

    if (getPredatorCategoryCount() != getPredatorSelectivityCount())
      CError::errorListSameSize(PARAM_PREDATOR_CATEGORIES, PARAM_PREDATOR_SELECTIVITIES);

    if (dUMax >= ONE)
      CError::errorGreaterThanEqualTo(PARAM_U_MAX, PARAM_ONE);
    if (dUMax <= TRUE_ZERO)
      CError::errorLessThanEqualTo(PARAM_U_MAX, PARAM_ZERO);

    //if (dA < ZERO)
    //  CError::errorLessThanEqualTo(PARAM_A, PARAM_ZERO);

    //if (dB < ZERO)
    //  CError::errorLessThanEqualTo(PARAM_B, PARAM_ZERO);

    //if (dX < ONE)
    //  CError::errorLessThanEqualTo(PARAM_X, PARAM_ONE);

  } catch (string &Ex) {
    Ex = "CPreySwitchPredationProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreySwitchPredationProcess::build()
// Build our process
//**********************************************************************
void CPreySwitchPredationProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Build our Grid To Be World+1
    if (pWorldSquare == 0) {
      pWorldSquare = new CWorldSquare();
      pWorldSquare->build();
    }

    // Build Refs
    pTimeStepManager = CTimeStepManager::Instance();

    // Build Penalty
    if (sPenalty != "")
      pPenalty = CPenaltyManager::Instance()->getPenalty(sPenalty);

    // Rebuild
    rebuild();

  } catch (string &Ex) {
    Ex = "CPreySwitchPredationProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CHollingMortalityProcess::rebuild()
// Rebuild
//**********************************************************************
void CPreySwitchPredationProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    //vMortalityRate.resize(0);
    //vMortalityN.resize(0);
    //vMortalityBiomass.resize(0);
    //vMortalityYears.resize(0);
    //vPredatorBiomass.resize(0);

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CPreySwitchPredationProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CPreySwitchPredationProcess::execute()
// Execute our process
//**********************************************************************
void CPreySwitchPredationProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base execute
    CProcess::execute();

    //double dSumMortality = 0;
    //double dSumAbundance = 0;
    //double dSumMortalityBiomass = 0;

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {

        // Get Current Square
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff = pWorld->getDifferenceSquare(i, j);

        // Clear our Square Out
        pWorldSquare->zeroGrid();

        // Loop Through Categories & Work out Vulnerable Stock in abundance or biomass
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
          }
        }

        // Loop Through Categories & Work out Predator Stock in abundance or biomass
        for (int k = 0; k < (int)vPredatorCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
          }
        }

      }
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CPreySwitchPredationProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CPreySwitchPredationProcess::~CPreySwitchPredationProcess()
// Destructor
//**********************************************************************
CPreySwitchPredationProcess::~CPreySwitchPredationProcess() {

  // Clean Our Grid
  if (pWorldSquare != 0) {
    delete pWorldSquare;
  }

  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iWorldHeight; ++i) {
      delete [] pGrid[i];
      pGrid[i] = 0;
    }
    delete [] pGrid;
  }
}
