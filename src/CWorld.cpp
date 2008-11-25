//============================================================================
// Name        : CWorld.cpp
// Author      : S.Rasmussen
// Date        : 3/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CWorld.h >>
// $Date$
//============================================================================

// Local Headers
#include "CWorld.h"
#include "CLayerManager.h"
#include "Layers/CNumericLayer.h"
#include "WorldSquares/CWorldSquare.h"

// Singleton Var
boost::thread_specific_ptr<CWorld> CWorld::clInstance;

//**********************************************************************
// CWorld::CWorld()
// Default Constructor
//**********************************************************************
CWorld::CWorld() {
  // Set Default Variable Values
  pGrid                       = 0;
  pDifferenceGrid             = 0;
  iWidth                      = 0;
  iHeight                     = 0;
  sBaseLayer                  = "";
  pBaseLayer                  = 0;
  iEnabledSquareCount         = 0;
}

//**********************************************************************
// CWorld* CWorld::Instance()
// Instance Method - Singleton
//**********************************************************************
CWorld* CWorld::Instance() {
  if (clInstance.get() == 0) {
    clInstance.reset(new CWorld());
  }
  return clInstance.get();
}

//**********************************************************************
// void CWorld::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CWorld::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CWorld::clone(CWorld *World)
// Clone our World
//**********************************************************************
void CWorld::clone(CWorld *World) {
  try {
    iWidth                      = World->getWidth();
    iHeight                     = World->getHeight();
    sBaseLayer                  = World->getBaseLayer();

  } catch (string Ex) {
    Ex = "CWorld.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CWorld::validateWorld()
// Validate The World
//**********************************************************************
void CWorld::validate() {
  try {
    // Validate The required parameters
    if (getHeight() <= 0)
      errorMissing(PARAM_NROWS);
    if (getWidth() <= 0)
      errorMissing(PARAM_NCOLS);
    if (getBaseLayer() == "")
      errorMissing(PARAM_LAYER_NAME);
    if (getHeight() > 1000)
      errorGreaterThan(PARAM_NROWS, PARAM_ONE_THOUSAND);
    if (getWidth() > 1000)
      errorGreaterThan(PARAM_NCOLS, PARAM_ONE_THOUSAND);

  } catch(string Ex) {
    Ex = "CWorld.validateWorld->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CWorld::buildWorld()
// Build our World
//**********************************************************************
void CWorld::build() {
  try {
    if (pGrid == 0) {
      // Allocate Space for our X (Height)
      pGrid = new CWorldSquare*[iHeight];
      for (int i = 0; i < iHeight; ++i) {
        pGrid[i] = new CWorldSquare[iWidth];
      }

      // Allocate Our Difference Grid
      pDifferenceGrid = new CWorldSquare*[iHeight];
      for (int i = 0; i < iHeight; ++i) {
        pDifferenceGrid[i] = new CWorldSquare[iWidth];
      }

      // Set Variables (Can't do it above. Stupid blah ISO C++)
      for (int i = 0; i < iHeight; ++i) {
        for (int j = 0; j < iWidth; ++j) {
          pGrid[i][j].build();
          pDifferenceGrid[i][j].build();
        }
      }
    }

    if (pBaseLayer == 0) {
      // Get Our Base Layer
      CLayerManager *pLayerManager = CLayerManager::Instance();
      pBaseLayer = pLayerManager->getNumericLayer(getBaseLayer());
      if (pBaseLayer->getType() != PARAM_DOUBLE)
        errorNotEqual(PARAM_LAYER_TYPE, PARAM_DOUBLE);

      // Set Enabled Square Count
      iEnabledSquareCount = iHeight * iWidth;

      // Flag any as Disabled if they don't match our Base_Layer
      for (int i = 0; i < iHeight; ++i) {
        for (int j = 0; j < iWidth; ++j) {
          if (pBaseLayer->getValue(i, j) == 0) {
            pGrid[i][j].setEnabled(false);
            iEnabledSquareCount--;
          } else if (pBaseLayer->getValue(i,j) < 0) {
            throw string(ERROR_NEGATIVE_BASE_LAYER);
          } else
            pGrid[i][j].setArea(pBaseLayer->getValue(i,j));
        }
      }

      if (iEnabledSquareCount <= 0)
        throw string(ERROR_VALID_SQUARES_WITH_LAYER);
    }

  } catch(string Ex) {
    Ex = "CWorld.buildWorld()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CWorldSquare* CWorld::getBaseSquare(int RowIndex, int ColIndex)
// Get a square from our Base Grid
//**********************************************************************
CWorldSquare* CWorld::getBaseSquare(int RowIndex, int ColIndex) {
#ifndef OPTIMISE
  try {
    if (RowIndex >= iHeight)
      errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_HEIGHT);
    if (ColIndex >= iWidth)
      errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_WIDTH);
#endif
    CWorldSquare *pPtr = dynamic_cast<CWorldSquare*>(&pGrid[RowIndex][ColIndex]);
    if (pPtr == 0)
      throw string(ERROR_BAD_CAST_WOLD_SQUARE);

    return pPtr;
#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CWorld.getBaseSquare()->" + Ex;
    throw Ex;
  }

  return 0;
#endif
}
//**********************************************************************
// CWorldSquare* CWorld::getDifferenceSquare(int RowIndex, int ColIndex)
// Get a square from our Difference Grid
//**********************************************************************
CWorldSquare* CWorld::getDifferenceSquare(int RowIndex, int ColIndex) {
#ifndef OPTIMISE
  try {
    if (RowIndex >= iHeight)
      errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_HEIGHT);
    if (ColIndex >= iWidth)
      errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_WIDTH);
#endif

    return &pDifferenceGrid[RowIndex][ColIndex];

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CWorld.getDifferenceSquare()->" + Ex;
    throw Ex;
  }

  return 0;
#endif
}

//**********************************************************************
// void CWorld::mergeDifferenceGrid()
// Merge Difference Grid onto our Main Grid
//**********************************************************************
void CWorld::mergeDifferenceGrid() {
#ifndef OPTIMISE
  try {
#endif
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j) {
        pGrid[i][j].makeAdjustments(&pDifferenceGrid[i][j]);
        pDifferenceGrid[i][j].zeroGrid();
      }
#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CWorld.mergeDifferenceGrid->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CWorld::zeroGrid()
// Reset the WorldGrid To 0
//**********************************************************************
void CWorld::zeroGrid() {
#ifndef OPTIMISE
  try {
#endif

    // Zero our Grid
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j)
        pGrid[i][j].zeroGrid();

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CWorld.zeroGrid()->" + Ex;
    throw Ex;
  }
#endif
}
//**********************************************************************
// CWorld::~CWorld()
// Default De-Constructor
//**********************************************************************
CWorld::~CWorld() {
  // Clean Our DifferenceGrid
  if (pDifferenceGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete [] pDifferenceGrid[i];
      pDifferenceGrid[i] = 0;
    }
    delete [] pDifferenceGrid;
  }

  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete [] pGrid[i];
      pGrid[i] = 0;
    }
    delete [] pGrid;
  }
}
