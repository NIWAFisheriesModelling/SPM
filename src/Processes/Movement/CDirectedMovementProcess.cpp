//============================================================================
// Name        : CDirectedMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CDirectedMovementProcess.h"
#include "../../PreferenceFunctions/CPreferenceFunctionManager.h"
#include "../../Layers/Numeric/CDoubleLayer.h"
#include "../../PreferenceFunctions/CPreferenceFunction.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CDirectedMovementProcess::CDirectedMovementProcess()
// Default Constructor
//**********************************************************************
CDirectedMovementProcess::CDirectedMovementProcess() {
  // Variables
  dRunningTotal          = 0.0;
}

//**********************************************************************
// void CDirectedMovementProcess::addDirectedProcess(string value)
// Add Directed movment process label to our list
//**********************************************************************
void CDirectedMovementProcess::addDirectedProcess(string value) {
  vDirectedProcessList.push_back(value);
}

//**********************************************************************
// string CDirectedMovementProcess::getDirectedProcess(int index)
// Get the directed process from vector @ index
//**********************************************************************
string CDirectedMovementProcess::getDirectedProcess(int index) {
  return vDirectedProcessList[index];
}

//**********************************************************************
// void CDirectedMovementProcess::validate()
// validate
//**********************************************************************
void CDirectedMovementProcess::validate() {
  try {
    // Base Validation
    // Don't Call MovementProcess::validate
    // This Validates Stuff this Process Doesn't Use
    CProcess::validate();

    // Local Validation
    if (vDirectedProcessList.size() == 0)
      CError::errorMissing(PARAM_DIRECTED_PROCESSES);
    if (getCategoryCount() == 0)
      CError::errorMissing(PARAM_CATEGORIES);
    if (vSelectivityList.size() > 0)
      CError::errorSupported(PARAM_SELECTIVITIES);

  } catch (string Ex) {
    Ex = "CDirectedMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDirectedMovementProcess::build()
// Build
//**********************************************************************
void CDirectedMovementProcess::build() {
  try {
    // Base Build
    CMovementProcess::build();

    // Do We need to build our Process Index?
    if (vDirectedProcessIndex.size() == 0) {
      CPreferenceFunctionManager *pDirectedProcessManager = CPreferenceFunctionManager::Instance();
      // Loop and Add
      foreach(string Label, vDirectedProcessList) {
        vDirectedProcessIndex.push_back(pDirectedProcessManager->getProcess(Label));
      }
    }

    if (pLayer == 0)
      pLayer = new CDoubleLayer();

  } catch (string Ex) {
    Ex = "CDirectedMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDirectedMovementProcess::execute()
// execute
//**********************************************************************
void CDirectedMovementProcess::execute() {
#ifndef OPTIMISE
  try {
#endif
    // Base Execution
    CMovementProcess::execute();

    // Loop World
    for (int i = (iWorldHeight-1); i >= 0; --i) {
      for (int j = (iWorldWidth-1); j >= 0; --j) {
        // Get Current Squares
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        // Reset our Running Total (For Proportions)
        dRunningTotal = 0.0;

        // Re-Loop Through World Generating Our Logit Layer
        for (int k = (iWorldHeight-1); k >= 0; --k) {
          for (int l = (iWorldWidth-1); l >= 0; --l) {
            // Get Target Square
            pTargetBase = pWorld->getBaseSquare(k, l);

            // Make sure we are Ok!
            if (pTargetBase->getEnabled()) {
              dCurrent = 1.0;

              foreach(CPreferenceFunction *Process, vDirectedProcessIndex) {
                dCurrent *= Process->getResult(i, j, k, l);
              }
              // Logit This
              // if (!isZero(dCurrent))
              // dCurrent = 1 / (1-exp(-dCurrent));
            } else
              dCurrent = 0.0;

            // Put This in our Logit-Layer
            // +1 to k/l Because They are Indexes
            // The Function Requires Human Co-Ords
            pLayer->setValue(k+1, l+1, dCurrent);
            dRunningTotal += dCurrent;
          }
        }

        // Loop Through World
        for (int k = (iWorldHeight-1); k >= 0; --k) {
          for (int l = (iWorldWidth-1); l >= 0; --l) {
            // Get Current Squares
            pTargetDiff = pWorld->getDifferenceSquare(k, l);

            // Check if this square is ok
            if (!pTargetDiff->getEnabled())
              continue;

            // Loop Categories and Ages
            foreach(int Category, vCategoryIndex) {
              for (int m = (iBaseColCount-1); m >= 0; --m) {
                // Get Logit Amount
                dCurrent = pLayer->getValue(k, l);
                if (CComparer::isZero(dCurrent))
                  continue;

                // Convert To Proportion
                dCurrent /= dRunningTotal;

                // Get Current Number of Fish
                dCurrent *= pBaseSquare->getValue(Category, m);

                // Move
                pDiff->subValue(Category, m, dCurrent);
                pTargetDiff->addValue(Category, m, dCurrent);
              }
            }
          }
        }
      }
    }
#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CDirectedMovementProcess.execute()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CDirectedMovementProcess::~CDirectedMovementProcess()
// Default De-Constructor
//**********************************************************************
CDirectedMovementProcess::~CDirectedMovementProcess() {
}
