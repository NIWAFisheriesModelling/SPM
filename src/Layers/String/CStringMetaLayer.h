//============================================================================
// Name        : CStringMetaLayer.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSTRINGMETALAYER_H_
#define CSTRINGMETALAYER_H_

// Global Headers
#include <vector>

// Local headers
#include "CStringLayer.h"
#include "../CLayer.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"

// Classes
class CTimeStepManager;

// Using
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CStringMetaLayer : public CStringLayer {
public:
  // Functions
  CStringMetaLayer();
  virtual                     ~CStringMetaLayer();
  CLayer*                     clone() { return new CStringMetaLayer(*this); }
  void                        validate();
  void                        build();
  string                      getValue(int RowIndex, int ColIndex);

protected:
  // Variables
  string                       sDefaultLayer;
  vector<int>                  vYears;
  vector<string>               vLayerNames;
  vector<string>               vInitialisationPhases;
  vector<string>               vInitialisationLayers;
  vector<CStringLayer*>        vPhaseLayers;
  vector<int>                  vYearsIndex;
  vector<CStringLayer*>        vYearsLayers;
  bool                         bHasYears;
  bool                         bHasInitialisation;
  CInitializationPhaseManager  *pInitializationPhaseManager;
  CTimeStepManager             *pTimeStepManager;

};

#endif /* CMETALAYER_H_ */
