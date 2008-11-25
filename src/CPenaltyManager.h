//============================================================================
// Name        : CPenaltyManager.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPENALTYMANAGER_H_
#define CPENALTYMANAGER_H_

// Local Headers
#include "BaseClasses/CBaseBuildableObject.h"

// Classes
class CPenalty;

// Structure
struct SFlaggedPenalty {
  string Label;
  double Score;
};

//**********************************************************************
//
//
//**********************************************************************
class CPenaltyManager : public CBaseBuildableObject {
public:
  static CPenaltyManager*    Instance();
  static void                Destroy();

  // Functions
  void                       addPenalty(CPenalty *Penalty);
  int                        getPenaltyCount() { return vPenaltyList.size(); }
  CPenalty*                  getPenalty(string Label);
  CPenalty*                  getPenalty(int index);
  void                       flagPenalty(string Label, double Value);
  void                       clearFlaggedPenaltyList();
  int                        getFlaggedPenaltyCount() { return vFlaggedPenaltyList.size(); }
  SFlaggedPenalty*           getFlaggedPenalty(int Index);
  void                       clone(CPenaltyManager *Manager);
  void                       validate();
  void                       build();
  virtual                    ~CPenaltyManager();

protected:
  // Functions
	CPenaltyManager();

	// Variables
	vector<CPenalty*>          vPenaltyList;
	vector<SFlaggedPenalty>    vFlaggedPenaltyList;

private:
  static boost::thread_specific_ptr<CPenaltyManager>    clInstance;
};

#endif /*CPENALTYMANAGER_H_*/
