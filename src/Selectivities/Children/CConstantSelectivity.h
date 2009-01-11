//============================================================================
// Name        : CConstantSelectivity.h
// Author      : S.Rasmussen
// Date        : 6/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONSTANTSELECTIVITY_H_
#define CCONSTANTSELECTIVITY_H_

// Local Headers
#include "../CSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CConstantSelectivity : public CSelectivity {
public:
  // Functions
	CConstantSelectivity(CConstantSelectivity *Selectivity = 0);
	virtual                    ~CConstantSelectivity();
  void                       setC(double value) { dC = value; }
  double                     getC() { return dC; }
  CSelectivity*              clone() { return (new CConstantSelectivity(this)); }
  void                       validate();
  void                       build() { }; // Override parent and blank
  void                       rebuild() { };
  double                     getResult(int Index);

protected:
  // Functions
  double                     calculateResult(int Age);

  // Variables
  double                     dC;
};

#endif /*CCONSTANTSELECTIVITY_H_*/
