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
#include "../../../Helpers/CComparer.h"

//**********************************************************************
// CNumericLayer::CNumericLayer();
// Default Constructor
//**********************************************************************
CNumericLayer::CNumericLayer() {

  // Default Variables
  dMin              = -1.0;
  dMax              = -1.0;
  pGrid             = 0;
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

    // Allocate Space for our X (Width)
    pGrid = new double*[iHeight];
    for (int i = 0; i < iHeight; ++i)
      pGrid[i] = new double[iWidth];

  } catch (string Ex) {
    Ex = "CNumericLayer.validate(" + getLabel() + ")->" + Ex;
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
