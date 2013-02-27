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
#include "../../Helpers/ForEach.h"

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
    dCR = pParameterList->getDouble(PARAM_CONSUMPTION_RATE);
    pParameterList->fillVector(vPreyGroups, PARAM_PREY);
    pParameterList->fillVector(vElectivityList, PARAM_ELECTIVITIES);
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);
    pParameterList->fillVector(vPreyAllocationList, PARAM_PREY_GROUPS);
    pParameterList->fillVector(vPredatorCategoryList, PARAM_PREDATOR_CATEGORIES);
    pParameterList->fillVector(vPredatorSelectivityList, PARAM_PREDATOR_SELECTIVITIES);
    dUMax = pParameterList->getDouble(PARAM_U_MAX,true,0.99);
    sPenalty  = pParameterList->getString(PARAM_PENALTY, true, "");

    // Base Validation
    CProcess::validate();

    // Register Estimables
    registerEstimable(PARAM_CONSUMPTION_RATE,&dCR);
    for (int i = 0; i < (int)vElectivityList.size(); ++i)
      registerEstimable(PARAM_ELECTIVITIES, i, &vElectivityList[i]);

    // Local Validation
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

    if (vPreyGroups.size() != vElectivityList.size())
      CError::errorListSameSize(PARAM_PREY, PARAM_ELECTIVITIES);

    if (getCategoryCount() != (int) vPreyAllocationList.size())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_PREY_GROUPS);

    if (getPredatorCategoryCount() != getPredatorSelectivityCount())
      CError::errorListSameSize(PARAM_PREDATOR_CATEGORIES, PARAM_PREDATOR_SELECTIVITIES);

    if (dUMax >= ONE)
      CError::errorGreaterThanEqualTo(PARAM_U_MAX, PARAM_ONE);
    if (dUMax <= TRUE_ZERO)
      CError::errorLessThanEqualTo(PARAM_U_MAX, PARAM_ZERO);

    if (dCR < ZERO)
      CError::errorLessThanEqualTo(PARAM_CR, PARAM_ZERO);

    // Loop Through Electivities. Make Sure They have sum one, and they are always non-negative
    double dRunningTotal = 0.0;
    foreach(double Prop, vElectivityList) {
      dRunningTotal += Prop;
      if (Prop < TRUE_ZERO)
        CError::errorLessThan(PARAM_ELECTIVITIES, PARAM_ZERO);
    }
    // See if it is less than one
    if (dRunningTotal != 1.0)
      CError::errorNotEqual(PARAM_ELECTIVITIES, PARAM_ONE);

    //Loop through prey groups and ensure uniqueness
    if (CComparer::hasDuplicates(vPreyGroups))
      CError::errorDuplicate(PARAM_PREY, getLabel());

    //Check each prey is in a prey group
    foreach(string Prey, vPreyAllocationList) {
     bool bIsIn = false;
      for (int i=0; i < (int) vPreyGroups.size(); ++i) {
        if (Prey == vPreyGroups[i]) {
          bIsIn = true;
          break;
        }
      }
      if (!bIsIn)
        CError::errorInvalidCharacter(PARAM_PREY_GROUPS,PARAM_PREY);
    }

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

    //define number of prey groups
    iNPreyGroups = vPreyGroups.size();

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

    //reset holding vectors
    vMortalityRate.resize(iNPreyGroups);
    vMortalityN.resize(iNPreyGroups);
    vMortalityBiomass.resize(iNPreyGroups);
    vMortalityYears.resize(0);
    vPredatorBiomass.resize(0);

    for (int i=0; i < iNPreyGroups; ++i) {
      vMortalityRate[i].resize(0);
      vMortalityN[i].resize(0);
      vMortalityBiomass[i].resize(0);
    }

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

    vector<double> vSumMortality(iNPreyGroups);
    vector<double> vSumAbundance(iNPreyGroups);
    vector<double> vSumMortalityBiomass(iNPreyGroups);

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

        // Clear our Vulnerable Amount
        vVulnerable.resize(iNPreyGroups);
        dPredatorVulnerable = 0.0;
        double dTotalVulnerable = 0.0;

        // Loop Through Group, then Categories & Work out Vulnerable Stock in abundance or biomass
        for (int m = 0; m < iNPreyGroups; ++m) {
          vVulnerable[m] = 0.0;
          for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
            if (vPreyAllocationList[k] == vPreyGroups[m]) { // if a member of that group
              for (int l = 0; l < iBaseColCount; ++l) {
                // get current prey abundance in age/category
                dCurrent = pBaseSquare->getValue( vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l);
                if (dCurrent < 0.0)
                  dCurrent = 0.0;

                // record our Vulnerable number
                pWorldSquare->addValue(vCategoryIndex[k], l, dCurrent);

                // Increase Vulnerable biomass
                if(bIsAbundance) {
                  vVulnerable[m] += dCurrent;
                } else {
                  vVulnerable[m] += dCurrent * pWorld->getMeanWeight(l,vCategoryIndex[k]);
                }
              }
            }
          }
          dTotalVulnerable += vVulnerable[m] * vElectivityList[m];
        }

        // Loop Through Categories & Work out Predators in abundance or biomass
        for (int k = 0; k < (int)vPredatorCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // get current prey abundance in age/category
            dPredatorCurrent = pBaseSquare->getValue( vPredatorCategoryIndex[k], l) * vPredatorSelectivityIndex[k]->getResult(l);
            if (dPredatorCurrent <0.0)
              dPredatorCurrent = 0.0;

            // Increase Predator biomass
            if(bIsAbundance) {
              dPredatorVulnerable += dPredatorCurrent;
            } else {
              dPredatorVulnerable += dPredatorCurrent * pWorld->getMeanWeight(l,vPredatorCategoryIndex[k]);
            }
          }
        }

        // Work out exploitation rate to remove (catch/vulnerableBiomass)
        for (int m = 0; m < iNPreyGroups; ++m) {
          vMortality[m] = dPredatorVulnerable * dCR * (vVulnerable[m] * vElectivityList[m]) / dTotalVulnerable;
          vExploitation[m] = vMortality[m] / CMath::zeroFun(vVulnerable[m],ZERO);
          if (vExploitation[m] > dUMax) {
            vExploitation[m] = dUMax;
            if (pPenalty != 0) { // Throw Penalty
              pPenalty->trigger(sLabel, vMortality[m], (vVulnerable[m] * dUMax));
            }
          } else if (vExploitation[m] < ZERO) {
            vExploitation[m] = 0.0;
          }
        }

        // Loop Through Categories & remove number based on calcuated exploitation rate
        for (int m = 0; m < iNPreyGroups; ++m) {
          for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
            if (vPreyAllocationList[k] == vPreyGroups[m]) { // if a member of that group
              for (int l = 0; l < iBaseColCount; ++l) {
                // Get Amount to remove
                dCurrent = pWorldSquare->getValue(vCategoryIndex[k], l) * vExploitation[m];

                // If is Zero, Cont
                if (dCurrent <= 0.0)
                  continue;

                // Subtract These
                pDiff->subValue(vCategoryIndex[k], l, dCurrent);
                vSumMortality[m] += dCurrent;
                vSumAbundance[m] += pBaseSquare->getValue( vCategoryIndex[k], l);
                if(!bIsAbundance) vSumMortalityBiomass[m] += dCurrent * pWorld->getMeanWeight(l,vCategoryIndex[k]);
              }
            }
          }
        }
      }
    }
    if ( pRuntimeController->getCurrentState() != STATE_INITIALIZATION ) {
      vMortalityYears.push_back(pTimeStepManager->getCurrentYear());
      vPredatorBiomass.push_back(dPredatorVulnerable);
      for(int m=0; m <iNPreyGroups; ++m) {
        vMortalityRate[m].push_back(vSumMortality[m] / vSumAbundance[m]);
        vMortalityN[m].push_back(vSumMortality[m]);
        if(!bIsAbundance) vMortalityBiomass[m].push_back(vSumMortalityBiomass[m]);
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
