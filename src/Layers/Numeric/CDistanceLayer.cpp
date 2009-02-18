//============================================================================
// Name        : CDistanceLayer.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CDistanceLayer.h"
#include "../../World/CWorld.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CDistanceLayer::CDistanceLayer()
// Default Constructor
//**********************************************************************
CDistanceLayer::CDistanceLayer() {
}

//**********************************************************************
// double CDistanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0)
// Get The Value Fromo ur Distance Layer
//**********************************************************************
double CDistanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0) {
#ifndef OPTIMIZE
  try {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);

  } catch (string Ex) {
    Ex = "CDistanceLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  // Adjust For our Location in Distance Layers
  RowIndex = abs(RowIndex - TargetRow);
  ColIndex = abs(ColIndex - TargetCol);

  // Assign Ret
  return pGrid[RowIndex][ColIndex];
}

//**********************************************************************
// void CDistanceLayer::build()
// build
//**********************************************************************
void CDistanceLayer::build() {
  try {

    // Fill The Grid With The Distances
    for (int i = 0; i < iHeight; ++i) {
      for (int j = 0; j < iWidth; ++j) {
        pGrid[i][j]= sqrt( (double)((i*i)+(j*j)) );
      }
    }

  } catch (string Ex) {
    Ex = "CDistanceLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// CDistanceLayer::~CDistanceLayer()
// Default De-Constructor
//**********************************************************************
CDistanceLayer::~CDistanceLayer() {
}
