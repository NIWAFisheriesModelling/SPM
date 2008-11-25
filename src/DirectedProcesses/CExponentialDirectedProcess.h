//============================================================================
// Name        : CExponentialDirectedProcess.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CEXPONENTIALDIRECTEDPROCESS_H_
#define CEXPONENTIALDIRECTEDPROCESS_H_

// Local Headers
#include "CDirectedProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CExponentialDirectedProcess : public CDirectedProcess {
public:
  // Functions
	CExponentialDirectedProcess(CExponentialDirectedProcess *Process = 0);
	virtual                    ~CExponentialDirectedProcess();
  void                       setLambda(double value) { dLambda = value; }
  double                     getLambda() { return dLambda; }
	double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
	CDirectedProcess*          clone() { return (new CExponentialDirectedProcess(this)); }
	void                       validate();

protected:
  double                     dLambda;
};

#endif /*CEXPONENTIALDIRECTEDPROCESS_H_*/
