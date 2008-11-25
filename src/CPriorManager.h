//============================================================================
// Name        : CPriorManager.h
// Author      : S.Rasmussen
// Date        : 10/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPRIORMANAGER_H_
#define CPRIORMANAGER_H_

// Local Includes
#include "BaseClasses/CBaseObject.h"

// Classes
class CPrior;

//**********************************************************************
//
//
//**********************************************************************
class CPriorManager : public CBaseObject {
public:
  static CPriorManager*      Instance();
  static void                Destroy();

  // Function
	void                       addPrior(CPrior *Prior);
	int                        getPriorCount() { return vPriorList.size(); }
	CPrior*                    getPrior(string Label);
	CPrior*                    getPrior(int index);
	void                       clone(CPriorManager *Manager);
 	void                       validate();
 	virtual                    ~CPriorManager();

protected:
  // Functions
  CPriorManager();

  // Variables
  vector<CPrior*>             vPriorList;

private:
  // Variables
  static boost::thread_specific_ptr<CPriorManager> clInstance;
};

#endif /*CPRIORMANAGER_H_*/
