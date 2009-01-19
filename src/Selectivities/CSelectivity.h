//============================================================================
// Name        : CSelectivity.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CSELECTIVITY_H_
#define CSELECTIVITY_H_

// Local Headers
#include "../BaseClasses/CBaseExecutableObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CSelectivity : public CBaseExecutableObject {
public:
  // Functions
  CSelectivity(CSelectivity *Selectivity = 0);
  virtual                    ~CSelectivity();
	virtual double             getResult(int Index) = 0;
	virtual CSelectivity*      clone() = 0;
	virtual void               validate();
	virtual void               build() { }
	void                       execute() { }
};

#endif /*CSELECTIVITY_H_*/
