//============================================================================
// Name        : CAbundanceLayer.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CAbundanceLayer.h"
#include "../../CSelectivityManager.h"
#include "../../CWorld.h"
#include "../../Selectivities/CSelectivity.h"

//**********************************************************************
// CAbundanceLayer::CAbundanceLayer(CAbundanceLayer *Layer = 0)
// Default Constructor
//**********************************************************************
CAbundanceLayer::CAbundanceLayer(CAbundanceLayer *Layer)
: CNumericLayer(Layer) {
  // Variables
  pWorld = CWorld::Instance();
  sType  = PARAM_ABUNDANCE;
}

//**********************************************************************
// void CAbundanceLayer::addCategory(string value)
// Add A Category to our Abundance Layer
//**********************************************************************
void CAbundanceLayer::addCategory(string value) {
  vCategoryList.push_back(value);
}

//**********************************************************************
// void CAbundanceLayer::addSelectivity(string value)
// Add a selectivity to our list.
//**********************************************************************
void CAbundanceLayer::addSelectivity(string value) {
  vSelectivityList.push_back(value);
}

//**********************************************************************
// void CAbundanceLayer::validate()
// Validate
//**********************************************************************
void CAbundanceLayer::validate() {
 try {
   // Base Validate
   CNumericLayer::validate();

   if (vCategoryList.size() == 0)
     errorMissing(PARAM_CATEGORIES);
   if (vSelectivityList.size() == 0)
     errorMissing(PARAM_SELECTIVITIES);
   if (bNormalize)
     throw string(ERROR_SUPPORTED_NORMALIZE);

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
    // Base Build
    CNumericLayer::build();

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

    CWorldSquare *pSquare = pWorld->getBaseSquare(RowIndex, ColIndex);
    return pSquare->getPopulation();

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
