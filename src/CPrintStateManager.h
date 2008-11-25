//============================================================================
// Name        : CPrintStateManager.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : This class is responsible for holding our PrintStates.
//       Like all Manager it is responsible for the validate, build and
//       execute calls to our children.
//
//       A PrintState generates defined output (a report/CSV etc) at a given
//       time during our model's run.
//
//       PrintStates are valid only during RunMode. Because the other modes
//       require the model to be run N times.
//
// $Date$
//============================================================================
#ifndef CPRINTSTATEMANAGER_H_
#define CPRINTSTATEMANAGER_H_

// Local Includes
#include "BaseClasses/CBaseBuildableObject.h"

// Classes
class CPrintState;

//**********************************************************************
//
//
//**********************************************************************
class CPrintStateManager : public CBaseBuildableObject {
public:
  static CPrintStateManager*  Instance();
  static void                 Destroy();
  // Functions
	void                       addPrintState(CPrintState* PrintState);
	int                        getPrintStateCount() { return vPrintStateList.size(); }
	void                       validate();
	void                       build();
	void                       execute(EState state);
	void                       execute();
	virtual                    ~CPrintStateManager();

protected:
  // Functions
  CPrintStateManager();

  // Variables
  vector<CPrintState*>        vPrintStateList;

private:
  // Variables
  //static CPrintStateManager* clInstance;
  static boost::thread_specific_ptr<CPrintStateManager> clInstance;
};

#endif /*CPRINTSTATEMANAGER_H_*/
