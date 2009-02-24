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

// Global Headers
#include <vector>

// Local headers
#include "../CSelectivity.h"

// Using
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CAllValuesBoundedSelectivity : public CSelectivity {
public:
  // Functions
  CAllValuesBoundedSelectivity();
  virtual                     ~CAllValuesBoundedSelectivity();
  CSelectivity*               clone() { return new CAllValuesBoundedSelectivity(*this); }
  void                        validate();
  double                      getResult(int Index);

protected:
  // Variables
  double                      dL;
  double                      dH;
  vector<double>              vVs;
};

#endif /* CALLVALUESBOUNDEDSELECTIVITY_H_ */
