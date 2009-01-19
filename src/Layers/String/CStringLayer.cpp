//============================================================================
// Name        : CStringLayer.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CStringLayer.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CStringLayer::CStringLayer(CStringLayer *Layer = 0)
// Default Constructor
//**********************************************************************
CStringLayer::CStringLayer(CStringLayer *Layer)
: CLayer(Layer) {

  // Build 2D Array
  pGrid = new string*[iHeight];
  for (int i = 0; i < iHeight; ++i) {
    pGrid[i] = new string[iWidth];
  }

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_ROW);
}

//**********************************************************************
// void CStringLayer::setValue(int Row, int Col, string Value)
// Add Value to Grid
//**********************************************************************
void CStringLayer::setValue(int Row, int Col, string Value) {
#ifndef OPTIMISE
  try {
    if (Row > iHeight)
      CError::errorGreaterThan(PARAM_ROW, PARAM_LAYER_HEIGHT);
    if (Col > iWidth)
      CError::errorGreaterThan(PARAM_COLUMN, PARAM_LAYER_WIDTH);
    if (Row <= 0)
      CError::errorLessThanEqualTo(PARAM_ROW, PARAM_ZERO);
    if (Col <= 0)
      CError::errorLessThanEqualTo(PARAM_COLUMN, PARAM_ZERO);
#endif

    pGrid[(Row-1)][(Col-1)] = Value;

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CStringLayer.setValue()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// string CStringLayer::getValue(int RowIndex, int ColIndex)
// get Value
//**********************************************************************
string CStringLayer::getValue(int RowIndex, int ColIndex) {
  // Vars
  string sRet = "";
#ifndef OPTIMISE
  try {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);
#endif

    // Assign Ret
    sRet = pGrid[RowIndex][ColIndex];

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CStringLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return sRet;
}

//**********************************************************************
// void CStringLayer::Validate()
// Validate
//**********************************************************************
void CStringLayer::validate() {
  try {
    // Base Validate
    CLayer::validate();

    // Fill a new vector with our row information
    vector<string> vData;

    pParameterList->fillVector(vData, PARAM_DATA);

    int iRow  = 0;
    int iCol  = 0;

    for (int i = 0; i < (int)vData.size(); ++i) {
      if (vData[i] == PARAM_DATA)
        continue;

      if (iRow >= iHeight)
        throw string("Too much data"); // TODO: Add CError

      if (iCol >= iWidth) {
        iCol = 0;
        iRow++;
      }

      pGrid[iRow][iCol] = vData[i];
      iCol++;
    }

    if ((iRow < iHeight) || (iCol < iWidth))
      throw string("Not enough data"); // TODO: Add CError

  } catch(string Ex) {
    Ex = "CStringLayer.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CStringLayer::~CStringLayer()
// Default De-Constructor
//**********************************************************************
CStringLayer::~CStringLayer() {
  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete [] pGrid[i];
      pGrid[i] = 0;
    }

    delete [] pGrid;
  }
}
