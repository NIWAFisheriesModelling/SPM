//============================================================================
// Name        : CAbundanceLayer.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CAbundanceLayer.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../World/CWorld.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CAbundanceLayer::CAbundanceLayer()
// Default Constructor
//**********************************************************************
CAbundanceLayer::CAbundanceLayer() {
  // Variables
  pWorld = CWorld::Instance();

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
}

//**********************************************************************
// void CAbundanceLayer::addCategory(string value)
// Add A Category to our Abundance Layer
//**********************************************************************
void CAbundanceLayer::addCategory(string value) {
  vCategoryNames.push_back(value);
}

//**********************************************************************
// void CAbundanceLayer::addSelectivity(string value)
// Add a selectivity to our list.
//**********************************************************************
void CAbundanceLayer::addSelectivity(string value) {
  vSelectivityNames.push_back(value);
}

//**********************************************************************
// void CAbundanceLayer::validate()
// Validate
//**********************************************************************
void CAbundanceLayer::validate() {
 try {
   // Base Validate
   CNumericLayer::validate();

   // Populate our Parameters
   pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
   pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

   // Check For Duplicate Categories.
   map<string, int> mList;
   foreach(string Category, vCategoryNames) {
     mList[Category] += 1;
     if (mList[Category] > 1)
       throw string(ERROR_DUPLICATE_CATEGORY + Category);
   }

 } catch (string Ex) {
   Ex = "CAbundanceLayer.validate(" + getLabel() + ")->" + Ex;
   throw Ex;
 }
}

//**********************************************************************
// void CAbundanceLayer::build()
// Build
//**********************************************************************
void CAbundanceLayer::build() {
  try {
    // Build Selectivities
    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vSelectivities, vSelectivityNames);

    // Build Categories
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

  } catch (string Ex) {
    Ex = "CAbundanceLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CAbundanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// get Value
//**********************************************************************
double CAbundanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0) {
#ifndef OPTIMISE
  try {
#endif

    return pWorld->getBaseSquare(RowIndex, ColIndex)->getPopulation();

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CAbundanceLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CAbundanceLayer::~CAbundanceLayer()
// Default De-Constructor
//**********************************************************************
CAbundanceLayer::~CAbundanceLayer() {
}
