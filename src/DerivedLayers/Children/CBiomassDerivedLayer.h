//============================================================================
// Name        : CSampleDerivedLayer.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
//============================================================================
#ifndef CBIOMASSDERIVEDLAYER_H_
#define CBIOMASSDERIVEDLAYER_H_

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
class CBiomassDerivedLayer : public CDerivedLayer {
public:
  // Methods
  CBiomassDerivedLayer();
  virtual                     ~CBiomassDerivedLayer();
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

#endif /* CBIOMASSDERIVEDLAYER_H_ */
