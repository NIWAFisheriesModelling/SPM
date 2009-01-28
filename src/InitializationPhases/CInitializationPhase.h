//============================================================================
// Name        : CInitializationPhase.h
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINITIALIZATIONPHASE_H_
#define CINITIALIZATIONPHASE_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes
class CProcess;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationPhase : public CBaseExecute {
public:
  CInitializationPhase();
  virtual                     ~CInitializationPhase();
  CInitializationPhase*       clone() { return (new CInitializationPhase(*this)); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  int                         iYears;
  vector<string>              vProcessNames;
  vector<CProcess*>           vProcesses;
};

#endif /* CINITIALIZATIONPHASE_H_ */
