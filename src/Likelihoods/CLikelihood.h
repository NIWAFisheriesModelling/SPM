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
class CLikelihood: public CBaseObject {
public:
  CLikelihood();
  virtual ~CLikelihood();
  virtual double              adjustErrorValue(double processError, double errorValue) = 0;
  virtual void                getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
                                vector<double> &errorValue, vector<double> &processError, double delta) = 0;
  virtual void                simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
                                vector<double> &processError, double delta) = 0;
  virtual double              getInitialScore(vector<string> &keys, vector<double> &processError, vector<double> &errorValue) { return 0; }
};

#endif /* CLIKELIHOOD_H_ */
