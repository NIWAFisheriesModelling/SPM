//============================================================================
// Name        : CBiomassLayer.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBiomassLayer.h"

//**********************************************************************
// CBiomassLayer::CBiomassLayer()
// Default constructor
//**********************************************************************
CBiomassLayer::CBiomassLayer() {

  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHTS);
}

//**********************************************************************
// double CBiomassLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// get the value from our layer
//**********************************************************************
double CBiomassLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol) {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CBiomassLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CBiomassLayer::validate()
// Validate the layer
//**********************************************************************
void CBiomassLayer::validate() {
  try {
    // Base
    CNumericLayer::validate();

    // Get our parameters
    pParameterList->fillVector(vCategories, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivities, PARAM_SELECTIVITIES);
    pParameterList->fillVector(vSizeWeights, PARAM_SIZE_WEIGHTS);

    // TODO: Add Vector size checks against each other
    throw string("Not yet implemented"); // TODO: Implement this

  } catch (string Ex) {
    Ex = "CBiomassLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// void CBiomassLayer::build()
// Build our layer
//**********************************************************************
void CBiomassLayer::build() {
  try {
    throw string("Not yet implemented"); // TODO: Implement this
  } catch (string Ex) {
    Ex = "CBiomassLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CBiomassLayer::~CBiomassLayer()
// Destructor
//**********************************************************************
CBiomassLayer::~CBiomassLayer() {

}
