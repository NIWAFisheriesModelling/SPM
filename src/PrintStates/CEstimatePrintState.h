//============================================================================
// Name        : CEstimatePrintState.h
// Author      : S.Rasmussen
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CESTIMATEPRINTSTATE_H_
#define CESTIMATEPRINTSTATE_H_

// Local Includes
#include "CPrintState.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimatePrintState : public CPrintState {
public:
  // Functions
	CEstimatePrintState();
	virtual                    ~CEstimatePrintState();
	void                       execute();
};

#endif /*CESTIMATEPRINTSTATE_H_*/
