//============================================================================
// Name        : CLogNormalPrior.h
// Author      : A.Dunn
// Date        : 13/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLOGNORMALPRIOR_H_
#define CLOGNORMALPRIOR_H_

// Local Headers
#include "../CPrior.h"

//**********************************************************************
//
//
//**********************************************************************
class CLogNormalPrior : public CPrior {
public:
  // Functions
  CLogNormalPrior(CLogNormalPrior *Prior = 0);
  virtual                     ~CLogNormalPrior();
  void                        setMu(double value) { dMu = value; }
  double                      getMu() { return dMu; }
  void                        setCv(double value) { dCv = value; }
  double                      getCv() { return dCv; }
  CPrior*                     clone() { return (new CLogNormalPrior(this)); }
  void                        validate();
  double                      getResult(double Param);

protected:
  // Variables
  double                      dMu;
  double                      dCv;

private:
  // Variables
  double                      dSigma;

};

#endif /*CLOGNORMALPRIOR_H_*/
