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

//**********************************************************************
// CStringLayer::CStringLayer(CStringLayer *Layer = 0)
// Default Constructor
//**********************************************************************
CStringLayer::CStringLayer(CStringLayer *Layer)
: CLayer(Layer) {

  // Allocate Space for our X (Width)
  pGrid = new string*[iHeight];

  // For Each X Add A Y (Height)
  for (int i = 0; i < iHeight; ++i) {
    pGrid[i] = new string[iWidth];
  }

  for (int i = 0; i < iHeight; ++i)
    for (int j = 0; j < iWidth; ++j)
      pGrid[i][j] = "";

  // Set Type
  sType = "string";

  // Copy Construct
  if (Layer != 0) {
    // Copy Values Over
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j)
        pGrid[i][j] = Layer->getValue(i, j);
  }
}

//**********************************************************************
// void CStringLayer::setValue(int Row, int Col, string Value)
// Add Value to Grid
//**********************************************************************
void CStringLayer::setValue(int Row, int Col, string Value) {
#ifndef OPTIMISE
  try {
    if (Row > iHeight)
          errorGreaterThan(PARAM_ROW, PARAM_LAYER_HEIGHT);
    if (Col > iWidth)
      errorGreaterThan(PARAM_COLUMN, PARAM_LAYER_WIDTH);
    if (Row <= 0)
      errorLessThanEqualTo(PARAM_ROW, PARAM_ZERO);
    if (Col <= 0)
      errorLessThanEqualTo(PARAM_COLUMN, PARAM_ZERO);
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
      errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);
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

    // Make sure all spots have been filled.
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j)
        if (pGrid[i][j] == "")
          throw string(ERROR_MISSING_LAYER_SPOT + sLabel);

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
