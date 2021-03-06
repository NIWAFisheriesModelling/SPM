//============================================================================
// Name        : CDoubleLayer.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Global Headers
#include <iostream>
#include <boost/lexical_cast.hpp>

// Local Includes
#include "CDoubleLayer.h"
#include "../../World/CWorld.h"
#include "../../World/CWorldSquare.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"

// Namespace
using std::cout;
using std::endl;

//**********************************************************************
// CDoubleLayer::CDoubleLayer()
// Default Constructor
//**********************************************************************
CDoubleLayer::CDoubleLayer() {

  sType = PARAM_DOUBLE;

  // Register Allowed Parameters
  pParameterList->registerAllowed(PARAM_DATA);
  pParameterList->registerAllowed(PARAM_RESCALE);

}

//**********************************************************************
// double CDoubleLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0)
// Get Value From Our Layer
//**********************************************************************
double CDoubleLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0) {
#ifndef OPTIMIZE
  try {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);

  } catch (string &Ex) {
    Ex = "CDoubleLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return pGrid[RowIndex][ColIndex];
}

//**********************************************************************
// void CDoubleLayer::addValue(int Row, int Col, double Value)
// Add Value to our Grid
//**********************************************************************
void CDoubleLayer::setValue(int Row, int Col, double Value) {
#ifndef OPTIMIZE
  try {
    if (Row > iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW, PARAM_LAYER_HEIGHT);
    if (Col > iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN, PARAM_LAYER_WIDTH);
    if (Row <= 0)
      CError::errorLessThanEqualTo(PARAM_ROW, PARAM_ZERO);
    if (Col <= 0)
      CError::errorLessThanEqualTo(PARAM_COLUMN, PARAM_ZERO);

  } catch(string &Ex) {
    Ex = "CDoubleLayer.addValue()->" + Ex;
    throw Ex;
  }
#endif

  pGrid[(Row-1)][(Col-1)] = Value;
}

//**********************************************************************
// void CDoubleLayer::validate()
// Validate Our Layer
//**********************************************************************
void CDoubleLayer::validate() {
  try {
    // Base Validate
    CNumericLayer::validate();


    if (pParameterList->hasParameter(PARAM_RESCALE)) {
      // Get the value
      dRescale = pParameterList->getDouble(PARAM_RESCALE);
      // register estimable parameters
      registerEstimable(PARAM_RESCALE, &dRescale);
    }

    // Fill a new vector with our row information
    vector<string> vData;
    pParameterList->fillVector(vData, PARAM_DATA);

    int iRow  = 0;
    int iCol  = 0;

    for (int i = 0; i < (int)vData.size(); ++i) {
      if (vData[i] == PARAM_DATA)
        continue;

      // Read data and if enough on theis row, then start filling out the next row
      if (iCol >= iWidth) {
        iCol = 0;
        iRow++;
      }

      // Read data and if too much data, report an error
      if (iRow >= iHeight)
        CError::errorTooMuch(PARAM_DATA);

      try {
        // Set grid data
        pGrid[iRow][iCol] = boost::lexical_cast<double>(vData[i]);
        // register as estimable
        registerEstimable(PARAM_DATA, i, &pGrid[iRow][iCol]);
      } catch (boost::bad_lexical_cast) {
        string Ex = string("Non-numeric value in layer ") + getLabel();
        throw Ex;
      }
      iCol++;
    }

    if (((iRow+1) != iHeight) || (iCol != iWidth))
      CError::errorNotEnough(PARAM_DATA);

  } catch(string &Ex) {
    Ex = "CDoubleLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double getLayerMin();
// Get layer value min
//**********************************************************************
double CDoubleLayer::getLayerMin() {
  try {

    double dMin = pGrid[0][0];

    for (int i = 0; i < iHeight; ++i) {
      for (int j = 0; j < iWidth; ++j) {
        dMin = std::min(dMin,pGrid[i][j]);
      }
    }

    return(dMin);

  } catch (string &Ex) {
    Ex = "CDoubleLayer.getLayerMin(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// double getLayerMax();
// Get layer value max
//**********************************************************************
double CDoubleLayer::getLayerMax() {
  try {

    double dMax = pGrid[0][0];

    for (int i = 0; i < iHeight; ++i) {
      for (int j = 0; j < iWidth; ++j) {
        dMax = std::max(dMax,pGrid[i][j]);
      }
    }

    return(dMax);

  } catch (string &Ex) {
    Ex = "CDoubleLayer.getLayerMax(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// void CDoubleLayer::build()
// Build our layer
//**********************************************************************
void CDoubleLayer::build() {
  try {

    if (pParameterList->hasParameter(PARAM_RESCALE)) {
      // Rescale the layer to 0-1 range
      double dTotal = 0.0;

      for (int i = 0; i < iHeight; ++i)
        for (int j = 0; j < iWidth; ++j)
          dTotal += pGrid[i][j];

      if (!CComparer::isZero(dTotal)) {
        if (!CComparer::isEqual(dTotal, dRescale)) { // Only normalize if not already done.
          for (int i = 0; i < iHeight; ++i) {
            for (int j = 0; j < iWidth; ++j) {
              pGrid[i][j] = (pGrid[i][j]) / dTotal;
              pGrid[i][j] *= dRescale;
            }
          }
        }
      }
    }

  } catch (string &Ex) {
    Ex = "CDoubleLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDoubleLayer::~CDoubleLayer()
// Default De-Constructor
//**********************************************************************
CDoubleLayer::~CDoubleLayer() {
}
