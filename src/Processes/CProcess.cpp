//============================================================================
// Name        : CProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CProcess.h"
#include "../CLayerManager.h"
#include "../Layers/CNumericLayer.h"
#include "../CPenaltyManager.h"
#include "../CSelectivityManager.h"

//**********************************************************************
// CProcess::CProcess(CProcess *Process = 0)
// Default Constructor
//**********************************************************************
CProcess::CProcess(CProcess *Process)
: CBaseExecutableObject(Process) {

  // Default Vars
  bDependsOnLayer             = false;
  sLayerName                  = "";
  dLayerMin                   = -1.0;
  dLayerMax                   = -1.0;
  iNumberOfValidLayerSpots    = -1;
  pLayer                      = 0;
  pDiff                       = 0;
  iBaseColCount               = -1;
  dCurrent                    = 0;
  dSelectivityResult          = 0;
  sPenalty                    = "";
  pPenalty                    = 0;

  // Copy Construct
  if (Process != 0) {
    bDependsOnLayer     = Process->getDependsOnLayer();
    sLayerName          = Process->getLayerName();
    dLayerMin           = Process->getLayerMin();
    dLayerMax           = Process->getLayerMax();
    sPenalty            = Process->getPenalty();

    // Copy our Vectors
    for (int i = 0; i < Process->getCategoryCount(); ++i)
      addCategory(Process->getCategory(i));
    for (int i = 0; i < Process->getSelectivityCount(); ++i)
      addSelectivity(Process->getSelectivity(i));
    for (int i = 0; i < Process->getLayerCategoryCount(); ++i)
      addLayerCategory(Process->getLayerCategory(i));
  }
}

//**********************************************************************
// void CProcess::addCategory()
// Add Category To Our List
//**********************************************************************
void CProcess::addCategory(string value) {
  vCategoryList.push_back(value);
}

//**********************************************************************
// string CProcess::getCategory(int index)
// Get category from vector at index
//**********************************************************************
string CProcess::getCategory(int index) {
  return vCategoryList[index];
}

//**********************************************************************
// void CProcess::addSelectivity(string value)
// Add Selectivities to our List
//**********************************************************************
void CProcess::addSelectivity(string value) {
  vSelectivityList.push_back(value);
}

//**********************************************************************
// string CProcess::getSelectivity(int index)
// Get Selectivity from vector at index
//**********************************************************************
string CProcess::getSelectivity(int index) {
  return vSelectivityList[index];
}

//**********************************************************************
// void CProcess::addLayerCategory(string value)
// Add Layer Category (For String Layers
//**********************************************************************
void CProcess::addLayerCategory(string value) {
  vLayerCategoryList.push_back(value);
}

//**********************************************************************
// string CProcess::getLayerCategory(int index)
// Get layer category from vector at index
//**********************************************************************
string CProcess::getLayerCategory(int index) {
  return vLayerCategoryList[index];
}

//**********************************************************************
// void CProcess::validate()
// Validate our Base Parameters
//**********************************************************************
void CProcess::validate() {
  try {
    // Base Validation
    CBaseExecutableObject::validate();

    // If Layer is already assigned. No need to re-validate it
    if (sLayerName != "")
      setDependsOnLayer(true);
    else
      setDependsOnLayer(false);
    if ( (sLayerName == "") && (bDependsOnLayer) )
      errorMissing(PARAM_LAYER_NAME);
    if ( (dLayerMin == -1.0) && (dLayerMax != -1.0) )
      errorMissing(PARAM_LAYER_MIN);
    if ( (dLayerMax == -1.0) && (dLayerMin != -1.0) )
      errorMissing(PARAM_LAYER_MAX);
    if ( (dLayerMin >= -1.0) && (dLayerMax >= -1.0) && (dLayerMax < dLayerMin) )
      errorGreaterThan(PARAM_LAYER_MAX, PARAM_LAYER_MIN);

    map<string, int> mList;

    // Check For Duplicate Categories.
    if (vCategoryList.size() > 0) {
      foreach(string Category, vCategoryList) {
        mList[Category] += 1;

        if (mList[Category] > 1)
          throw string(ERROR_DUPLICATE_CATEGORY + Category);
      }
      mList.clear();
    }

  } catch (string Ex) {
    Ex = "CProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CProcess::build()
// Build our Base Objects
//**********************************************************************
void CProcess::build() {
  try {
    // Do We Need To Re-Build Selectivity Index?
    if ((int)vSelectivityIndex.size() == 0) {
      CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
      foreach(string Name, vSelectivityList) {
        vSelectivityIndex.push_back(pSelectivityManager->getSelectivity(Name));
      }
    }

    // Do We Need To Re-Build Category Index?
    if ((int)vCategoryIndex.size() == 0) {
      foreach(string Name, vCategoryList) {
        vCategoryIndex.push_back(pConfig->getCategoryIndexForName(Name));
      }
    }

    // Do We need to get our Layer Pointer?
    if ( (pLayer == 0) && (bDependsOnLayer) ) {
      // Assign
      CLayerManager *pLayerManager = CLayerManager::Instance();
      pLayer = pLayerManager->getNumericLayer(getLayerName());

      // If we are using Min/Max, Set Them
      if ( (dLayerMin >= 0.0) && (dLayerMax >= 0.0) )
        pLayer->setMinMax(dLayerMin, dLayerMax);

      // Check No. Valid Spots
      iNumberOfValidLayerSpots = pLayer->countValidSpaces();
      if (iNumberOfValidLayerSpots == 0)
        throw string(ERROR_VALID_SQUARES_WITH_LAYER);

      pLayer->defaultMinMax();
    }

    // Get Penalty
    if ( (pPenalty == 0) && (sPenalty != "") ) {
      CPenaltyManager *pPenaltyManager = CPenaltyManager::Instance();
      pPenalty = pPenaltyManager->getPenalty(sPenalty);
    }

    // Setup Vars
    iBaseColCount   = pWorld->getBaseSquare(0, 0)->getWidth();

  } catch (string Ex) {
    Ex = "CProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProcess::execute()
// Base execution
//**********************************************************************
void CProcess::execute() {
#ifndef OPTIMISE
  try {
#endif
    // Default Variables
    dCurrent  = 0.0;

    // Set Up Our Layer
    if (bDependsOnLayer) {
      if ( (dLayerMin >= 0.0) && (dLayerMax >= 0.0) )
        pLayer->setMinMax(dLayerMin, dLayerMax);
      else
        pLayer->defaultMinMax();
    }

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}
//**********************************************************************
// bool CProcess::checkUsableSquare(CWorldSquare *Square, int iX, int iY)
// Check If Square Is Usable
//**********************************************************************
bool CProcess::checkUsableSquare(CWorldSquare *Square, int iX, int iY) {
#ifndef OPTIMISE
  try {
#endif
    if (!Square->getEnabled())
      return false;

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CProcess.checkUsableSquare(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
  return true;
}

//**********************************************************************
// bool CProcess::checkUsableBaseSquare(int RowIndex, int ColIndex)
// Check If base Square Is Usable
//**********************************************************************
bool CProcess::checkUsableBaseSquare(int RowIndex, int ColIndex) {
#ifndef OPTIMISE
  try {
#endif
    // Check if Enabled
    if (!pBase->getEnabled())
      return false;

    // Check if Layer Oks It
    if (bDependsOnLayer)
      if (!pLayer->checkSpace(RowIndex, ColIndex))
        return false;

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CProcess.checkUsableSquare(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  // Default
  return true;
}

//**********************************************************************
// CProcess::~CProcess()
// Default De-Constructor
//**********************************************************************
CProcess::~CProcess() {
  // Clear
  pPenalty    = 0;
  pBase       = 0;
  pDiff       = 0;
  pLayer      = 0;
  pWorld      = 0;
  vCategoryList.clear();
  vCategoryIndex.clear();
  vSelectivityIndex.clear();
  vSelectivityList.clear();
}
