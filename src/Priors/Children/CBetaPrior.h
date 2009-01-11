//============================================================================
// Name        : CBetaPrior.h
// Author      : A.Dunn
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBETAPRIOR_H_
#define CBETAPRIOR_H_

// Local Headers
#include "../CPrior.h"

//**********************************************************************
//
//
//**********************************************************************
class CBetaPrior : public CPrior {
public:
  // Functions
  CBetaPrior(CBetaPrior *Prior = 0);
  virtual                    ~CBetaPrior();
  void                       setMu(double value) { dMu = value; }
  double                     getMu() { return dMu; }
  void                       setSigma(double value) { dSigma = value; }
  double                     getSigma() { return dSigma; }
  void                       setA(double value) { dA = value; }
  double                     getA() { return dA; }
  void                       setB(double value) { dB = value; }
  double                     getB() { return dB; }
  CPrior*                    clone() { return (new CBetaPrior(this)); }
  void                       validate();
  double                     getResult(double Param);

protected:
  // Variables
  double                     dMu;
  double                     dSigma;
  double                     dA;
  double                     dB;

 private:
   // Variables
  double                     dV;
  double                     dT;
  double                     dM;
  double                     dN;

};

#endif /*CBETAPRIOR_H_*/
