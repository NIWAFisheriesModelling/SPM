//============================================================================
// Name        : CCategoryTransitionRateProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCATEGORYTRANSITIONRATEPROCESS_H_
#define CCATEGORYTRANSITIONRATEPROCESS_H_

// Local headers
#include "../CProcess.h"

// Forward Declaration
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CCategoryTransitionRateProcess : public CProcess {
public:
  CCategoryTransitionRateProcess();
  virtual                     ~CCategoryTransitionRateProcess();
  CProcess*                   clone() { return new CCategoryTransitionRateProcess(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Variables
  vector<string>             vFrom;
  vector<int>                vFromIndex;
  vector<string>             vTo;
  vector<int>                vToIndex;
  vector<double>             vProportions;
  vector<string>             vSelectivityNames;
  vector<CSelectivity*>      vSelectivities;
  string                     sLayer;
  CNumericLayer              *pLayer;

};

#endif /* CCATEGORYTRANSITIONRATEPROCESS_H_ */
