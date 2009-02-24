//============================================================================
// Name        : CIncreasingSelectivity.h
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINCREASINGSELECTIVITY_H_
#define CINCREASINGSELECTIVITY_H_

// Global headers
#include <vector>

// Local headers
#include "../CSelectivity.h"

// Using
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CIncreasingSelectivity: public CSelectivity {
public:
  // Functions
  CIncreasingSelectivity();
  virtual                     ~CIncreasingSelectivity();
  CSelectivity*               clone() { return new CIncreasingSelectivity(*this); }
  void                        validate();
  double                      getResult(int Index);

protected:
  double                      dL;
  double                      dH;
  vector<double>              vVs;
};

#endif /* CINCREASINGSELECTIVITY_H_ */
