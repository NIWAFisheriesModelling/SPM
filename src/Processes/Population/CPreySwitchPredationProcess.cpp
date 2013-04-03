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
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CCompoundCategories.h"
#include "../../Penalties/CPenalty.h"
#include "../../Penalties/CPenaltyManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CPreySwitchPredationProcess::CPreySwitchPredationProcess()
// Default Constructor
//**********************************************************************
CPreySwitchPredationProcess::CPreySwitchPredationProcess() {
  // Variables
  pGrid            = 0;
  sType = PARAM_PREY_SWITCH_PREDATION;
  pWorldSquare     = 0;
  pPreyCategories  = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_IS_ABUNDANCE);
  pParameterList->registerAllowed(PARAM_CONSUMPTION_RATE);
  pParameterList->registerAllowed(PARAM_ELECTIVITIES);
  pParameterList->registerAllowed(PARAM_PREY_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PREY_SELECTIVITIES);
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
    pParameterList->fillVector(vElectivityList, PARAM_ELECTIVITIES);
    pParameterList->fillVector(vPreyCategoryList, PARAM_PREY_CATEGORIES);
    pParameterList->fillVector(vPreySelectivityList, PARAM_PREY_SELECTIVITIES);
    pParameterList->fillVector(vPredatorCategoryList, PARAM_PREDATOR_CATEGORIES);
    pParameterList->fillVector(vPredatorSelectivityList, PARAM_PREDATOR_SELECTIVITIES);
    dUMax = pParameterList->getDouble(PARAM_U_MAX,true,0.99);
    sPenalty  = pParameterList->getString(PARAM_PENALTY, true, "");

    // Base Validation
    // CProcess::validate();
    CBaseExecute::validate();

    // Check For Duplicate Prey Categories, ignoring '+'
    map<string, int> mList;
    if (vPreyCategoryList.size() > 0) {
      foreach(string Category, vPreyCategoryList) {
        if ( Category != CONFIG_AND )
          mList[Category] += 1;

        if (mList[Category] > 1)
          CError::errorDuplicate(PARAM_PREY_CATEGORIES, Category);
      }
      mList.clear();
    }

    // Check For Duplicate Predator Categories
    mList.clear();
    if (vPredatorCategoryList.size() > 0) {
      foreach(string Category, vPredatorCategoryList) {
        mList[Category] += 1;

        if (mList[Category] > 1)
          CError::errorDuplicate(PARAM_PREDATOR_CATEGORIES, Category);
      }
      mList.clear();
    }

    // Register Estimables
    registerEstimable(PARAM_CONSUMPTION_RATE,&dCR);
    for (int i = 0; i < (int)vElectivityList.size(); ++i)
      registerEstimable(PARAM_ELECTIVITIES, i, &vElectivityList[i]);

    // Assign compound categories
    pPreyCategories = new CCompoundCategories;
    pPreyCategories->setCategories(vPreyCategoryList);

    // Local Validation
    if (pPreyCategories->getNCategories() != (int)vPreySelectivityList.size())
      CError::errorListSameSize(PARAM_PREY_CATEGORIES, PARAM_PREY_SELECTIVITIES);

    if ((int)vElectivityList.size() != pPreyCategories->getNRows())
      CError::errorListSameSize(PARAM_PREY_CATEGORIES, PARAM_ELECTIVITIES);

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
    // Check if equal to one
    if (dRunningTotal != 1.0)
      CError::errorNotEqual(PARAM_ELECTIVITIES, PARAM_ONE);


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
    //CProcess::build();

    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    // Prey
    int count = 0;
    vector<CSelectivity* >   tempSelectivityIndex;
    for( int i =0; i < pPreyCategories->getNRows(); ++i) {
      for( int j = 0; j < pPreyCategories->getNElements(i); ++j) {
        tempSelectivityIndex.push_back(pSelectivityManager->getSelectivity(vPreySelectivityList[count]));
        count++;
      }
      vvPreySelectivityIndex.push_back(tempSelectivityIndex);
    }

    // Predator
    foreach(string Name, vPredatorSelectivityList) {
      vPredatorSelectivityIndex.push_back(pSelectivityManager->getSelectivity(Name));
    }
    foreach(string Name, vPredatorCategoryList) {
      vPredatorCategoryIndex.push_back(pWorld->getCategoryIndexForName(Name));
    }

    // Setup Vars
    iBaseColCount   = pWorld->getBaseSquare(0, 0)->getWidth();

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
// void CPreySwitchPredationProcess::rebuild()
// Rebuild
//**********************************************************************
void CPreySwitchPredationProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    //reset holding vectors
    vMortalityRate.resize(pPreyCategories->getNRows());
    vMortalityN.resize(pPreyCategories->getNRows());
    vMortalityBiomass.resize(pPreyCategories->getNRows());
    vMortalityYears.resize(0);
    vPredatorBiomass.resize(0);

    for (int i=0; i < pPreyCategories->getNRows(); ++i) {
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
// vector<string> CPreySwitchPredationProcess::getPreyGroups()
//
//**********************************************************************
vector<string> CPreySwitchPredationProcess::getPreyGroups() {

  vector<string> result;

  for ( int i = 0; i < pPreyCategories->getNRows(); ++i ) {
    string temp ="";
    for ( int j = 0; j < pPreyCategories->getNElements(i); ++j ) {
      temp = std::string(temp) + std::string(pPreyCategories->getCategoryName(i,j)) + std::string(j<((int)pPreyCategories->getNElements(i)-1)?CONFIG_AND:"");
    }
    result.push_back(temp);
  }

  return(result);
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
   //
    vector<double> vSumMortality(pPreyCategories->getNRows());
    vector<double> vSumAbundance(pPreyCategories->getNRows());
    vector<double> vSumMortalityBiomass(pPreyCategories->getNRows());

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
        vVulnerable.resize(pPreyCategories->getNRows());
        vMortality.resize(pPreyCategories->getNRows());
        vExploitation.resize(pPreyCategories->getNRows());
        dPredatorVulnerable = 0.0;
        double dTotalVulnerable = 0.0;

        // Loop Through Groups then Categories & Work out Vulnerable Stock in abundance or biomass
        for (int m = 0; m < pPreyCategories->getNRows(); ++m) {
          vVulnerable[m] = 0.0;
          for (int k = 0; k < pPreyCategories->getNElements(m); ++k) {
            for (int l = 0; l < iBaseColCount; ++l) {
              // get current prey abundance in age/category
              dCurrent = pBaseSquare->getValue( pPreyCategories->getCategoryIndex(m,k), l) * vvPreySelectivityIndex[m][k]->getResult(l);
              if (dCurrent < 0.0)
                dCurrent = 0.0;
               // record our Vulnerable number
              pWorldSquare->addValue(pPreyCategories->getCategoryIndex(m,k), l, dCurrent);
               // Increase Vulnerable biomass
              if(bIsAbundance) {
                vVulnerable[m] += dCurrent;
              } else {
                vVulnerable[m] += dCurrent * pWorld->getMeanWeight(l,pPreyCategories->getCategoryIndex(m,k));
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

            if (dPredatorCurrent < 0.0)
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
        for (int m = 0; m < pPreyCategories->getNRows(); ++m) {
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

        // Loop Through Categories & remove number based on calculated exploitation rate
        for (int m = 0; m < pPreyCategories->getNRows(); ++m) {
          for (int k = 0; k < pPreyCategories->getNElements(m); ++k) {
            for (int l = 0; l < iBaseColCount; ++l) {
              // Get Amount to remove
              dCurrent = pWorldSquare->getValue(pPreyCategories->getCategoryIndex(m,k), l) * vExploitation[m];
               // If is Zero, Cont
              if (dCurrent <= 0.0)
                continue;
               // Subtract These
              pDiff->subValue(pPreyCategories->getCategoryIndex(m,k), l, dCurrent);
              vSumMortality[m] += dCurrent;
              vSumAbundance[m] += pBaseSquare->getValue( pPreyCategories->getCategoryIndex(m,k), l);
              if(!bIsAbundance) vSumMortalityBiomass[m] += dCurrent * pWorld->getMeanWeight(l,pPreyCategories->getCategoryIndex(m,k));
            }
          }
        }
      }
    }
    if ( pRuntimeController->getCurrentState() != STATE_INITIALIZATION ) {
      vMortalityYears.push_back(pTimeStepManager->getCurrentYear());
      vPredatorBiomass.push_back(dPredatorVulnerable);
      for(int m=0; m < pPreyCategories->getNRows(); ++m) {
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
