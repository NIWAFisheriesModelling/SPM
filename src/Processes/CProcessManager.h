//============================================================================
// Name        : CProcessManager.h
// Author      : S.Rasmussen
// Date        : 12/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This class is responsible for maintaining our
//       processes. Like all Managers it is responsible for the build and
//       validate calls to the children.
//
//       The main functionality of this class involves serving back pointers
//       to our processes for the TimeSteps. This allows the TimeSteps to
//       reference pointers directly to increase the speed of our model.
//
//       There are 2 main types of processes. Population processes, which act
//       on a single Grid-Square; and Movement Processes, which act between
//       Grid-Squares.
//
// $Date$
//============================================================================
#ifndef CPROCESSMANAGER_H_
#define CPROCESSMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseBuildableObject.h"

// Classes
class CProcess;

//**********************************************************************
//
//
//**********************************************************************
class CProcessManager : public CBaseBuildableObject {
public:
  static CProcessManager*   Instance();
  static void               Destroy();

  // Functions
  void                        addProcess(CProcess* value);
  int                         getProcessCount() { return vProcessList.size(); }
  CProcess*                   getProcess(string Label);
  CProcess*                   getProcess(int index);
  void                        clone(CProcessManager *Manager);
  void                        validate();
  void                        build();
  void                        rebuild();
  virtual                     ~CProcessManager();

protected:
  // Functions
  CProcessManager();

	// Variables
	vector<CProcess*>            vProcessList;

private:
  static boost::thread_specific_ptr<CProcessManager> clInstance;
};

#endif /*CPROCESSMANAGER_H_*/