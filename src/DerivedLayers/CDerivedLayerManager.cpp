//============================================================================
// Name        : CDerivedLayerManager.cpp
// Author      : S.Rasmussen
// Date        : 30/03/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
//============================================================================

// Headers
#include <iostream>

#include "CDerivedLayerManager.h"
#include "CDerivedLayer.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Using
using std::cout;
using std::endl;

// Singleton Variable
boost::thread_specific_ptr<CDerivedLayerManager> CDerivedLayerManager::clInstance;

//**********************************************************************
// CDerivedLayerManager::CDerivedLayerManager()
// Default Constructor
//**********************************************************************
CDerivedLayerManager::CDerivedLayerManager() {
}

//**********************************************************************
// CDerivedLayerManager* CDerivedLayerManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CDerivedLayerManager* CDerivedLayerManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CDerivedLayerManager());
  return clInstance.get();
}

//**********************************************************************
// void CDerivedLayerManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CDerivedLayerManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CDerivedLayerManager::addDerivedLayer(CDerivedLayer *DerivedLayer)
// Add Derived Layer to our list
//**********************************************************************
void CDerivedLayerManager::addDerivedLayer(CDerivedLayer *DerivedLayer) {
  vDerivedLayers.push_back(DerivedLayer);
}

//**********************************************************************
// CDerivedLayer* CDerivedLayerManager::getDerivedLayer(string label)
// Get our Derived Layer
//**********************************************************************
CDerivedLayer* CDerivedLayerManager::getDerivedLayer(string label) {
  try {
    foreach(CDerivedLayer *DerivedLayer, vDerivedLayers) {
      if (DerivedLayer->getLabel() == label)
        return DerivedLayer;
    }

    CError::errorUnknown(PARAM_DERIVED_LAYER, label);

  } catch (string &Ex) {
    Ex = "CDerivedLayerManager.validate()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CDerivedLayerManager::validate()
// Validate our Derived Layers
//**********************************************************************
void CDerivedLayerManager::validate() {
  try {

    foreach(CDerivedLayer *DerivedLayer, vDerivedLayers) {
      DerivedLayer->validate();
    }

  } catch (string &Ex) {
    Ex = "CDerivedLayerManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedLayerManager::build()
// Build our Derived Layers
//**********************************************************************
void CDerivedLayerManager::build() {
  try {

    foreach(CDerivedLayer *DerivedLayer, vDerivedLayers) {
      DerivedLayer->build();
    }

  } catch (string &Ex) {
    Ex = "CDerivedLayerManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedLayerManager::rebuild()
// ReBuild our Derived Layers
//**********************************************************************
void CDerivedLayerManager::rebuild() {
  try {

    foreach(CDerivedLayer *DerivedLayer, vDerivedLayers) {
      DerivedLayer->rebuild();
    }

  } catch (string &Ex) {
    Ex = "CDerivedLayerManager.rebuild()->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// void CDerivedLayerManager::calculate()
// Calculate Derived Layers
//**********************************************************************
void CDerivedLayerManager::calculate() {
  foreach(CDerivedLayer *DerivedLayer, vDerivedLayers) {
    DerivedLayer->calculate();
  }
}

//**********************************************************************
// void CDerivedLayerManager::calculate(bool initialisationPhase)
// Calculate Derived Layers
//**********************************************************************
void CDerivedLayerManager::calculate(int initialisationPhase) {

  foreach(CDerivedLayer *DerivedLayer, vDerivedLayers) {
    DerivedLayer->calculate(initialisationPhase);
  }
}

//**********************************************************************
// CDerivedLayerManager::~CDerivedLayerManager()
// Destructor
//**********************************************************************
CDerivedLayerManager::~CDerivedLayerManager() {
  foreach(CDerivedLayer *DerivedLayer, vDerivedLayers) {
    delete DerivedLayer;
  }
  vDerivedLayers.clear();
}
