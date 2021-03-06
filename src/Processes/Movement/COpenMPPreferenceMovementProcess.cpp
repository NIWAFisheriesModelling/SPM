//============================================================================
// Name        : CPreferenceMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>
#include <omp.h>

// Local headers
#include "COpenMPPreferenceMovementProcess.h"
#include "../../PreferenceFunctions/CPreferenceFunctionManager.h"
#include "../../Layers/Numeric/CDoubleLayer.h"
#include "../../PreferenceFunctions/CPreferenceFunction.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CComparer.h"

// Using
using std::cout;
using std::cerr;
using std::endl;

//**********************************************************************
// CPreferenceMovementProcess::CPreferenceMovementProcess()
// Default constructor
//**********************************************************************
COpenMPPreferenceMovementProcess::COpenMPPreferenceMovementProcess() {
  // Default Values
  pLayer = 0;
  sType = PARAM_PREFERENCE_MOVEMENT;
  bIsStatic = false;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTION);
  pParameterList->registerAllowed(PARAM_PREFERENCE_FUNCTIONS);
}

//**********************************************************************
// void CPreferenceMovementProcess::validate()
// Validate the process
//**********************************************************************
void COpenMPPreferenceMovementProcess::validate() {
  try {
    // Base
    CProcess::validate();

    // Get our Variables
    dProportion = pParameterList->getDouble(PARAM_PROPORTION,true,1.0);

    pParameterList->fillVector(vDirectedProcessList, PARAM_PREFERENCE_FUNCTIONS);
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);

    //register estimables
    registerEstimable(PARAM_PROPORTION, &dProportion);

    if (getProportion() < 0.0)
      CError::errorLessThan(PARAM_PROPORTION, PARAM_ZERO);
    if (getProportion() > 1.0)
      CError::errorGreaterThan(PARAM_PROPORTION, PARAM_ONE);

  } catch (string &Ex) {
    Ex = "CPreferenceMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceMovementProcess::build()
// Build the process
//**********************************************************************
void COpenMPPreferenceMovementProcess::build() {
  try {
    // Base Build
    CMovementProcess::build();

    // Do We need to build our Process Index?
    if (vDirectedProcessIndex.size() == 0) {
      CPreferenceFunctionManager *pDirectedProcessManager = CPreferenceFunctionManager::Instance();
      // Loop and Add
      foreach(string Label, vDirectedProcessList) {
        vDirectedProcessIndex.push_back(pDirectedProcessManager->getPreferenceFunction(Label));
      }
    }

    if (pLayer == 0) {
      pLayer = new CDoubleLayer();

      for (int i = 0; i < pWorld->getHeight(); ++i)
        for (int j = 0; j < pWorld->getWidth(); ++j)
          pLayer->addParameter(PARAM_DATA, "0");

      pLayer->addParameter(PARAM_LABEL, "_");
      pLayer->validate();
      pLayer->build();
    }

    bIsStatic = true;
    if (pLayer != 0)
      bIsStatic = bIsStatic && pLayer->getIsStatic();

    foreach(CPreferenceFunction* preferenceFunction, vDirectedProcessIndex) {
      bIsStatic = bIsStatic && preferenceFunction->getIsStatic();
    }

    if (bIsStatic) {
      vPreferenceCache.resize(iWorldHeight);
      vRunningTotalCache.resize(iWorldHeight);
      for (int i = 0; i < iWorldHeight; ++i) {

        vRunningTotalCache[i].resize(iWorldWidth, 0.0);
        vPreferenceCache[i].resize(iWorldWidth);
        for (int j = 0; j < iWorldWidth; ++j) {

          vPreferenceCache[i][j].resize(iWorldHeight);
          for (int k = 0; k < iWorldHeight; ++k)
            vPreferenceCache[i][j][k].resize(iWorldWidth, 0.0);
        }
      }

      rebuild();
    }

  } catch (string &Ex) {
    Ex = "CPreferenceMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// void CPreferenceMovementProcess::execute()
// Execute the process
//**********************************************************************
void COpenMPPreferenceMovementProcess::rebuild() {
  if (bIsStatic) {
    for (int i = (iWorldHeight-1); i >= 0; --i) {
      for (int j = (iWorldWidth-1); j >= 0; --j) {
        if (!pWorld->getBaseSquare(i, j)->getEnabled())
          continue;

        dRunningTotal = 0.0;
        for (int k = (iWorldHeight-1); k >= 0; --k) {
          for (int l = (iWorldWidth-1); l >= 0; --l) {
            if (!pWorld->getBaseSquare(k, l)->getEnabled()) {
              dCurrent = 0.0;
            } else {
              dCurrent = 1.0;

              foreach(CPreferenceFunction* preferenceFunction, vDirectedProcessIndex) {
                dCurrent *= preferenceFunction->getResult(i, j, k, l);
              }
            }

            vPreferenceCache[i][j][k][l] = dCurrent;
            dRunningTotal += dCurrent;
          }
        }

        vRunningTotalCache[i][j] = dRunningTotal;
      }
    }
  }
}

//**********************************************************************
// void CPreferenceMovementProcess::execute()
// Execute the process
//**********************************************************************
void COpenMPPreferenceMovementProcess::execute() {
  try {
    // Base Execution
    CMovementProcess::execute();

    // Loop World
    int procs = (omp_get_num_procs() * 2) - 1; // Default to number of cores less one
    int iMaxProcs = pConfig->getNumberOfThreads();
    if ( iMaxProcs > 0 && iMaxProcs < procs ) procs = iMaxProcs;
    if ( procs < 1) procs = 1;

    omp_set_dynamic(0);
    omp_set_num_threads(procs);

    #pragma omp parallel for
    for (int i = (iWorldHeight-1); i >= 0; --i) {
      for (int j = (iWorldWidth-1); j >= 0; --j) {
        CDoubleLayer pLayer = CDoubleLayer();

        // Get Current Squares
        CWorldSquare* pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        CWorldSquare* pDiff       = pWorld->getDifferenceSquare(i, j);

        // Only rebuild the cache if we have too
        // Reset our Running Total (For Proportions)
        double dRunningTotal = 0.0;

        if (!bIsStatic) {
          // Re-Loop Through World Generating Our Logit Layer
          for (int k = (iWorldHeight-1); k >= 0; --k) {
            for (int l = (iWorldWidth-1); l >= 0; --l) {
              double dCurrent = 0.0;
              // Get Target Square
              CWorldSquare* pTargetBase = pWorld->getBaseSquare(k, l);

              // Make sure the target cell is enabled
              if (pTargetBase->getEnabled()) {
                dCurrent = 1.0;
                foreach(CPreferenceFunction *Process, vDirectedProcessIndex) {
                  dCurrent *= Process->getResult(i, j, k, l);
                }
              } else {
                dCurrent = 0.0;
              }

              pLayer.setValue(k+1, l+1, dCurrent);
              dRunningTotal += dCurrent;
            }
          }
        }

        // Loop Through World
        for (int k = (iWorldHeight-1); k >= 0; --k) {
          for (int l = (iWorldWidth-1); l >= 0; --l) {
            // Get Current Squares
            CWorldSquare* pTargetDiff = pWorld->getDifferenceSquare(k, l);

            // Make sure the target cell is enabled
            if (!pTargetDiff->getEnabled())
              continue;

            // Loop Categories and Ages
            foreach(int Category, vCategoryIndex) {
              for (int m = (iBaseColCount-1); m >= 0; --m) {
                double dCurrent = 0.0;
                // Get Amount
                if (bIsStatic)
                  dCurrent = vPreferenceCache[i][j][k][l];
                else
                  dCurrent = pLayer.getValue(k, l, 0, 0);

                // if the amount is low, then don't bother moving
                if (dCurrent <= TRUE_ZERO)
                  continue;

                // Convert To Proportion
                if (bIsStatic) {
                  dCurrent /= vRunningTotalCache[i][j];
                } else {
                  dCurrent /= dRunningTotal;
                }

                // Get Current Number of Fish, multipled by proportion to move
                dCurrent *= dProportion * pBaseSquare->getValue(Category, m);

                // Move
                pDiff->subValue(Category, m, dCurrent);
                pTargetDiff->addValue(Category, m, dCurrent);
              }
            }
          }
        }
//        delete pLayer;
      }
    }

  } catch (string &Ex) {
    Ex = "CPreferenceMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPreferenceMovementProcess::~CPreferenceMovementProcess()
// Destructor
//**********************************************************************
COpenMPPreferenceMovementProcess::~COpenMPPreferenceMovementProcess() {
}
