//============================================================================
// Name        : CInverseLogisticDirectedProcess.h
// Author      : A. Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINVERSELOGISTICDIRECTEDPROCESS_H_
#define CINVERSELOGISTICDIRECTEDPROCESS_H_

// Local Headers
#include "../CDirectedProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CInverseLogisticDirectedProcess : public CDirectedProcess {
public:
  // Functions
	CInverseLogisticDirectedProcess(CInverseLogisticDirectedProcess *Process = 0);
	virtual                    ~CInverseLogisticDirectedProcess();
  CDirectedProcess*          clone() { return (new CInverseLogisticDirectedProcess(this)); }
	double                     getA50() { return dA50; }
	double                     getAto95() { return dAto95; }
	double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
	void                       validate();

protected:
  // Variables
  double                     dA50;
  double                     dAto95;
};

#endif /*CINVERSELOGISTICDIRECTEDPROCESS_H_*/
