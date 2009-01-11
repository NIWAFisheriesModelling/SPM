//============================================================================
// Name        : CTimeStepManager.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : This class is responsible for holding and executing our
//       TimeSteps. Like each "Manager" it calls validate, build and
//       execute when required.
//
//       When the world is running, each year is broken down into a user
//       defined amount of "Steps". These steps are called "TimeSteps".
//       Each TimeStep has processes assigned to it that it will execute when
//       it is called. This is the basis for how our simulation runs.
//
// $Date$
//============================================================================
#ifndef CTIMESTEPMANAGER_H_
#define CTIMESTEPMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseBuildableObject.h"

// Classes
class CTimeStep;

//**********************************************************************
//
//
//**********************************************************************
class CTimeStepManager : public CBaseBuildableObject {
public:
  static CTimeStepManager*   Instance();
  static void                Destroy();

  // Functions
  void                       addTimeStep(CTimeStep *value);
  int                        getTimeStepCount() { return vTimeStepList.size(); }
  CTimeStep*                 getTimeStep(int index);
  int                        getCurrentYear() { return iCurrentYear; }
  int                        getCurrentTimeStep() { return iCurrentTimeStep; }
  void                       clone(CTimeStepManager *Manager);
	void                       validate();
	void                       build();
	void                       execute(int Year, int Step);
  virtual                    ~CTimeStepManager();

protected:
  // Functions
  CTimeStepManager();

  // Variables
  int                        iNumberOfYears;
  int                        iCurrentYear;
  int                        iCurrentTimeStep;
  vector<CTimeStep*>         vTimeStepList;

private:
  static boost::thread_specific_ptr<CTimeStepManager> clInstance;
};

#endif /*CTIMESTEPMANAGER_H_*/
