//============================================================================
// Name        : CDerivedLayerReport.cpp
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// headers
#include <boost/lexical_cast.hpp>

// Local headers
#include "CDerivedLayerReport.h"
#include "../../DerivedLayers/CDerivedLayerManager.h"
#include "../../DerivedLayers/CDerivedLayer.h"

//**********************************************************************
// CDerivedLayerReport::CDerivedLayerReport()
// Constructor
//**********************************************************************
CDerivedLayerReport::CDerivedLayerReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;
  pDerivedLayer  = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_DERIVED_LAYER);
  pParameterList->registerAllowed(PARAM_INITIALIZATION);

}

//**********************************************************************
// void CDerivedLayerReport::validate()
// Validate our report
//**********************************************************************
void CDerivedLayerReport::validate() {
  try {

    sDerivedLayer = pParameterList->getString(PARAM_DERIVED_LAYER);
    bPrintInitialisation = pParameterList->getBool(PARAM_INITIALIZATION,true,false);

    // Validate parent
    CFileReport::validate();

    // Local validation

  } catch (string & ex) {
    ex = "CDerivedLayerReport.validate(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
// void CDerivedLayerReport::build()
// Build our Report
//**********************************************************************
void CDerivedLayerReport::build() {
  try {

    // Get our derived quantity
    CDerivedLayerManager *pManager = CDerivedLayerManager::Instance();
    pDerivedLayer = pManager->getDerivedLayer(sDerivedLayer);

  } catch (string &Ex) {
    Ex = "CDerivedLayerReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedLayerReport::execute()
// Execute
//**********************************************************************
void CDerivedLayerReport::execute() {

  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();


    // Output Header
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_DERIVED_QUANTITY << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sDerivedLayer << "\n";
    if(bPrintInitialisation) {
      // Output initialisation values
      for (int i=0; i < pDerivedLayer->getInitialisationSize(); ++i) {
        for (int j=0; j < pDerivedLayer->getInitialisationValuesSize(i); ++j) {
          vector<vector<double> > vvDerivedLayer = pDerivedLayer->getInitialisationValue(i, j);
          cout << PARAM_INITIALIZATION << "." << PARAM_INITIALIZATION_PHASE << CONFIG_ARRAY_START << boost::lexical_cast<string>(i+1) << CONFIG_ARRAY_END << CONFIG_RATIO_SEPARATOR << " " ;
          cout << PARAM_YEAR << "=" << j+1 << "\n";
          for (int k = 0; k < pDerivedLayer->getHeight(); ++k) {
            for (int l = 0; l < pDerivedLayer->getWidth(); ++l) {
              cout << vvDerivedLayer[k][l] << (l<((int)pDerivedLayer->getWidth()-1) ? CONFIG_SPACE_SEPERATOR : "\n");
            }
          }
        }
      }
    }
    // Output values for each year
    for (int i = pWorld->getInitialYear(); i <= pWorld->getCurrentYear(); ++i) {
      vector<vector<double> > vvDerivedLayer = pDerivedLayer->getValue(i);
      cout << PARAM_YEARS << CONFIG_RATIO_SEPARATOR << " " << PARAM_YEAR << "=" << i << "\n";
      for (int k = 0; k < pDerivedLayer->getHeight(); ++k) {
        for (int l = 0; l < pDerivedLayer->getWidth(); ++l) {
          cout << vvDerivedLayer[k][l] << (l<((int)pDerivedLayer->getWidth()-1) ? CONFIG_SPACE_SEPERATOR : "\n");
        }
      }
    }
    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();

  } catch (string &Ex) {
    Ex = "CDerivedLayerReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDerivedLayerReport::~CDerivedLayerReport()
// Destructor
//**********************************************************************
CDerivedLayerReport::~CDerivedLayerReport() {
}
