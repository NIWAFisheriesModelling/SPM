//============================================================================
// Name        : CDerivedLayerManager.h
// Author      : S.Rasmussen
// Date        : 30/03/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
//============================================================================
#ifndef CDERIVEDLAYERMANAGER_H_
#define CDERIVEDLAYERMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Forward Declaration
class CDerivedLayer;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedLayerManager: public CBaseManager {
public:
  static CDerivedLayerManager* Instance();
  static void                     Destroy();

  // Functions
  void                        addDerivedLayer(CDerivedLayer *DerivedLayer);
  CDerivedLayer*              getDerivedLayer(string label);
  void                        setInitialisationPhase(int newValue) { iInitialisationPhase = newValue; }
  void                        validate();
  void                        build();
  void                        rebuild();
  void                        calculate();
  void                        calculate(int initialisationPhase);
  virtual                     ~CDerivedLayerManager();

protected:
  // Functions
  CDerivedLayerManager();

  // Variables
  vector<CDerivedLayer*>   vDerivedLayers;
  int                      iInitialisationPhase;

private:
  static boost::thread_specific_ptr<CDerivedLayerManager> clInstance;
};

#endif /* CDERIVEDLAYERMANAGER_H_ */
