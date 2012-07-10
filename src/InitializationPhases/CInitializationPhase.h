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
class CTimeStep;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationPhase : public CBaseExecute {
public:
  CInitializationPhase();
  virtual                     ~CInitializationPhase();
  void                        validate();
  void                        build();
  void                        execute();
  int                         getCurrentTimeStep() { return iCurrentTimeStep; }

protected:
  int                         iYears;
  int                         iCurrentTimeStep;
  vector<string>              vTimeStepNames;
  vector<CTimeStep*>          vTimeSteps;
};

#endif /* CINITIALIZATIONPHASE_H_ */
