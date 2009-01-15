//============================================================================
// Name        : CBiomassDensityLayer.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBiomassDensityLayer.h"

//**********************************************************************
// CBiomassDensityLayer::CBiomassDensityLayer(CBiomassDensityLayer *Layer)
// Default constructor
//**********************************************************************
CBiomassDensityLayer::CBiomassDensityLayer(CBiomassDensityLayer *Layer)
: CNumericLayer(Layer) {

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHTS);
}

//**********************************************************************
// double CBiomassDensityLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// Get the value from our layer
//**********************************************************************
double CBiomassDensityLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol) {
  try {
    throw string("Not yet implemented"); // TODO: Implementt this
  } catch (string Ex) {
    Ex = "CBiomassDensityLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CBiomassDensityLayer::validate()
// Validate the layer
//**********************************************************************
void CBiomassDensityLayer::validate() {
  try {
    // Base
    CNumericLayer::validate();

    // Populate our parameters
    pParameterList->fillVector(vCategories, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivities, PARAM_SELECTIVITIES);
    pParameterList->fillVector(vSizeWeights, PARAM_SIZE_WEIGHTS);

  } catch (string Ex) {
    Ex = "CBiomassDensityLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBiomassDensityLayer::build()
// Build the layer
//**********************************************************************
void CBiomassDensityLayer::build() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CBiomassDensityLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CBiomassDensityLayer::~CBiomassDensityLayer()
// Destructor
//**********************************************************************
CBiomassDensityLayer::~CBiomassDensityLayer() {

}
