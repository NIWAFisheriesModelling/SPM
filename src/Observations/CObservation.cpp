//============================================================================
// Name        : CObservation.cpp
// Author      : S.Rasmussen
// Date        : 19/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CObservation.h"
#include "../Layers/CLayerManager.h"
#include "../Selectivities/CSelectivityManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

//**********************************************************************
// CObservation::CObservation()
// Default Constructor
//**********************************************************************
CObservation::CObservation() {
}

//**********************************************************************
// string CObservation::getCategory(int index)
// Get Category
//**********************************************************************
string CObservation::getCategory(int index) {
  return vCategoryList[index];
}

//**********************************************************************
// string CObservation::getSelectivity(int index)
// Get The selectivity for index
//**********************************************************************
string CObservation::getSelectivity(int index) {
  return vSelectivityList[index];
}

//**********************************************************************
// void CObservation::build()
// build
//**********************************************************************
void CObservation::build() {
  try {
    // Get our Layer Pointer
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayer = pLayerManager->getStringLayer(sLayer);

    // Do We Need To Re-Build Selectivity Index?
    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    foreach(string Name, vSelectivityList) {
      vSelectivityIndex.push_back(pSelectivityManager->getSelectivity(Name));
    }

    foreach(string Name, vCategoryList) {
      vCategoryIndex.push_back(pWorld->getCategoryIndexForName(Name));
    }

  } catch (string Ex) {
    Ex = "CObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CObservation::~CObservation()
// Default De-Constructor
//**********************************************************************
CObservation::~CObservation() {
}
