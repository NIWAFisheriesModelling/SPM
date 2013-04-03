//============================================================================
// Name        : CCompoundCategories.cpp
// Author      : A.Dunn
// Date        : 16/03/2013
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CCompoundCategories.h"
#include "CError.h"
#include "../Translations/Translations.h"

//**********************************************************************
// CProportionsAtAgeObservation::CProportionsAtAgeObservation()
// Default Constructor
//**********************************************************************
CCompoundCategories::CCompoundCategories() {

  // Default Values
  vvCategoryNames.resize(0);
  iNRows             = 0;
  vNElements.resize(0);
  iNCategories       = 0;
  pWorld = CWorld::Instance();

}

//**********************************************************************
// void  setCategories(vector<string> value);
//**********************************************************************
void CCompoundCategories::setCategories(vector<string> vCategoryNames) {

  try {
    // Neither first or last element may be the '+' symbol
    if (vCategoryNames[0] == CONFIG_AND || vCategoryNames[vCategoryNames.size()-1] == CONFIG_AND)
      CError::error("Invalid category: " + string(CONFIG_AND));

    // Otherwise get categories
    else {
      int iCount = 1;
      vector<string> tempCategories;
      tempCategories.push_back(vCategoryNames[0]);

      while ( iCount < (int)vCategoryNames.size()) {
        if (vCategoryNames[iCount] == CONFIG_AND) {
          ++iCount;
          tempCategories.push_back(vCategoryNames[iCount]);
         } else {
          vvCategoryNames.push_back(tempCategories);
          tempCategories.resize(0);
          tempCategories.push_back(vCategoryNames[iCount]);
        }
        ++iCount;
      }
      vvCategoryNames.push_back(tempCategories);
    }

    iNRows = vvCategoryNames.size();
    for (int i = 0; i < (int)vvCategoryNames.size(); ++i) {
      vNElements.push_back( vvCategoryNames[i].size() );
      iNCategories += vvCategoryNames[i].size();
    }

    for (int i = 0; i < (int)vvCategoryNames.size(); ++i) {
      vector<int> tempSelectivities;
      for (int j = 0; j < (int)vvCategoryNames[i].size(); ++j) {
        tempSelectivities.push_back( setCategoryIndex(i,j) );
      }
      vvCategoryIndex.push_back(tempSelectivities);
    }

  } catch (string &Ex) {
    Ex = "CCompoundCategories.setCompoundCategories()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// vector<string>  getCategoryNames(int row);
//**********************************************************************
vector<string> CCompoundCategories::getCategoryNames(int row) {

  return(vvCategoryNames[row]);

}

//**********************************************************************
// string getCategoryName(int row, int col);
//**********************************************************************
string CCompoundCategories::getCategoryName(int row, int col) {

  return(vvCategoryNames[row][col]);

}

//**********************************************************************
//  int setCompoundCategories(int row);
//**********************************************************************
int CCompoundCategories::setCategoryIndex(int row, int col) {

  int Index = pWorld->getCategoryIndexForName(vvCategoryNames[row][col]);

  return( Index );

}

//**********************************************************************
// static vector<string>  getCompoundCategories(int row);
//**********************************************************************
int CCompoundCategories::getCategoryIndex(int row, int col) {

  int Index = vvCategoryIndex[row][col];

  return( Index );

}
