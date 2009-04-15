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
  virtual                 ~CPseudoLikelihood();
  double                  getResult(double expected, double observed, double errorValue, double processError, double delta) { return 0; }
};

#endif /* CPSEUDOLIKELIHOOD_H_ */
