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
	virtual double             getResult(int Index);
	virtual CSelectivity*      clone() = 0;
	virtual void               validate();
	virtual void               build();
	virtual void               rebuild();
	void                       execute() { };

protected:
  // Functions
  virtual double             calculateResult(int Age) = 0;

  // Variables
  vector<double>             vResults;

};

#endif /*CSELECTIVITY_H_*/
