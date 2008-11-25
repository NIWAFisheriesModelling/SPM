//============================================================================
// Name        : CNormalDirectedProcess.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALDIRECTEDPROCESS_H_
#define CNORMALDIRECTEDPROCESS_H_

// Local Headers
#include "CDirectedProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CNormalDirectedProcess : public CDirectedProcess {
public:
  // Functions
	CNormalDirectedProcess(CNormalDirectedProcess *Process = 0);
	virtual                    ~CNormalDirectedProcess();
  void                       setMu(double value) { dMu = value; }
  double                     getMu() { return dMu; }
  void                       setSigma(double value) { dSigma = value; }
  double                     getSigma() { return dSigma; }
	double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
	CDirectedProcess*          clone() { return (new CNormalDirectedProcess(this)); }
	void                       validate();

protected:
  // Variables
  double                     dMu;
  double                     dSigma;

};

#endif /*CNORMALDIRECTEDPROCESS_H_*/
