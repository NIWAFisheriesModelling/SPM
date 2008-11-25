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
#include "../../CLayerManager.h"
#include "../../CTimeStepManager.h"
#include "../../Penalties/CPenalty.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Layers/CNumericLayer.h"

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

  registerEstimable(PARAM_UMAX, &dUMax);

  // Copy Construct
  if (Process != 0) {
    dUMax         = Process->getUMax();

    // Copy Vectors
    for (int i = 0; i < Process->getYearsCount(); ++i)
      vYearsList.push_back(Process->getYears(i));
    for (int i = 0; i < Process->getLayersCount(); ++i)
      vLayersList.push_back(Process->getLayers(i));
  }
}

//**********************************************************************
// void CEventMortalityProcess::addYears(int value)
// Add A Years To Our List
//**********************************************************************
void CEventMortalityProcess::addYears(int value) {
  // Scale Year back to internal representation
  value -= pConfig->getHumanStartYear();

  if (value < 0)
    throw string(ERROR_INVALID_YEAR + convertInt(value));

  // Add
  vYearsList.push_back(value);
}

//**********************************************************************
// int CEventMortalityProcess::getYears(int index)
// Return the years entry from vector @ index
//**********************************************************************
int CEventMortalityProcess::getYears(int index) {
  return vYearsList[index];
}

//**********************************************************************
// void CEventMortalityProcess::addLayers(string value)
// Add Layers to our list
//**********************************************************************
void CEventMortalityProcess::addLayers(string value) {
  vLayersList.push_back(value);
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

    // Local Validation
    if (vLayersList.size() == 0)
      errorMissing(PARAM_LAYERS);
    if (isSame(dUMax, -1.0))
      errorMissing(PARAM_UMAX);
    if (vYearsList.size() == 0)
      errorMissing(PARAM_YEARS);
    if (vLayersList.size() != vYearsList.size())
      errorNotEqual(PARAM_YEARS, PARAM_LAYERS);
    if (vSelectivityList.size() != vCategoryList.size())
      throw string(ERROR_EQUAL_CATEGORY_SELECTIVITY);
    if (vSelectivityList.size() == 0)
      errorMissing(PARAM_SELECTIVITIES);
    if (bDependsOnLayer)
      errorSupported(PARAM_LAYER_NAME);

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
        dExploitation = dCatch / zeroFun(dVulnerable,ZERO);
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
            if (isZero(dCurrent))
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
