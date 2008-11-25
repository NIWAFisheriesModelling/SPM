//============================================================================
// Name        : CUniformMovementProcess.h
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CUNIFORMMOVEMENTPROCESS_H_
#define CUNIFORMMOVEMENTPROCESS_H_

// Local Headers
#include "../CMovementProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CUniformMovementProcess : public CMovementProcess {
public:
	CUniformMovementProcess(CUniformMovementProcess *Process = 0);
	virtual                    ~CUniformMovementProcess();
	CProcess*                  clone() { return (new CUniformMovementProcess(this)); }
	void                       validate();
	void                       build();
	void                       execute();
};

#endif /*CUNIFORMMOVEMENTPROCESS_H_*/

