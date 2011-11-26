//============================================================================
// Name        : CAbundanceDensityLayer.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAbundanceDensityLayer.h"

// TODO: (Alistair) Implement Abundance Density Layer

//**********************************************************************
// CAbundanceDensityLayer::CAbundanceDensityLayer()
// Default Constructor
//**********************************************************************
CAbundanceDensityLayer::CAbundanceDensityLayer() {

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
}

//**********************************************************************
// double CAbundanceDensityLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// Return the value from the layer
//**********************************************************************
double CAbundanceDensityLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol) {
  try {
    throw string("Not yet implemented");
  } catch (string &Ex) {
    Ex = "CAbundanceDensityLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CAbundanceDensityLayer::validate()
// Validate the layer
//**********************************************************************
void CAbundanceDensityLayer::validate() {
  try {
    // Base
    CNumericLayer::validate();

    // Get parameters
    pParameterList->fillVector(vCategories, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivities, PARAM_SELECTIVITIES);

  } catch (string &Ex) {
    Ex = "CAbundanceDensityLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAbundanceDensityLayer::build()
// Build the layer
//**********************************************************************
void CAbundanceDensityLayer::build() {
  try {
    throw string("Not yet implemented");
  } catch (string &Ex) {
    Ex = "CAbundanceDensityLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CAbundanceDensityLayer::~CAbundanceDensityLayer()
// Destructor
//**********************************************************************
CAbundanceDensityLayer::~CAbundanceDensityLayer() {
}
