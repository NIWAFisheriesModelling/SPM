//============================================================================
// Name        : CInitializationManager.h
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINITIALIZATIONMANAGER_H_
#define CINITIALIZATIONMANAGER_H_

// Local Headers
#include "BaseClasses/CBaseExecutableObject.h"

// Classes
class CTimeStep;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationManager : CBaseBuildableObject {
public:
  static CInitializationManager*   Instance();
  static void                      Destroy();
  // Functions
  void                       addTimeStep(CTimeStep *value);
  int                        getTimeStepCount() { return vTimeStepList.size(); }
  CTimeStep*                 getTimeStep(string label);
  CTimeStep*                 getTimeStep(int index);
  void                       clone(CInitializationManager *Manager);
  void                       validate();
  void                       build();
  virtual                    ~CInitializationManager();

protected:
  // Functions
	CInitializationManager();

  // Variables
	vector<CTimeStep*>         vTimeStepList;

private:
  // Variables
  static boost::thread_specific_ptr<CInitializationManager> clInstance;
};

#endif /*CINITIALISATIONMANAGER_H_*/
