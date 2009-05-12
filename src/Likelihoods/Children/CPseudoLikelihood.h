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
  void                        getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
                                vector<double> &errorValue, vector<double> &processError, double delta) { }
  void                        simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
                                vector<double> &processError, double delta) { }
};

#endif /* CPSEUDOLIKELIHOOD_H_ */
