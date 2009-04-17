//============================================================================
// Name        : CDerivedQuantity.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDERIVEDQUANTITY_H_
#define CDERIVEDQUANTITY_H_

// Local headers
#include "../BaseClasses/CBaseExecute.h"

// Forward Declarations
class CNumericLayer;
class CSelectivity;
class CTimeStepManager;
class CCompleteWorldView;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantity : public CBaseExecute {
public:
  // Functions
  CDerivedQuantity();
  virtual                     ~CDerivedQuantity();
  CDerivedQuantity*           clone() { return new CDerivedQuantity(*this); }
  double                      getValue(int offset = 0);
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Variables
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
  vector<double>              vValues;

};

#endif /* CDERIVEDQUANTITY_H_ */
