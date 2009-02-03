//============================================================================
// Name        : CPrior.h
// Author      : S.Rasmussen
// Date        : 10/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPRIOR_H_
#define CPRIOR_H_

// Local Headers
#include "../BaseClasses/CBaseValidate.h"

//**********************************************************************
//
//
//**********************************************************************
class CPrior : public CBaseValidate {
public:
  // Functions
	CPrior();
	virtual                    ~CPrior();
	virtual CPrior*            clone() = 0;
	virtual double             getResult(double param) = 0;
  virtual void               validate() = 0;
};

#endif /*CPRIOR_H_*/
