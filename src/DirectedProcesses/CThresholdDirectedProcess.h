//============================================================================
// Name        : CThresholdDirectedProcess.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CTHRESHOLDDIRECTEDPROCESS_H_
#define CTHRESHOLDDIRECTEDPROCESS_H_

// Local Headers
#include "CDirectedProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CThresholdDirectedProcess : public CDirectedProcess {
public:
  // Functions
	CThresholdDirectedProcess(CThresholdDirectedProcess *Process = 0);
	virtual                    ~CThresholdDirectedProcess();
	double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void                       setN(double value) { dN = value; }
  double                     getN() { return dN; }
  void                       setLambda(double value) { dLambda = value; }
  double                     getLambda() { return dLambda; }
  CDirectedProcess*          clone() { return (new CThresholdDirectedProcess(this)); }
  void                       validate();

protected:
  // Variables
  double                     dN;
  double                     dLambda;

};

#endif /*CTHRESHOLDDIRECTEDPROCESS_H_*/
