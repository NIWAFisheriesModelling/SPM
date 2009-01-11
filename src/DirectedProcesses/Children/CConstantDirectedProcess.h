//============================================================================
// Name        : CConstantDirectedProcess.h
// Author      : A. Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONSTANTDIRECTEDPROCESS_H_
#define CCONSTANTDIRECTEDPROCESS_H_

// Local Headers
#include "../CDirectedProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CConstantDirectedProcess : public CDirectedProcess {
public:
  // Functions
	CConstantDirectedProcess(CConstantDirectedProcess *Process = 0);
	virtual                    ~CConstantDirectedProcess();
	CDirectedProcess*          clone() { return (new CConstantDirectedProcess(this)); };
	double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void                       validate();
};

#endif /*CCONSTANTDIRECTEDPROCESS_H_*/
