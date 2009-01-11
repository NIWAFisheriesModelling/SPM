//============================================================================
// Name        : CWorldSquareCollection.h
// Author      : S.Rasmussen
// Date        : 11/09/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#ifndef CWORLDSQUARECOLLECTION_H_
#define CWORLDSQUARECOLLECTION_H_

// Local Headers
#include "../../BaseClasses/CBaseBuildableObject.h"

// Classes
class CWorldSquare;
class CStringLayer;

//**********************************************************************
//
//
//**********************************************************************
class CWorldSquareCollection : public CBaseBuildableObject {
public:
  // Functions
  CWorldSquareCollection(CWorldSquareCollection *Collection = 0);
  virtual                     ~CWorldSquareCollection();
  void                        setLayer(CStringLayer *layer) { pLayer = layer; }
  CStringLayer*               getLayer() { return pLayer; }
  int                         getGroupCount() { return (int)mvCollection.size(); }
  double                      getPopulationForAge(string group, int ageIndex);
  double                      getPopulationInCategoryForAge(string group, int ageIndex, int categoryIndex);
  double                      getPopulationForCategory(string group, int categoryIndex);
  void                        validate();
  void                        build();

protected:
  // Variables
  map<string, vector<CWorldSquare*> > mvCollection;
  CStringLayer                *pLayer;
};

#endif /* CWORLDSQUARECOLLECTION_H_ */
