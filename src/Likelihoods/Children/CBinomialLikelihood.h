//============================================================================
// Name        : CBinomialLikelihood.h
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBINOMIALLIKELIHOOD_H_
#define CBINOMIALLIKELIHOOD_H_

// Local headers
#include "../CLikelihood.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

//**********************************************************************
//
//
//**********************************************************************
class CBinomialLikelihood: public CLikelihood {
public:
  CBinomialLikelihood();
  virtual                     ~CBinomialLikelihood();
  double                      adjustErrorValue(double processError, double errorValue);
  void                        getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
                                vector<double> &errorValue, vector<double> &processError, double delta);
  void                        simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
                                vector<double> &processError, double delta);
};

#endif /* CBINOMIALLIKELIHOOD_H_ */
