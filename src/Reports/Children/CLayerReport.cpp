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
    pLayer    = pLayerManager->getNumericLayer(sLayer);

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

    for (int i = 0; i < pLayer->getHeight(); ++i) {
      for (int j = 0; j < pLayer->getWidth(); ++j) {
        cout << pLayer->getValue(i, j) << " ";
      }
      cout << "\n";
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
