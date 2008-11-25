//============================================================================
// Name        : CKnifeEdgeSelectivity.h
// Author      : A. Dunn
// Date        : 12/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CKNIFEEDGESELECTIVITY_H_
#define KNIFEEDGESELECTIVITY_H_

// Local Headers
#include "CSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CKnifeEdgeSelectivity : public CSelectivity {
public:
  // Functions
	CKnifeEdgeSelectivity(CKnifeEdgeSelectivity *Selectivity = 0);
	virtual                    ~CKnifeEdgeSelectivity();
  void                       setC(double value) { dC = value; }
  double                     getC() { return dC; }
  CSelectivity*              clone() { return (new CKnifeEdgeSelectivity(this)); }
  void                       validate();
  void                       build() { }; // Prevent Parent
  void                       rebuild() { }; // Prevent Parent
  double                     getResult(int Param);

protected:
  // Functions
  double                     calculateResult(int Age);

  // Variables
  double                     dC;
};

#endif /*KNIFEEDGESELECTIVITY_H_*/
