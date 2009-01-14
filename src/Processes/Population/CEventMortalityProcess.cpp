//============================================================================
// Name        : CEventMortalityProcess.cpp
// Author      : S.Rasmussen
// Date        : 9/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CEventMortalityProcess.h"
#include "../../Layers/CLayerManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../Penalties/CPenalty.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CEventMortalityProcess::CEventMortalityProcess(CEventMortalityProcess *Process)
// Default Constructor
//**********************************************************************
CEventMortalityProcess::CEventMortalityProcess(CEventMortalityProcess *Process)
: CProcess(Process) {
  // Variables
  dUMax            = -1.0;
  dCatch           = 0.0;
  dVulnerable      = 0.0;
  dExploitation    = 0.0;
  pWorldSquare     = 0;
  iCurrentYear     = 0;
  bYearMatch       = false;
  pTimeStepManager = CTimeStepManager::Instance();

  // Register estimable parameters
  registerEstimable(PARAM_UMAX, &dUMax);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_LAYERS);
  pParameterList->registerAllowed(PARAM_UMAX);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_PENALTY);
}

//**********************************************************************
// int CEventMortalityProcess::getYears(int index)
// Return the years entry from vector @ index
//**********************************************************************
int CEventMortalityProcess::getYears(int index) {
  return vYearsList[index];
}

//**********************************************************************
// string CEventMortalityProcess::getLayers(int index)
// Return the layers entry in vector at index
//**********************************************************************
string CEventMortalityProcess::getLayers(int index) {
  return vLayersList[index];
}

//**********************************************************************
// void CEventMortalityProcess:validate()
// Validate This
//**********************************************************************
void CEventMortalityProcess::validate() {
  try {
    // Base Validate
    CProcess::validate();

    // Get our Parameters
    dUMax     = pParameterList->getDouble(PARAM_UMAX);
    sPenalty  = pParameterList->getString(PARAM_PENALTY);

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vYearsList, PARAM_YEARS);
    pParameterList->fillVector(vLayersList, PARAM_LAYERS);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    // TODO: Check for vectors to be the same size

  } catch(string Ex) {
    Ex = "CEventMortalityProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEventMortalityProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CEventMortalityProcess::build() {
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

    foreach(string Label, vLayersList) {
      vLayersIndex.push_back(pLayerManager->getNumericLayer(Label));
    }

  } catch(string Ex) {
    Ex = "CEventMortalityProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEventMortalityProcess::execute()
// execute this Process
//**********************************************************************
void CEventMortalityProcess::execute() {
#ifndef OPTIMISE
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
        pBase       = pWorld->getBaseSquare(i, j);
        // Check Square Ok
        if (!pBase->getEnabled())
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        // Clear our Square Out
        pWorldSquare->zeroGrid();

        // Get Layer Value
        dCatch = pLayer->getValue(i, j);

        // Clear our Vulnerable Amount
        dVulnerable = 0.0;

        // Loop Through Categories & Work out Vulnerable Stock
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            dCurrent = pBase->getValue(vCategoryIndex[k],l) * vSelectivityIndex[k]->getResult(l);
            pWorldSquare->addValue(vCategoryIndex[k], l, dCurrent);

            // Increase Vulnerable Amount
            dVulnerable += dCurrent;
          }
        }

        // Work out exploitation rate To Kill off
        dExploitation = dCatch / CMath::zeroFun(dVulnerable,ZERO);
        if (dExploitation > dUMax) {
          dExploitation = dUMax;
          if (pPenalty != 0) { // Throw Penalty
            pPenalty->execute(sLabel, (dCatch - (dVulnerable * dUMax)));
          }
        }

        // Loop Through Categories & Kill Stock
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Amount to Kill/Exploit
            dCurrent = pWorldSquare->getValue(vCategoryIndex[k], l) * dExploitation;

            // If is Zero, Cont
            if (CComparer::isZero(dCurrent))
              continue;

            // Subtract These
            pDiff->subValue(vCategoryIndex[k], l, dCurrent);
          }
        }
      }
    }
#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CEventMortalityProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CEventMortalityProcess::~CEventMortalityProcess()
// Default De-Constructor
//**********************************************************************
CEventMortalityProcess::~CEventMortalityProcess() {
  // Clean Our Grid
  if (pWorldSquare != 0) {
    delete pWorldSquare;
  }
}
