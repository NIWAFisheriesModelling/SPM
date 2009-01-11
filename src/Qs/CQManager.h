//============================================================================
// Name        : CQManager.h
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
class CQ;

//**********************************************************************
//
//
//**********************************************************************
class CQManager : public CBaseObject {
public:
  static CQManager*         Instance();
  static void               Destroy();

  // Functions
  void                       addQ(CQ *Q);
  int                        getQCount() { return vQList.size(); }
  CQ*                        getQ(string label);
  CQ*                        getQ(int index);
  void                       clone(CQManager *Manager);
  virtual                    ~CQManager();

protected:
  // Functions
	CQManager();

	// Variables
	vector<CQ*>                vQList;

private:
  // Variables
  static boost::thread_specific_ptr<CQManager> clInstance;
};

#endif /*CQMANAGER_H_*/
