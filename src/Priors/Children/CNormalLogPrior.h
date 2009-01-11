//============================================================================
// Name        : CNormalLogPrior.h
// Author      : A.Dunn
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALLOGPRIOR_H_
#define CNORMALLOGPRIOR_H_

// Local Headers
#include "../CPrior.h"

//**********************************************************************
//
//
//**********************************************************************
class CNormalLogPrior : public CPrior {
public:
  // Functions
  CNormalLogPrior(CNormalLogPrior *Prior = 0);
  virtual                    ~CNormalLogPrior();
  void                       setMu(double value) { dMu = value; }
  void                       setSigma(double value) { dSigma = value; }
  double                     getMu() { return dMu; }
  double                     getSigma() { return dSigma; }
  CPrior*                    clone() { return (new CNormalLogPrior(this)); }
  void                       validate();
  double                     getResult(double Param);

protected:
  // Variables
  double                     dMu;
  double                     dSigma;

 private:
   // Variables

};

#endif /*CNORMALLOGPRIOR_H_*/
