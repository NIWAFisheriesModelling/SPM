//============================================================================
// Name        : CCachedSelectivity.h
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCACHEDSELECTIVITY_H_
#define CCACHEDSELECTIVITY_H_

// Local headers
#include "../../CSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CCachedSelectivity : public CSelectivity {
public:
  CCachedSelectivity(CCachedSelectivity *Selectivity = 0);
  virtual                     ~CCachedSelectivity();
  void                        build();
  void                        rebuild();
  double                      getResult(int index);

protected:
  // Functions
  virtual double              calculateResult(int Age) = 0;

  // variables
  vector<double>              vResults;
};

#endif /* CCACHEDSELECTIVITY_H_ */
