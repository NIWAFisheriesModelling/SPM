//============================================================================
// Name        : CNormalPrior.h
// Author      : A.Dunn
// Date        : 12/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALPRIOR_H_
#define CNORMALPRIOR_H_

// Local Headers
#include "../CPrior.h"

//**********************************************************************
//
//
//**********************************************************************
class CNormalPrior : public CPrior {
public:
  // Functions
  CNormalPrior(CNormalPrior *Prior = 0);
  virtual                    ~CNormalPrior();
  void                       setMu(double value) { dMu = value; }
  void                       setCv(double value) { dCv = value; }
  double                     getMu() { return dMu; }
  double                     getCv() { return dCv; }
  CPrior*                    clone() { return (new CNormalPrior(this)); }
  void                       validate();
  double                     getResult(double Param);

protected:
  // Variables
  double                     dMu;
  double                     dCv;
};

#endif /*CNORMALPRIOR_H_*/
