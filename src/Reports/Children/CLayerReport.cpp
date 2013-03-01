//============================================================================
// Name        : CLayerReport.cpp
// Author      : S.Rasmussen
// Date        : 26/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CLayerReport.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CLayerReport::CLayerReport()
// Default Constructor
//**********************************************************************
CLayerReport::CLayerReport() {
  // Variables
  eExecutionState     = STATE_MODELLING;
  pTimeStepManager    = CTimeStepManager::Instance();
  pLayerManager       = CLayerManager::Instance();

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_TIME_STEP);
  pParameterList->registerAllowed(PARAM_LAYER);

  sLayerType = "";
  sType = "";

}

//**********************************************************************
// void CLayerReport::validate()
// Validate this reporter
//**********************************************************************
void CLayerReport::validate() {
  try {

    // Assign Variables
    pParameterList->fillVector(vYears, PARAM_YEARS, true);
    if (vYears.size() == 0)
      vYears.push_back(pWorld->getInitialYear());

    sTimeStep   = pParameterList->getString(PARAM_TIME_STEP,true,"");
    sLayer      = pParameterList->getString(PARAM_LAYER);

    // Validate parent
    CFileReport::validate();

    // Local validation
    // Validate Year Range
    foreach(int year, vYears) {
      if (year < pWorld->getInitialYear())
        CError::errorLessThan(PARAM_YEAR, PARAM_INITIAL_YEAR);
      else if (year > pWorld->getCurrentYear())
        CError::errorGreaterThan(PARAM_YEAR, PARAM_CURRENT_YEAR);
    }

  } catch (string &Ex) {
    Ex = "CLayerReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerReport::build()
// Build this reporter
//**********************************************************************
void CLayerReport::build() {
  try {
    // Base
    CFileReport::build();

    // Populate TimeStepIndex
    if (sTimeStep != "")
      iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);
    else {
      iTimeStep = 0;
      sTimeStep = pTimeStepManager->getFirstTimeStepLabel();
    }

    sLayerType = pLayerManager->getLayerType(sLayer);
    if (sLayerType == PARAM_ABUNDANCE_DENSITY ||
        sLayerType == PARAM_ABUNDANCE ||
        sLayerType == PARAM_BIOMASS_DENSITY ||
        sLayerType == PARAM_BIOMASS ||
        sLayerType == PARAM_DOUBLE ) {
      pNumericLayer    = pLayerManager->getNumericLayer(sLayer);
      sType = PARAM_DOUBLE;
   } else if (sLayerType == PARAM_STRING) {
      pStringLayer    = pLayerManager->getStringLayer(sLayer);
      sType = PARAM_STRING;
   } else {
      CError::error(string("Invalid ") + PARAM_LAYER + " " + PARAM_TYPE + " (" + sLayerType + ") for report " + string(sLabel));
   }

  } catch (string &Ex) {
    Ex = "CLayerReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerReport::execute()
// Execute reporter
//**********************************************************************
void CLayerReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;
    if (std::find(vYears.begin(), vYears.end(), pTimeStepManager->getCurrentYear()) == vYears.end())
      return;
    if (iTimeStep != pTimeStepManager->getCurrentTimeStep())
      return;

    this->start();

    // Print Out
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pTimeStepManager->getCurrentYear() << "\n";
    cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << sTimeStep << "\n";

    if( sType==PARAM_DOUBLE ) {
      for (int i = 0; i < pNumericLayer->getHeight(); ++i) {
        for (int j = 0; j < pNumericLayer->getWidth(); ++j) {
          cout << pNumericLayer->getValue(i, j) << (j<((int)pNumericLayer->getWidth()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
        }
      }
    } else if( sType==PARAM_STRING ) {
      for (int i = 0; i < pStringLayer->getHeight(); ++i) {
        for (int j = 0; j < pStringLayer->getWidth(); ++j) {
          cout << pStringLayer->getValue(i, j) << (j<((int)pStringLayer->getWidth()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
        }
      }
    }

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();
  } catch (string &Ex) {
    Ex = "CLayerReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// CLayerReport::~CLayerReport()
// Destructor
//**********************************************************************
CLayerReport::~CLayerReport() {
}
