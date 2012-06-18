//============================================================================
// Name        : CSampleDerivedQuantity.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSAMPLEDERIVEDQUANTITY_H_
#define CSAMPLEDERIVEDQUANTITY_H_

// Headers
#include "../CDerivedQuantity.h"

// Forward Declarations
class CNumericLayer;
class CSelectivity;
class CTimeStepManager;
class CCompleteWorldView;

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceDerivedQuantity : public CDerivedQuantity {
public:
  // Methods
  CAbundanceDerivedQuantity();
  virtual                     ~CAbundanceDerivedQuantity();
  void                        validate();
  void                        build();
  void                        calculate();
  void                        calculate(int initialisationPhase);

protected:
  // Members
  CTimeStepManager            *pTimeStepManager;
  string                      sTimeStep;
  int                         iTimeStep;
  vector<string>              vCategoryNames;
  vector<int>                 vCategories;
  string                      sLayer;
  CNumericLayer               *pLayer;
  vector<string>              vSelectivityNames;
  vector<CSelectivity*>       vSelectivities;
  CCompleteWorldView          *pWorldView;
};

#endif /* CSAMPLEDERIVEDQUANTITY_H_ */
