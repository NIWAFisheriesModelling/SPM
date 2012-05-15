//============================================================================
// Name        : CLayerDerivedWorldViewReport.cpp
// Author      : S.Rasmussen
// Date        : 9/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

//Headers
#include <boost/lexical_cast.hpp>

// Local headers
#include "CLayerDerivedWorldViewReport.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../World/WorldView/CLayerDerivedWorldView.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CLayerDerivedWorldViewReport::CLayerDerivedWorldViewReport()
// Constructor
//**********************************************************************
CLayerDerivedWorldViewReport::CLayerDerivedWorldViewReport() {

  // Variables
  eExecutionState     = STATE_MODELLING;
  pTimeStepManager    = CTimeStepManager::Instance();
  pLayerManager       = CLayerManager::Instance();
  pWorldView          = 0;

  // Register Allowed Parameters
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_TIME_STEP);
}

//**********************************************************************
//
//
//**********************************************************************
void CLayerDerivedWorldViewReport::validate() {
  try {
    // Base
    CFileReport::validate();

    // Assign Variables
    pParameterList->fillVector(vYear, PARAM_YEARS);
    //iYear       = pParameterList->getInt(PARAM_YEAR,true,pWorld->getInitialYear());
    sTimeStep   = pParameterList->getString(PARAM_TIME_STEP,true,"");
    sLayer      = pParameterList->getString(PARAM_LAYER);

    // Validate Year Range
    for (int i = 0; i < (int)vYear.size(); ++i) {
      if (boost::lexical_cast<double>(vYear[i]) < pWorld->getInitialYear())
        CError::errorLessThan(PARAM_YEARS, PARAM_INITIAL_YEAR);
      else if (boost::lexical_cast<double>(vYear[i]) > pWorld->getCurrentYear())
        CError::errorGreaterThan(PARAM_YEARS, PARAM_CURRENT_YEAR);
    }

  } catch (string &Ex) {
    Ex = "CLayerDerivedWorldViewReport.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerDerivedWorldViewReport::build()
// Build our Report
//**********************************************************************
void CLayerDerivedWorldViewReport::build() {
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

    // Get our Layer
    pLayer = pLayerManager->getStringLayer(sLayer);

    // Build our view
    pWorldView = new CLayerDerivedWorldView(pLayer);
    pWorldView->validate();
    pWorldView->build();

    // Build our Areas
    mAreas.clear();

    for (int i = 0; i < pLayer->getHeight(); ++i)
      for (int j = 0; j < pLayer->getWidth(); ++j)
        mAreas[pLayer->getValue(i,j)]++;

  } catch (string &Ex) {
    Ex = "CLayerDerivedWorldViewReport.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerDerivedWorldViewReport::execute()
// Execute our Layer Derived World View
//**********************************************************************
void CLayerDerivedWorldViewReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    // Start IO
    this->start();

    for (int i = 0; i < (int)vYear.size(); ++i) {
      iYear = boost::lexical_cast<double>(vYear[i]);
      if (iYear == pTimeStepManager->getCurrentYear()) {
        if (iTimeStep == pTimeStepManager->getCurrentTimeStep()) {

          pWorldView->execute();

          // Start Output
          cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
          cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
          cout << PARAM_PARTITION << "." << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << boost::lexical_cast<string>(iYear) << "\n";
          cout << PARAM_PARTITION << "." << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << sTimeStep << "\n";

          cout << PARAM_AREA << CONFIG_SEPERATOR_ESTIMATE_VALUES;
          cout << PARAM_CATEGORY;
          for(int i = pWorld->getMinAge(); i < pWorld->getMaxAge()+1; i++) {
            cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << PARAM_AGE;
            cout << CONFIG_ARRAY_START << i << CONFIG_ARRAY_END;
          }
          cout << "\n";

          map<string, int>::iterator mPtr = mAreas.begin();
          while (mPtr != mAreas.end()) {
            pBaseSquare = pWorldView->getSquare((*mPtr).first);

            int iSquareHeight = pBaseSquare->getHeight();
            int iSquareWidth  = pBaseSquare->getWidth();

            // Loop Through
            for (int i = 0; i < iSquareHeight; ++i) {
              cout << (*mPtr).first << CONFIG_SEPERATOR_ESTIMATE_VALUES << pWorld->getCategoryNameForIndex(i);
              for (int j = 0; j < iSquareWidth; ++j) {
                cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << pBaseSquare->getValue(i, j);
              }
              cout << "\n";
            }

            mPtr++;
          }
          cout << CONFIG_END_REPORT << "\n" << endl;
        }
      }
    }
    // End IO
    this->end();

  } catch (string &Ex) {
    Ex = "CLayerDerivedViewReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CLayerDerivedWorldViewReport::~CLayerDerivedWorldViewReport()
// Destructor
//**********************************************************************
CLayerDerivedWorldViewReport::~CLayerDerivedWorldViewReport() {
  // Clean Memory
//  if (pWorldView != 0)
//    delete pWorldView;
}
