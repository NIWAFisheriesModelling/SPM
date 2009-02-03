//============================================================================
// Name        : CUniformLogPrior.h
// Author      : A.Dunn
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CUNIFORMLOGPRIOR_H_
#define CUNIFORMLOGPRIOR_H_

// Local Headers
#include "../CPrior.h"

//**********************************************************************
//
//
//**********************************************************************
class CUniformLogPrior : public CPrior {
public:
  // Functions
  CUniformLogPrior();
  virtual                    ~CUniformLogPrior();
  CPrior*                    clone() { return new CUniformLogPrior(*this); }
  void                       validate();
  double                     getResult(double Param);

protected:
  // Variables
  double                     dC;
};

#endif /*CUNIFORMLOGPRIOR_H_*/
