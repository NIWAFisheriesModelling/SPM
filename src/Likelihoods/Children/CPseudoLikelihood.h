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
  double                      adjustErrorValue(const double processError, const double errorValue) { return 0; }
  void                        getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
                                const vector<double> &errorValue, const vector<double> &processError, const double delta) { }
  void                        simulateObserved(const vector<string> &keys, vector<double> &observed, const vector<double> &expected,
                                const vector<double> &errorValue, const vector<double> &processError, const double delta) { };
};

#endif /* CPSEUDOLIKELIHOOD_H_ */
