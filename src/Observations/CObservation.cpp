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
#include "../CLayerManager.h"
#include "../CSelectivityManager.h"

//**********************************************************************
// CObservation::CObservation(CObservation *Observation);
// Default Constructor
//**********************************************************************
CObservation::CObservation(CObservation *Observation)
: CBaseExecutableObject(Observation) {

  // Variables
  dScore              = 0.0;
  pLayer              = 0;
  sDist               = "";
  sLayer              = "";
  sLabel              = "";
  iYear               = -1;
  iTimeStep           = -1;

  // Copy Construct
  if (Observation != 0) {
    iYear     = Observation->getYear();
    sDist     = Observation->getDist();
    sLayer    = Observation->getLayer();
    sLabel    = Observation->getLabel();
    iTimeStep = Observation->getTimeStep();

    // Clone our Category and Selectivity Lists
    for (int i = 0; i < Observation->getCategoryCount(); ++i)
      vCategoryList.push_back(Observation->getCategory(i));
    for (int i = 0; i < Observation->getSelectivityCount(); ++i)
      vSelectivityList.push_back(Observation->getSelectivity(i));
  }
}


//**********************************************************************
// void CObservation::addCategory(string value)
// Add Category To our Vector
//**********************************************************************
void CObservation::addCategory(string value) {
  vCategoryList.push_back(value);
}

//**********************************************************************
// string CObservation::getCategory(int index)
// Get Category
//**********************************************************************
string CObservation::getCategory(int index) {
  return vCategoryList[index];
}
//**********************************************************************
// void CObservation::addSelectivity(string value)
// Add Selectivity to our vector
//**********************************************************************
void CObservation::addSelectivity(string value) {
  vSelectivityList.push_back(value);
}

//**********************************************************************
// string CObservation::getSelectivity(int index)
// Get The selectivity for index
//**********************************************************************
string CObservation::getSelectivity(int index) {
  return vSelectivityList[index];
}

//**********************************************************************
// void CObservation::validate()
// validate
//**********************************************************************
void CObservation::validate() {
  try {
    // Adjust Year
      if (iYear > pConfig->getHumanStartYear())
        iYear -= pConfig->getHumanStartYear();

      if (iYear > pConfig->getNumberOfYearsToRun())
        errorGreaterThan(PARAM_YEAR, PARAM_RUN_YEARS);
      if (iYear < 0)
        errorLessThan(PARAM_YEAR, PARAM_ZERO);
      if (iTimeStep <= 0)
        errorLessThanEqualTo(PARAM_TIME_STEP, PARAM_ZERO);
      if (iTimeStep > pConfig->getNumberOfTimeSteps())
        errorGreaterThan(PARAM_TIME_STEP, PARAM_TIME_STEPS);
      if (sLayer == "")
        errorMissing(PARAM_LAYER_NAME);
      if (vCategoryList.size() == 0)
        errorMissing(PARAM_CATEGORIES);
      if (vSelectivityList.size() == 0)
        errorMissing(PARAM_SELECTIVITIES);
      if (sDist == "")
        errorMissing(PARAM_DIST);

  } catch (string Ex) {
    Ex = "CObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservation::build()
// build
//**********************************************************************
void CObservation::build() {
  try {
    // Get our Layer Pointer
    if (pLayer == 0) {
      CLayerManager *pLayerManager = CLayerManager::Instance();
      pLayer = pLayerManager->getStringLayer(sLayer);
    }

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
