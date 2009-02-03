//============================================================================
// Name        : CLayerManager.cpp
// Author      : S.Rasmussen
// Date        : 11/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : << See CLayerManager.h >>
// $Date$
//============================================================================

// Local Headers
#include "CLayerManager.h"
#include "CLayer.h"
#include "Numeric/Base/CNumericLayer.h"
#include "String/CStringLayer.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Single Static variable
boost::thread_specific_ptr<CLayerManager> CLayerManager::clInstance;

//**********************************************************************
// CLayerManager::CLayerManager()
// Default Constructor
//**********************************************************************
CLayerManager::CLayerManager() {
  // Default Vars
  vLayerList.clear();
}

//**********************************************************************
// CLayerManager* CLayerManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CLayerManager* CLayerManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CLayerManager());
  return clInstance.get();
}

//**********************************************************************
// void CLayerManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CLayerManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CLayerManager::addLayer(CLayer *Layer)
// Add A Layer to our List
//**********************************************************************
void CLayerManager::addLayer(CLayer* Layer) {
  vLayerList.push_back(Layer);
}

//**********************************************************************
// CLayer* CLayerManager::getLayer(int index)
// Get layer from our vector @ index
//**********************************************************************
CLayer* CLayerManager::getLayer(int index) {
  try {
    if (index >= (int)vLayerList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_LAYERS);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vLayerList[index];

  } catch (string Ex) {
    Ex = "CLayerManager.gerLayer()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNumericLayer* CLayerManager::getNumericLayer(string Label)
// Return our Numeric Layer
//**********************************************************************
CNumericLayer* CLayerManager::getNumericLayer(string Label) {
  try {
    // Loop Through Layers
    foreach(CLayer* Layer, vLayerList) {
       if (Layer->getLabel() == Label) {
        // Cast and Check if is Numeric
        CNumericLayer *pPtr = dynamic_cast<CNumericLayer*>(Layer);
        if (pPtr == 0)
          throw string(ERROR_INVALID_LAYER_TYPE_NUMERIC + Label);

        // Otherise, Cool as
        return pPtr;
      }
    }

    throw string(ERROR_UNKNOWN_LAYER + Label);

  } catch(string Ex) {
    Ex = "CLayerManager.getNumericLayer()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// CStringLayer* CLayerManager::getStringLayer(string Label)
// Get String Layer
//**********************************************************************
CStringLayer* CLayerManager::getStringLayer(string Label) {
  try {
    // Loop Through Layers
    foreach(CLayer* Layer, vLayerList) {
      if (Layer->getLabel() == Label) {
        // Cast and Check if is Numeric
        CStringLayer *pPtr = dynamic_cast<CStringLayer*>(Layer);
        if (pPtr == 0)
          throw string(ERROR_INVALID_LAYER_TYPE_STRING + Label);

        // Otherise, Cool as
        return pPtr;
      }
    }

    throw string(ERROR_UNKNOWN_LAYER + Label);

  } catch(string Ex) {
    Ex = "CLayerManager.getStringLayer()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CLayerManager::clone(CLayerManager *Manager)
// Clone the target layer manager
//**********************************************************************
void CLayerManager::clone(CLayerManager *Manager) {
  try {
    for (int i = 0; i < Manager->getLayerCount(); ++i) {
      CLayer *pLayer = Manager->getLayer(i);
      vLayerList.push_back( pLayer->clone());
    }

  } catch (string Ex) {
    Ex = "CLayerManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerManager::validate()
// Validate Layers
//**********************************************************************
void CLayerManager::validate() {
  try {
    // Validate The Layers
    foreach(CLayer *Layer, vLayerList) {
      Layer->validate();
    }

    // Look for Duplicate Labels
    map<string, int>            mLabelList;
    foreach(CLayer* Layer, vLayerList) {
      // Increase Count for this label
      mLabelList[Layer->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[Layer->getLabel()] > 1)
        throw string(ERROR_DUPLICATE_LABEL + Layer->getLabel());
    }

  } catch(string Ex) {
    Ex = "CLayerManager.validate->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerManager::build()
// Build our Dynamic Layers
//**********************************************************************
void CLayerManager::build() {
  try {
    foreach(CLayer *Layer, vLayerList) {
      Layer->build();
    }
  } catch (string Ex) {
    Ex = "CLayerManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CLayerManager::~CLayerManager()
// Default De-Constructor
//**********************************************************************
CLayerManager::~CLayerManager() {
  // Delete Our Layers
  foreach(CLayer *Layer, vLayerList) {
    delete Layer;
  }

  // Clear Vector
  vLayerList.clear();
}
