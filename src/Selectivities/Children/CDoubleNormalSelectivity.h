//============================================================================
// Name        : CDoubleNormalSelectivity.h
// Author      :
// Date        : 6/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDOUBLENORMALSELECTIVITY_H_
#define CDOUBLENORMALSELECTIVITY_H_

#include "../CSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CDoubleNormalSelectivity : public CSelectivity {
public:
  // Functions
	CDoubleNormalSelectivity(CDoubleNormalSelectivity *Selectivity = 0);
	virtual                    ~CDoubleNormalSelectivity();
	void                       setMu(double value) { dMu = value; }
	double                     getMu() { return dMu; }
	void                       setSigmaL(double value) { dSigmaL = value; }
	double                     getSigmaL() { return dSigmaL; }
	void                       setSigmaR(double value) { dSigmaR = value; }
	double                     getSigmaR() { return dSigmaR; }
	CSelectivity*              clone() { return (new CDoubleNormalSelectivity(this)); }
	void                       validate();

protected:
  // Functions
  double                     calculateResult(int Age);

	// Variables
	double                     dMu;
	double                     dSigmaL;
	double                     dSigmaR;
};

#endif /*CDOUBLENORMALSELECTIVITY_H_*/
