//============================================================================
// Name        : CMCMCManager.h
// Author      : S.Rasmussen
// Date        : 10/11/2014
// Copyright   : Copyright NIWA Science ©2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CMCMCMANAGER_H_
#define CMCMCMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CMCMC;

/**
 * Class definition
 */
class CMCMCManager : public CBaseManager {
public:
  // methods
  static CMCMCManager*        Instance();
  static void                 Destroy();
  virtual                     ~CMCMCManager();
  void                        addMCMC(CMCMC* value);
  CMCMC*                      getMCMC(string Label);
  void                        clone(CMCMCManager *Manager);
  void                        validate();
  void                        build();
  void                        rebuild();

private:
  // methods
  CMCMCManager();

  // members
  vector<CMCMC*>            vMCMCList;
  static boost::thread_specific_ptr<CMCMCManager> clInstance;
};

#endif /* CMCMCMANAGER_H_ */
