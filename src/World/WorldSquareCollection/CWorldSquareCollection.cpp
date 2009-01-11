//============================================================================
// Name        : CWorldSquareCollection.cpp
// Author      : S.Rasmussen
// Date        : 11/09/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CWorldSquareCollection.h"
#include "../CWorldSquare.h"
#include "../CWorld.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CWorldSquareCollection::CWorldSquareCollection(CWorldSquareCollection *Collection)
// Default Constructor
//**********************************************************************
CWorldSquareCollection::CWorldSquareCollection(CWorldSquareCollection *Collection)
: CBaseBuildableObject(Collection) {

  // Set Variables
  pLayer      = 0;

  // Copy Construct
  if (Collection != 0) {
    pLayer  = Collection->getLayer();
  }
}

//**********************************************************************
// double CWorldSquareCollecton::getPopulationForAge(string group, int ageIndex)
// Get the population from our group for age.
//**********************************************************************
double CWorldSquareCollection::getPopulationForAge(string group, int ageIndex) {

  double dRet = 0.0;

  foreach(CWorldSquare* WorldSquare, mvCollection[group]) {
    dRet += WorldSquare->getPopulationForAge(ageIndex);
  }

  return dRet;;
}

//**********************************************************************
// double CWorldSquareCollection::getPopulationInCategoryForAge(string group, int ageIndex, int categoryIndex)
//
//**********************************************************************
double CWorldSquareCollection::getPopulationInCategoryForAge(string group, int ageIndex, int categoryIndex) {

  double dRet = 0.0;

  foreach(CWorldSquare *WorldSquare, mvCollection[group]) {
    dRet += WorldSquare->getPopulationInCategoryForAge(ageIndex, categoryIndex);
  }

  return dRet;
}

//**********************************************************************
// double CWorldSquareCollection::getPopulationForCategory(string group, int categoryIndex)
//
//**********************************************************************
double CWorldSquareCollection::getPopulationForCategory(string group, int categoryIndex) {

  double dRet = 0.0;

  foreach(CWorldSquare *WorldSquare, mvCollection[group]) {
    dRet += WorldSquare->getPopulationForCategory(categoryIndex);
  }

  return dRet;
}

//**********************************************************************
// void CWorldSquareCollection::validate()
// Validate
//**********************************************************************
void CWorldSquareCollection::validate() {
  try {
    // Validate local variables
    if (pLayer == 0)
      CError::errorMissing(PARAM_LAYER_NAME);

  } catch (string Ex) {
    Ex = "CWorldSquareCollection.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CWorldSquareCollection::build()
// Build
//**********************************************************************
void CWorldSquareCollection::build() {
  try {

    // Build our collection. We do this by looping through the layer and getting
    // the world square for each label. Then we we add this into the map<vector>
    CWorld *pWorld = CWorld::Instance();

    for (int i = 0; i < pLayer->getHeight(); ++i) {
      for (int j = 0; j < pLayer->getWidth(); ++j)
        mvCollection[pLayer->getValue(i,j)].push_back(pWorld->getBaseSquare(i, j));
    }

  } catch (string Ex) {
    Ex = "CWorldSquareCollection.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CWorldSquareCollection::~CWorldSquareCollection()
// Destructor
//**********************************************************************
CWorldSquareCollection::~CWorldSquareCollection() {

}
