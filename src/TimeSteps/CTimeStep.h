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
#include "../BaseClasses/CBaseExecutableObject.h"

// Classes
class CProcess;

//**********************************************************************
//
//
//**********************************************************************
class CTimeStep : public CBaseExecutableObject {
public:
	CTimeStep(CTimeStep *TimeStep = 0);
	virtual                    ~CTimeStep();
  void                       setStep(int value) { iStep = value; }
  int                        getStep() { return iStep; }
  void                       setNumberOfYears(int value) { iNumberOfYears = value; }
  int                        getNumberOfYears() { return iNumberOfYears; }
  void                       addPopulationProcess(string value);
  int                        getPopulationProcessCount() { return vPopulationList.size(); }
  string                     getPopulationProcess(int index);
  void                       addMovementProcess(string value);
  int                        getMovementProcessCount() { return vMovementList.size(); }
  string                     getMovementProcess(int index);
  CTimeStep*                 clone() { return (new CTimeStep(this)); }
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  int               iStep;
  int               iNumberOfYears;
  vector<string>    vPopulationList;
  vector<string>    vMovementList;
  vector<CProcess*> vProcessList;
};

#endif /*CTIMESTEP_H_*/
