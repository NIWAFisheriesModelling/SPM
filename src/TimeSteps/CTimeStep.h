//============================================================================
// Name        : CTimeStep.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
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
  //int                        getProcessCount() { return vProcessNames.size(); }
  //string                     getProcess(int index);
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Variables
  vector<string>              vProcessNames;
  vector<CProcess*>           vProcesses;
};

#endif /*CTIMESTEP_H_*/
