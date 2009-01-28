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
  CBetaPrior();
  virtual                    ~CBetaPrior();
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
