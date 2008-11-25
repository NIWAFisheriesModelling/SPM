//============================================================================
// Name        : CWorldGridPrintState.h
// Author      : S.Rasmussen
// Date        : 18/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CWORLDGRIDPRINTSTATE_H_
#define CWORLDGRIDPRINTSTATE_H_

// Local Headers
#include "CPrintState.h"

//**********************************************************************
//
//
//**********************************************************************
class CWorldGridPrintState : public CPrintState {
public:
  // Functions
	CWorldGridPrintState();
	virtual                    ~CWorldGridPrintState();
  void                       setYear(int value) { iYear = value; }
  int                        getYear() { return iYear; }
  void                       setStep(int value) { iStep = value; }
  int                        getStep() { return iStep; }
  void                       validate();
	void                       execute();

protected:
  // Variables
  int                        iYear;
  int                        iStep;
};

#endif /*CWORLDGRIDPRINTSTATE_H_*/
