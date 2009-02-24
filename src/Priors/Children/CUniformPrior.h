//============================================================================
// Name        : CUniformPrior.h
// Author      : S.Rasmussen
// Date        : 10/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CUNIFORMPRIOR_H_
#define CUNIFORMPRIOR_H_

// Local Headers
#include "../CPrior.h"

//**********************************************************************
//
//
//**********************************************************************
class CUniformPrior : public CPrior {
public:
  // Functions
	CUniformPrior();
	virtual                    ~CUniformPrior();
	CPrior*                    clone() { return new CUniformPrior(*this); }
	void                       validate();
	double                     getResult(double Param) { return 0; }

};

#endif /*CUNIFORMPRIOR_H_*/
