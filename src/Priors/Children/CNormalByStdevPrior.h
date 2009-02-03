//============================================================================
// Name        : CNormalByStdevPrior.h
// Author      : A.Dunn
// Date        : 12/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALBYSTDEVPRIOR_H_
#define CNORMALBYSTDEVPRIOR_H_

// Local Headers
#include "../CPrior.h"

//**********************************************************************
//
//
//**********************************************************************
class CNormalByStdevPrior : public CPrior {
public:
  // Functions
  CNormalByStdevPrior();
  virtual                    ~CNormalByStdevPrior();
  CPrior*                    clone() { return new CNormalByStdevPrior(*this); }
  void                       validate();
  double                     getResult(double Param);

protected:
  // Variables
  double                     dMu;
  double                     dSigma;
};

#endif /*CNORMALBYSTDEVPRIOR_H_*/
