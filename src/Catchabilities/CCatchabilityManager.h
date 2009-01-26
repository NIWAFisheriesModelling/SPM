//============================================================================
// Name        : CCatchabilityManager.h
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CQMANAGER_H_
#define CQMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseObject.h"

// Classes
class CCatchability;

//**********************************************************************
//
//
//**********************************************************************
class CCatchabilityManager : public CBaseObject {
public:
  static CCatchabilityManager*         Instance();
  static void               Destroy();

  // Functions
  void                       addQ(CCatchability *Q);
  int                        getQCount() { return vQList.size(); }
  CCatchability*                        getQ(string label);
  CCatchability*                        getQ(int index);
  void                       clone(CCatchabilityManager *Manager);
  virtual                    ~CCatchabilityManager();

protected:
  // Functions
	CCatchabilityManager();

	// Variables
	vector<CCatchability*>                vQList;

private:
  // Variables
  static boost::thread_specific_ptr<CCatchabilityManager> clInstance;
};

#endif /*CQMANAGER_H_*/
