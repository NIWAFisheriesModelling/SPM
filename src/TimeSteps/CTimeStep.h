//============================================================================
// Name        : CTimeStep.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : A time-step is a unit of work in out model.
//              Each time step will execute multiple processes during it's
//              execution.
// $Date$
//============================================================================
#ifndef CTIMESTEP_H_
#define CTIMESTEP_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes
class CProcess;

//**********************************************************************
//
//
//**********************************************************************
class CTimeStep : public CBaseExecute {
public:
	CTimeStep();
	virtual                    ~CTimeStep();
  CTimeStep*                  clone() { return new CTimeStep(*this); }
  void                        validate();
  void                        build();
  void                        execute();
  vector<string>              getProcessNames() { return vProcessNames; }

protected:
  // Variables
  vector<string>              vProcessNames;
  vector<CProcess*>           vProcesses;
};

#endif /*CTIMESTEP_H_*/
