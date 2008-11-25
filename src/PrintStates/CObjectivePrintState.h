//============================================================================
// Name        : CObjectivePrintState.h
// Author      : S.Rasmussen
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBJECTIVEPRINTSTATE_H_
#define COBJECTIVEPRINTSTATE_H_

// Local Includes
#include "CPrintState.h"

//**********************************************************************
//
//
//**********************************************************************
class CObjectivePrintState : public CPrintState {
public:
  // Functions
	CObjectivePrintState();
	virtual                    ~CObjectivePrintState();
	void                       execute();
};

#endif /*COBJECTIVEPRINTSTATE_H_*/
