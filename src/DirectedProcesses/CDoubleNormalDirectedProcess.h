//============================================================================
// Name        : CDoubleNormalDirectedProcess.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDOUBLENORMALDIRECTEDPROCESS_H_
#define CDOUBLENORMALDIRECTEDPROCESS_H_

// Local Headers
#include "CDirectedProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CDoubleNormalDirectedProcess : public CDirectedProcess {
public:
  // Functions
	CDoubleNormalDirectedProcess(CDoubleNormalDirectedProcess *Process = 0);
	virtual                    ~CDoubleNormalDirectedProcess();
	void                       setSigmaL(double value) { dSigmaL = value; }
	double                     getSigmaL() { return dSigmaL; }
	void                       setSigmaR(double value) { dSigmaR = value; }
	double                     getSigmaR() { return dSigmaR; }
  void                       setMu(double value) { dMu = value; }
  double                     getMu() { return dMu; }
	double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
	CDirectedProcess*          clone() { return (new CDoubleNormalDirectedProcess(this)); }
	void                       validate();

protected:
  // Variables
  double                     dSigmaL;
  double                     dSigmaR;
  double                     dMu;
};

#endif /*CDOUBLENORMALDIRECTEDPROCESS_H_*/
