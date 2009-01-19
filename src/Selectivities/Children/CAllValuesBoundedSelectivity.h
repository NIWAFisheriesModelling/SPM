//============================================================================
// Name        : CAllValuesBoundedSelectivity.h
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CALLVALUESBOUNDEDSELECTIVITY_H_
#define CALLVALUESBOUNDEDSELECTIVITY_H_

// Local headers
#include "../CSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CAllValuesBoundedSelectivity : public CSelectivity {
public:
  // Functions
  CAllValuesBoundedSelectivity(CAllValuesBoundedSelectivity *Selectivity = 0);
  virtual                     ~CAllValuesBoundedSelectivity();
  CSelectivity*              clone() { return (new CAllValuesBoundedSelectivity(this)); }
  void                       validate();
  void                       build() { }
  double                     getResult(int Index);

protected:
  // Variables
  double                      dL;
  double                      dH;
  vector<double>              vVs;
};

#endif /* CALLVALUESBOUNDEDSELECTIVITY_H_ */
