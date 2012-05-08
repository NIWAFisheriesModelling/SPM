//============================================================================
// Name        : CCategoryTransitionProcess.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Penalties/CPenalty.h"
#include "../../Penalties/CPenaltyManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "CCategoryTransitionProcess.h"

//**********************************************************************
// CCategoryTransitionProcess::CCategoryTransitionProcess()
// Default Constructor
//**********************************************************************
CCategoryTransitionProcess::CCategoryTransitionProcess() {
  // Variables
  pTimeStepManager = CTimeStepManager::Instance();
  pWorldSquare     = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FROM);     //categories
  pParameterList->registerAllowed(PARAM_SELECTIVITIES); //selectivities for FROM to calculate vulnerable
  pParameterList->registerAllowed(PARAM_TO);       //categories
  pParameterList->registerAllowed(PARAM_YEARS);    //years for layers
  pParameterList->registerAllowed(PARAM_LAYERS);   //n to move
  pParameterList->registerAllowed(PARAM_PENALTY);

}

//**********************************************************************
// int CCategoryTransitionProcess::getYears(int index)
// Return the years entry from vector @ index
//**********************************************************************
int CCategoryTransitionProcess::getYears(int index) {
  return vYearsList[index];
}

//**********************************************************************
// string CCategoryTransitionProcess::getLayers(int index)
// Return the layers entry in vector at index
//**********************************************************************
string CCategoryTransitionProcess::getLayers(int index) {
  return vLayersList[index];
}

//**********************************************************************
// string CCategoryTransitionProcess::getCategoryTo(int index)
// Get category from vector at index
//**********************************************************************
string CCategoryTransitionProcess::getCategoryTo(int index) {
  return vCategoryToList[index];
}

//**********************************************************************
// void CCategoryTransitionProcess::validate()
// Validate This Object
//**********************************************************************
void CCategoryTransitionProcess::validate() {
  try {
    // Base Validation
    CProcess::validate();

    // Get our Parameters
    sPenalty  = pParameterList->getString(PARAM_PENALTY, true, "");

    pParameterList->fillVector(vCategoryList, PARAM_FROM);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);
    pParameterList->fillVector(vCategoryToList, PARAM_TO);
    pParameterList->fillVector(vYearsList, PARAM_YEARS);
    pParameterList->fillVector(vLayersList, PARAM_LAYERS);

    // Check for Duplicate Year
    map<int, int> mYears;
    foreach(int Year, vYearsList) {
      mYears[Year]++;

      if (mYears[Year] > 1)
        CError::errorDuplicate(PARAM_YEAR, boost::lexical_cast<string>(Year));
    }

    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_FROM, PARAM_SELECTIVITIES);
    if (getCategoryCount() != getCategoryToCount())
      CError::errorListSameSize(PARAM_FROM, PARAM_TO);
    if (getYearsCount() != getLayersCount())
      CError::errorListSameSize(PARAM_YEARS, PARAM_LAYERS);

  } catch(string &Ex) {
    Ex = "CCategoryTransitionProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionProcess::build()
// Build our Relationships and Indexes
//**********************************************************************
void CCategoryTransitionProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Build our Grid To Be World+1
    if (pWorldSquare == 0) {
      pWorldSquare = new CWorldSquare();
      pWorldSquare->build();
    }

    // Build our Layer Index
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayerManager->fillVector(vLayersIndex, vLayersList);

    // Build the category to list
    foreach(string Name, vCategoryToList) {
      vCategoryToIndex.push_back(pWorld->getCategoryIndexForName(Name));
    }

    // Build Penalty
    if (sPenalty != "")
      pPenalty = CPenaltyManager::Instance()->getPenalty(sPenalty);

  } catch(string &Ex) {
    Ex = "CCategoryTransitionProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionProcess::execute()
// Execute This Process
//**********************************************************************
void CCategoryTransitionProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // See if we are suppose to be executing first
    bYearMatch    = false;
    iCurrentYear  = pTimeStepManager->getCurrentYear();
    for (int i = 0; i < (int)vYearsList.size(); ++i) {
      if (vYearsList[i] == iCurrentYear) {
        bYearMatch = true;
        pLayer = vLayersIndex[i];
        break;
      }
    }

    // No Match. Don't Execute
    if (!bYearMatch)
      return;

    // Base execute
    CProcess::execute();


    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        // Clear our Square Out
        pWorldSquare->zeroGrid();

        // Get Layer Value
        dN = pLayer->getValue(i, j);

        // Clear our Vulnerable Amount
        dVulnerable = 0.0;

        // Loop Through Categories & Work out Vulnerable Stock
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k],l) * vSelectivityIndex[k]->getResult(l);
            pWorldSquare->addValue(vCategoryIndex[k], l, dCurrent);

            // Increase Vulnerable Amount
            dVulnerable += dCurrent;
          }
        }

        // Work out exploitation rate To Kill off
        dExploitation = dN / CMath::zeroFun(dVulnerable,ZERO);
        if (dExploitation > 0.999) {
          dExploitation = 0.999;
          if (pPenalty != 0) { // Throw Penalty
            pPenalty->trigger(sLabel, dN, (dVulnerable * 0.999));
          }
        }

        // Loop Through Categories & Kill Stock
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Amount to move
            dCurrent = pWorldSquare->getValue(vCategoryIndex[k], l) * dExploitation;

            // If is Zero, Cont
            if (CComparer::isZero(dCurrent))
              continue;

            // Add these to the categories to move to
            pDiff->addValue(vCategoryToIndex[k], l, dCurrent);
          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch(string &Ex) {
    Ex = "CCategoryTransitionProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CCategoryTransitionProcess::~CCategoryTransitionProcess()
// Default De-Constructor
//**********************************************************************
CCategoryTransitionProcess::~CCategoryTransitionProcess() {
  // Clean Our Grid
  if (pWorldSquare != 0) {
    delete pWorldSquare;
  }
}
