//============================================================================
// Name        : CNumericLayer.cpp
// Author      : S.Rasmussen
// Date        : 1/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNumericLayer.h"

//**********************************************************************
// CNumericLayer::CNumericLayer(CNumericLayer *Layer = 0);
// Default Constructor
//**********************************************************************
CNumericLayer::CNumericLayer(CNumericLayer *Layer)
: CLayer(Layer) {

  // Default Variables
  dMin              = -1.0;
  dMax              = -1.0;

  // Allocate Space for our X (Width)
  pGrid = new double*[iHeight];

  // For Each X Add A Y (Width)
  for (int i = 0; i < iHeight; ++i) {
    pGrid[i] = new double[iWidth];
  }

  for (int i = 0; i < iHeight; ++i)
    for (int j = 0; j < iWidth; ++j)
      pGrid[i][j] = -1;

  // Copy Construct
  if (Layer != 0) {
    dMin = Layer->getMin();
    dMax = Layer->getMax();
  }
}

//**********************************************************************
// void CNumericLayer::setValue(int X, int Y, double Value)
// Default Set Value
//**********************************************************************
void CNumericLayer::setValue(int X, int Y, double Value) {
  try {
    throw string(ERROR_SUPPORTED_FUNCTION);

  } catch (string Ex) {
    Ex = "CNumericLayer.setValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// bool CNumericLayer::checkSpace(int RowIndex, int ColIndex)
// check if Space is Usable
//**********************************************************************
bool CNumericLayer::checkSpace(int RowIndex, int ColIndex) {
  try {
    throw string(ERROR_SUPPORTED_FUNCTION);

  } catch (string Ex) {
    Ex = "CNumericLayer.checkSpace(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// int CNumericLayer::countValidSpaces()
// count Valid Spaces
//**********************************************************************
int CNumericLayer::countValidSpaces() {
  try {
    throw string(ERROR_SUPPORTED_FUNCTION);

  } catch (string Ex) {
    Ex = "CNumericLayer.countValidSpaces(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNumericLayer::validate()
// validate
//**********************************************************************
void CNumericLayer::validate() {
  try {
    // Base Validate
    CLayer::validate();

  } catch (string Ex) {
    Ex = "CNumericLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNumericLayer::build()
// build
//**********************************************************************
void CNumericLayer::build() {
  try {
    // Normalize
    if (bNormalize) {
      double dTotal = 0.0;

      for (int i = 0; i < iHeight; ++i)
        for (int j = 0; j < iWidth; ++j)
          dTotal += pGrid[i][j];

      if (isZero(dTotal))
        return;

      if (!isSame(dTotal, 1.0)) { // Only normalize if not already done.
        for (int i = 0; i < iHeight; ++i)
          for (int j = 0; j < iWidth; ++j)
            pGrid[i][j] = (pGrid[i][j]) / dTotal;
      }
    }
  } catch (string Ex) {
    Ex = "CNumericLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNumericLayer::~CNumericLayer()
// Default De-Constructor
//**********************************************************************
CNumericLayer::~CNumericLayer() {
  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete [] pGrid[i];
      pGrid[i] = 0;
    }
    delete [] pGrid;
  }
}
