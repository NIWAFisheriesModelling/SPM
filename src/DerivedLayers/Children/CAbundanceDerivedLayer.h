//============================================================================
// Name        : CAbundanceDerivedLayer.h
// Author      : S.Rasmussen
// Date        : 23/10/2012
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
//============================================================================
#ifndef CABUNDANCEDERIVEDLAYER_H_
#define CABUNDANCEDERIVEDLAYER_H_

// Headers
#include "../CDerivedLayer.h"

// Forward Declarations
class CNumericLayer;
class CSelectivity;
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceDerivedLayer : public CDerivedLayer {
public:
  // Methods
  CAbundanceDerivedLayer();
  virtual                     ~CAbundanceDerivedLayer();
  void                        validate();
  void                        build();
  void                        calculate();
  void                        calculate(int initialisationPhase);

protected:
  // Members
  CTimeStepManager            *pTimeStepManager;
  string                      sTimeStep;
  vector<string>              vInitializationTimeStepNames;
  int                         iTimeStep;
  vector<int>                 vInitializationTimeStepIndex;
  vector<string>              vCategoryNames;
  vector<int>                 vCategories;
  vector<string>              vSelectivityNames;
  vector<CSelectivity*>       vSelectivities;
};

#endif /* CABUNDANCEDERIVEDLAYER_H_ */
