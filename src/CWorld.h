//============================================================================
// Name        : CWorld.h
// Author      : S.Rasmussen
// Date        : 10/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : This class represents our world object. The central
//    points of interest for this class are the grids and the runMode
//    calls.
//
//    The world maintains a Grid (pGrid) of WorldSquare objects. This
//    represents the current state of the world as it is now. A second
//    grid called the Drifference Grid (pDifferenceGrid) is an exact copy
//    of pGrid in dimensions, but it maintains only the difference
//    (adjustments) we need to make to the world. After each process is run
//    the difference grid is merged into the world grid to update the current
//    state.
//
//    The runMode calls allow the application entry (int main()) easy access
//    to call functions based on each run mode. The World then sets up what
//    is required to kick-off each type of run.
//
//    Note: CWorld is a singleton because we only want one ever. Multiple
//    worlds are not prohibited.
//
// $Date$
//============================================================================
#ifndef CWORLD_H_
#define CWORLD_H_

// Local Headers
#include "BaseClasses/CBaseBuildableObject.h"

// Classes
class CWorldSquare;
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CWorld : public CBaseBuildableObject {
public:
  static CWorld*            Instance();
  static void               Destroy();

  // Functions
  void                      clone(CWorld *World);
  void                      validate();
  void                      build();
  void                      setWidth(int value) { iWidth = value; }
  int                       getWidth() { return iWidth; }
  void                      setHeight(int value) { iHeight = value; }
  int                       getHeight() { return iHeight; }
  void                      setBaseLayer(string value) { sBaseLayer = value; }
  string                    getBaseLayer() { return sBaseLayer; }
  CWorldSquare*             getBaseSquare(int RowIndex, int ColIndex);
  CWorldSquare*             getDifferenceSquare(int RowIndex, int ColIndex);
  int                       getEnabledSquareCount() { return iEnabledSquareCount; };
  void                      mergeDifferenceGrid();
  void                      zeroGrid();
  virtual                   ~CWorld();

protected:
  // Functions
  CWorld();

  // Variables
  int                       iWidth;
  int                       iHeight;
  CWorldSquare              **pGrid;
  CWorldSquare              **pDifferenceGrid;
  string                    sBaseLayer;
  CNumericLayer             *pBaseLayer;
  int                       iEnabledSquareCount;

private:
  static boost::thread_specific_ptr<CWorld> clInstance;
};

#endif /*CWORLD_H_*/
