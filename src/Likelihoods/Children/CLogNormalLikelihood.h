//============================================================================
// Name        : CLogNormalLikelihood.h
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLOGNORMALLIKELIHOOD_H_
#define CLOGNORMALLIKELIHOOD_H_

// Local headers
#include "../CLikelihood.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

//**********************************************************************
//
//
//**********************************************************************
class CLogNormalLikelihood: public CLikelihood {
public:
  // Functions
  CLogNormalLikelihood();
  virtual                     ~CLogNormalLikelihood();
  double                      adjustErrorValue(double processError, double errorValue);
  double                      getResult(double expected, double observed, double errorValue, double processError, double delta);
  double                      simulateObserved(double expected, double errorValue, double processError, double delta);

};

#endif /* CLOGNORMALLIKELIHOOD_H_ */
