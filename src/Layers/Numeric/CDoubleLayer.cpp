//============================================================================
// Name        : CDoubleLayer.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Includes
#include "CDoubleLayer.h"
#include "../../World/CWorld.h"
#include "../../World/CWorldSquare.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CDoubleLayer::CDoubleLayer(CDoubleLayer *Layer = 0);
// Default Constructor
//**********************************************************************
CDoubleLayer::CDoubleLayer(CDoubleLayer *Layer)
: CNumericLayer(Layer) {

  // Register Allowed Parameters
  pParameterList->registerAllowed(string(PARAM_ROW) + string(CONFIG_WILDCARD_MULTIPLE));

  // Copy Construct
  if (Layer != 0) {
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j)
        pGrid[i][j] = Layer->getValue(i, j, 0, 0);
  }
}

//**********************************************************************
// double CDoubleLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0)
// Get Value From Our Layer
//**********************************************************************
double CDoubleLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0) {
#ifndef OPTIMISE
  try {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);
#endif

    // Assign Ret
    return pGrid[RowIndex][ColIndex];

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CDoubleLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CDoubleLayer::addValue(int Row, int Col, double Value)
// Add Value to our Grid
//**********************************************************************
void CDoubleLayer::setValue(int Row, int Col, double Value) {
#ifndef OPTIMISE
  try {
    if (Row > iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW, PARAM_LAYER_HEIGHT);
    if (Col > iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN, PARAM_LAYER_WIDTH);
    if (Row <= 0)
      CError::errorLessThanEqualTo(PARAM_ROW, PARAM_ZERO);
    if (Col <= 0)
      CError::errorLessThanEqualTo(PARAM_COLUMN, PARAM_ZERO);
#endif

    pGrid[(Row-1)][(Col-1)] = Value;

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CDoubleLayer.addValue()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// bool CDoubleLayer::checkSpace(int RowIndex, int ColIndex)
// Check This Grid Spot. Is it Valid for our Check
//**********************************************************************
bool CDoubleLayer::checkSpace(int RowIndex, int ColIndex) {
#ifndef OPTIMISE
  try {
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);
#endif

    // Is this simple T/F Layer
    if ( (CComparer::isEqual(dMin, -1.0)) && (CComparer::isEqual(dMax, -1.0)) ) {
      if ( (pGrid[RowIndex][ColIndex] <= (1.0+ZERO)) && (pGrid[RowIndex][ColIndex] >= (1.0-ZERO)) ) {
        return true;
      } else {
        return false;
      }
    }

    // Otherwise, Does it fall within the Min/Max Range
    if ( (pGrid[RowIndex][ColIndex] <= (dMax+ZERO)) && (pGrid[RowIndex][ColIndex] >= (dMin-ZERO)) )
      return true;

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CDoubleLayer.checkSpace()->" + Ex;
    throw Ex;
  }
#endif
  return false;

}

//**********************************************************************
// int CDoubleLayer::countValidSpaces()
// Count How Many Valid Spots We Have Against World
//**********************************************************************
int CDoubleLayer::countValidSpaces() {
#ifndef OPTIMISE
  try {
#endif
    // Variables
    CWorld *pWorld    = CWorld::Instance();
    double dCurMin    = 1.0;
    double dCurMax    = 1.0;
    int    iRet       = 0;

    // Set Min/Max
    if ( (CComparer::isEqual(dMin, -1.0)) && (CComparer::isEqual(dMax, -1.0)) ) {
      dCurMin = dMin;
      dCurMax = dMax;
    }

    // Check Sizing
    if (pWorld->getHeight() != iHeight)
      CError::errorNotEqual(PARAM_LAYER_HEIGHT, PARAM_NROWS);
    if (pWorld->getWidth() != iWidth)
      CError::errorNotEqual(PARAM_LAYER_WIDTH, PARAM_NCOLS);

    // Loop Through World
    for (int i = 0; i < iHeight; ++i) {
      for (int j = 0; j < iWidth; ++j) {
        // Check if Space is disabled on World first
        if (!pWorld->getBaseSquare(i, j)->getEnabled())
          continue;

        // Check if our Grid Spot Matches Min/Max
        if ( (pGrid[i][j] >= (dCurMin-ZERO)) && (pGrid[i][j] <= (dCurMax+ZERO)) )
          iRet++;
      }
    }

    return iRet;

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CDoubleLayer.countValidSpaces()->" + Ex;
    throw Ex;
  }

  return -1;
#endif
}

//**********************************************************************
// void CDoubleLayer::validate()
// Validate Our Layer
//**********************************************************************
void CDoubleLayer::validate() {
  try {
    // Base Validate
    CNumericLayer::validate();

    // Fill Our Array
    if (pParameterList->countMatches(string(PARAM_ROW) + string(CONFIG_WILDCARD_MULTIPLE)) != iHeight)
      throw string("Not enough rows submitted for layer");

    for (int i = 0; i < iHeight; ++i) {
      string name = pParameterList->getMatchFullName(string(PARAM_ROW) + string(CONFIG_WILDCARD_MULTIPLE), i);

      if (pParameterList->countParameterValues(name) != iWidth)
        throw string(name + " doesn't have correct number of values");

      pParameterList->fillArray(pGrid[i], iWidth, name);
    }

    // Make sure all spots have been filled.
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j)
        if (pGrid[i][j] == -1)
          throw string(ERROR_MISSING_LAYER_SPOT + sLabel);

  } catch(string Ex) {
    Ex = "CDoubleLayer.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDoubleLayer::~CDoubleLayer()
// Default De-Constructor
//**********************************************************************
CDoubleLayer::~CDoubleLayer() {
}
