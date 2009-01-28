//============================================================================
// Name        : CDoubleExponentialSelectivity.h
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDOUBLEEXPONENTIALSELECTIVITY_H_
#define CDOUBLEEXPONENTIALSELECTIVITY_H_

// Local headers
#include "../CSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CDoubleExponentialSelectivity: public CSelectivity {
public:
  // Functions
  CDoubleExponentialSelectivity();
  virtual                     ~CDoubleExponentialSelectivity();
  void                        validate();
  double                      getResult(int Index);

protected:
  // Variables
  double                      dX0;
  double                      dX1;
  double                      dX2;
  double                      dY0;
  double                      dY1;
  double                      dY2;
};

#endif /* CDOUBLEEXPONENTIALSELECTIVITY_H_ */
