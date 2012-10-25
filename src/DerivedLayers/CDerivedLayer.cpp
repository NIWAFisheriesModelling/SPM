//============================================================================
// Name        : CDerivedLayer.cpp
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "CDerivedLayer.h"


//**********************************************************************
// CDerivedLayer::CDerivedLayer()
// Default Constructor
//**********************************************************************
CDerivedLayer::CDerivedLayer() : iCurrentInitialisationPhase(0) {
}

//**********************************************************************
// CDerivedLayer::~CDerivedLayer()
// Destructor
//**********************************************************************
CDerivedLayer::~CDerivedLayer() {
}

//**********************************************************************
// vector<vector<double> > CDerivedLayer::getValue(int offset)
// Get Value From our Derived Layer
//**********************************************************************
vector<vector<double> > CDerivedLayer::getValue(int offset) {

  int phasesCrossed = 0;

  if (vValues.size() > 0) {
    if (offset >= (int)vValues.size()) {
      offset -= vValues.size();
      phasesCrossed = 1;
    } else {
      return vValues[vValues.size() - (offset+1)];
    }
  }

  /**
   * If we have no values at all, return 0.0
   */
  if (vvInitialisationValues.size() == 0)
    return vBlankData;

  /**
   * Since we don't have any values that are not in the initialisation stage
   * or we've crossed because the offset was too large we need to start working
   * backwards through the initialisation values
   */
  vector<vector<Data> >::reverse_iterator vvIter;
  for (vvIter = vvInitialisationValues.rbegin(); vvIter != vvInitialisationValues.rend(); ++vvIter) {

    if (offset >= (int)vvIter->size()) {
      /**
       * If we have already crossed a phase then we want to return the first element
       * of the new phase, we cannot ever cross more than 1 phase
       */
      if (phasesCrossed == 1) {
        return (*vvIter->begin());
      } else {
        offset -= vvIter->size();
        phasesCrossed = 1;
      }

    } else {
      return vvIter->at(vvIter->size() - (offset+1));
    }
  }

  /**
   * Return the first value
   */

  return *vvInitialisationValues.begin()->begin();
}

//**********************************************************************
// void CDerivedLayer::rebuild()
// Rebuild our derived layer
//**********************************************************************
void CDerivedLayer::build() {

  // We have to build the blank data object to return when we haven't yet
  // built some data during the initialisation phases
  int worldHeight = pWorld->getHeight();
  int worldWidth  = pWorld->getWidth();

  vBlankData.resize(worldHeight);
  for (int i = 0; i < worldHeight; ++i)
    vBlankData[i].assign(worldWidth, 0.0);
}

//**********************************************************************
// void CDerivedLayer::rebuild()
// Rebuild our derived layer
//**********************************************************************
void CDerivedLayer::rebuild() {
   iCurrentInitialisationPhase = 0;
   vvInitialisationValues.clear();
   vValues.clear();
 }




















