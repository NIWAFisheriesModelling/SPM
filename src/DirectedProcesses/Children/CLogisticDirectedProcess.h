//============================================================================
// Name        : CLogisticDirectedProcess.h
// Author      : A. Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLOGISTICDIRECTEDPROCESS_H_
#define CLOGISTICDIRECTEDPROCESS_H_

// Local Headers
#include "../CDirectedProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CLogisticDirectedProcess : public CDirectedProcess {
public:
  // Functions
	CLogisticDirectedProcess(CLogisticDirectedProcess *Process = 0);
	virtual                    ~CLogisticDirectedProcess();
	CDirectedProcess*          clone() { return (new CLogisticDirectedProcess(this)); }
	double                     getA50() { return dA50; }
	double                     getAto95() { return dAto95; }
	double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
	void                       validate();

protected:
  // Variables
  double                     dA50;
  double                     dAto95;
};

#endif /*CLOGISTICDIRECTEDPROCESS_H_*/