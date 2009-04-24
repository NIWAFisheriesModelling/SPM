//============================================================================
// Name        : CLikelihood.h
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLIKELIHOOD_H_
#define CLIKELIHOOD_H_

// Local headers
#include "../BaseClasses/CBaseObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CLikelihood : public CBaseObject {
public:
  CLikelihood();
  virtual                     ~CLikelihood();
  virtual double              adjustErrorValue(double processError, double errorValue) = 0;
  virtual double              getResult(double expected, double observed, double errorValue, double processError, double delta) = 0;
  virtual double              simulateObserved(double expected, double errorValue, double processError, double delta) = 0;
};

#endif /* CLIKELIHOOD_H_ */
