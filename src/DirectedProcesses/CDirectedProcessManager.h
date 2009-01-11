//============================================================================
// Name        : CDirectedProcessManager.h
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CDIRECTEDPROCESSMANAGER_H_
#define CDIRECTEDPROCESSMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseBuildableObject.h"

// Classes
class CDirectedProcess;

//**********************************************************************
//
//
//**********************************************************************
class CDirectedProcessManager : public CBaseBuildableObject {
public:
  static CDirectedProcessManager*      Instance();
  static void                          Destroy();

  // Functions
  void                       addProcess(CDirectedProcess *Process);
  int                        getProcessCount() { return vDirectedProcessList.size(); }
  CDirectedProcess*          getProcess(int index);
  CDirectedProcess*          getProcess(string Label);
  void                       clone(CDirectedProcessManager *Manager);
  void                       validate();
  void                       build();
  virtual                    ~CDirectedProcessManager();

protected:
  // Functions
	CDirectedProcessManager();

	// Variables
	vector<CDirectedProcess*>  vDirectedProcessList;

private:
  static boost::thread_specific_ptr<CDirectedProcessManager> clInstance;
};

#endif /*CDIRECTEDPROCESSMANAGER_H_*/
