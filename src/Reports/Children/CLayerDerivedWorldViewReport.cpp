//============================================================================
// Name        : CLayerDerivedWorldViewReport.cpp
// Author      : S.Rasmussen
// Date        : 9/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CLayerDerivedWorldViewReport.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../World/WorldView/CLayerDerivedWorldView.h"

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
  pParameterList->registerAllowed(PARAM_YEAR);
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
    iYear       = pParameterList->getInt(PARAM_YEAR);
    sTimeStep   = pParameterList->getString(PARAM_TIME_STEP);
    sLayer      = pParameterList->getString(PARAM_LAYER);

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

  // Check for correct state
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    return;
  if (iYear != pTimeStepManager->getCurrentYear())
    return;
  if (iTimeStep != pTimeStepManager->getCurrentTimeStep())
    return;


  pWorldView->execute();

  // Start IO
  this->start();

  // Start Output
  cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
  cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
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

  // End IO
  this->end();
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
