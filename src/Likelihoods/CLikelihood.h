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

//**********************************************************************
//
//
//**********************************************************************
class CLikelihood {
public:
  CLikelihood();
  virtual                     ~CLikelihood();
  virtual double              getResult(double expected, double observed, double errorValue, double processError, double delta) = 0;
};

#endif /* CLIKELIHOOD_H_ */
