//============================================================================
// Name        : CSelectivityManager.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : This class is responsible for holding our Selectivities.
//       A Selectivity is a defined function that is applied during a process
//       to achieve a known result. Each Selectivity represents a unique
//       algorithm.
//
// $Date$
//============================================================================
#ifndef CSELECTIVITYMANAGER_H_
#define CSELECTIVITYMANAGER_H_

// Local Headers
#include "BaseClasses/CBaseBuildableObject.h"

// Classes
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CSelectivityManager : public CBaseBuildableObject {
public:
  static CSelectivityManager*   Instance();
  static void                Destroy();

  // Functions
	void                       addSelectivity(CSelectivity* Selectivity);
	int                        getSelectivityCount() { return vSelectivityList.size(); }
	int                        getSelectivityIndex(string Label);
	CSelectivity*              getSelectivity(string Label);
	CSelectivity*              getSelectivity(int index);
	void                       clone(CSelectivityManager *Manager);
	void                       validate();
	void                       build();
	void                       rebuild();
	virtual                    ~CSelectivityManager();

protected:
  // Functions
  CSelectivityManager();

  // Variables
  vector<CSelectivity*>       vSelectivityList;

private:
  static boost::thread_specific_ptr<CSelectivityManager> clInstance;
};

#endif /*CSELECTIVITYMANAGER_H_*/
