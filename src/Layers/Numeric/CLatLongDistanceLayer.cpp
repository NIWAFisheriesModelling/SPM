//============================================================================
// Name        : CLatLongDistanceLayer.cpp
// Author      : A.Dunn
// Date        : 11/08/2014
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CLatLongDistanceLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/DefinedValues.h"
#include "../../Layers/CLayerManager.h"
#include "../../World/CWorld.h"

//**********************************************************************
// CLatLongDistanceLayer::CLatLongDistanceLayer()
// Default Constructor
//**********************************************************************
CLatLongDistanceLayer::CLatLongDistanceLayer() {
  sType = PARAM_LAT_LONG_DISTANCE;

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_LONG_LAYER);
  pParameterList->registerAllowed(PARAM_LAT_LAYER);

}

//**********************************************************************
// double CLatLongDistanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0)
// Get The Value Fromo ur LatLongDistance Layer
//**********************************************************************
double CLatLongDistanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol) {

  try {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);

  } catch (string &Ex) {
    Ex = "CLatLongDistanceLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  double dLong1 = pLongLayer->getValue(RowIndex, ColIndex);
  double dLat1  = pLatLayer->getValue(RowIndex, ColIndex);
  double dLong2 = pLongLayer->getValue(TargetRow, TargetCol);
  double dLat2  = pLatLayer->getValue(TargetRow, TargetCol);
  double dDistance = haversine(dLong1, dLat1, dLong2, dLat2);

  return dDistance;

}

//**********************************************************************
// double CLatLongDistanceLayer::deg2rad(const double deg)
// Convert degrees to radians
//**********************************************************************
double CLatLongDistanceLayer::deg2rad(double deg) {
    double dResult = deg / 180.0 * PI;
    return(dResult);
}

//**********************************************************************
// double CLatLongDistanceLayer::haversine(const double long1, const double lat1, const double long2, const double lat2)
// calcuate distanced using the haversine formula
//**********************************************************************
double CLatLongDistanceLayer::haversine(const double long1, const double lat1, const double long2, const double lat2) {

    // Convert to radians
    double dLong1 = deg2rad(long1);
    double dLat1  = deg2rad(lat1);
    double dLong2 = deg2rad(long2);
    double dLat2  = deg2rad(lat2);

    // Haversine formula
    double dR = 6371; // Earth mean radius [km]
    double dDeltaLong = (dLong2 - dLong1);
    double dDeltaLat = (dLat2 - dLat1);
    double dA = pow(sin(dDeltaLat * 0.5), 2.0) + cos(dLat1) * cos(dLat2) * pow(sin(dDeltaLong * 0.5), 2.0);

    return(dR * 2.0 * asin(std::min(1.0, sqrt(dA))));  // return distance in kilometres

  }

//**********************************************************************
// void CLatLongDistanceLayer::validate()
// Validate our LatLongDistance Lyer
//**********************************************************************
void CLatLongDistanceLayer::validate() {
  try {

    sLatLayer  = pParameterList->getString(PARAM_LAT_LAYER);
    sLongLayer = pParameterList->getString(PARAM_LONG_LAYER);

    // Base
    CNumericLayer::validate();

  } catch (string &Ex) {
    Ex = "CLatLongDistanceLayer.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLatLongDistanceLayer::build()
// build
//**********************************************************************
void CLatLongDistanceLayer::build() {
  try {

    // Get our Layers and validate values
    pLatLayer = CLayerManager::Instance()->getNumericLayer(sLatLayer);
    pLongLayer = CLayerManager::Instance()->getNumericLayer(sLongLayer);

    for (int i = 0; i < iHeight; ++i) {
      for (int j = 0; j < iWidth; ++j) {
        double dLat = pLatLayer->getValue(i, j);
        double dLong = pLongLayer->getValue(i, j);
        if (dLat < -90)
          CError::errorLessThan(PARAM_LAT_LAYER,"-90");
        if (dLat > 90)
          CError::errorGreaterThan(PARAM_LAT_LAYER,"90");
        if (dLong < 0)
          CError::errorLessThan(PARAM_LONG_LAYER,"0");
        if (dLong > 360)
          CError::errorGreaterThan(PARAM_LONG_LAYER,"360");
      }
    }

  } catch (string &Ex) {
    Ex = "CLatLongDistanceLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CLatLongDistanceLayer::~CLatLongDistanceLayer()
// Default De-Constructor
//**********************************************************************
CLatLongDistanceLayer::~CLatLongDistanceLayer() {
}
