//============================================================================
// Name        : CReporterManager.h
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CREPORTERMANAGER_H_
#define CREPORTERMANAGER_H_

// Local headers
#include "../BaseClasses/CBaseManager.h"
#include "../CRuntimeController.h"

// Forward-Dec
class CReporter;

//**********************************************************************
//
//
//**********************************************************************
class CReporterManager: public CBaseManager {
public:
  // Function
  static CReporterManager*    Instance();
  static void                 Destroy();
  virtual                     ~CReporterManager();
  void                        addReporter(CReporter *value);
  void                        clone(CReporterManager *Manager);
  void                        validate();
  void                        build();
  void                        execute();
  void                        execute(EState state);
protected:
  // Functions
  CReporterManager();

  // Variables
  vector<CReporter*>          vReporters;
  vector<CReporter*>          vModellingReporters;

private:
  static boost::thread_specific_ptr<CReporterManager> clInstance;
};

#endif /* CREPORTERMANAGER_H_ */
