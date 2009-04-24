//============================================================================
// Name        : CPseudoLikelihood.h
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPSEUDOLIKELIHOOD_H_
#define CPSEUDOLIKELIHOOD_H_

// Local headers
#include "../CLikelihood.h"

//**********************************************************************
//
//
//**********************************************************************
class CPseudoLikelihood: public CLikelihood {
public:
  CPseudoLikelihood();
  virtual                     ~CPseudoLikelihood();
  double                      adjustErrorValue(double processError, double errorValue) { return 0; }
  double                      getResult(double expected, double observed, double errorValue, double processError, double delta) { return 0.0; }
  double                      simulateObserved(double expected, double errorValue, double processError, double delta) { return 0.0; }
};

#endif /* CPSEUDOLIKELIHOOD_H_ */
