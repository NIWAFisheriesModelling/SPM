//============================================================================
// Name        : CReporter.h
// Author      : S.Rasmussen
// Date        : 5/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CREPORTER_H_
#define CREPORTER_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

//**********************************************************************
//
//
//**********************************************************************
class CReporter : public CBaseExecute {
public:
  // Functions
  CReporter();
  virtual                     ~CReporter();
  virtual CReporter*          clone() = 0;
  virtual void                validate() { CBaseExecute::validate(); };
  virtual void                build() { };
  virtual void                start() = 0;
  virtual void                execute() = 0;
  virtual void                end() = 0;
  EState                      getExecutionState() { return eExecutionState; }

protected:
  // Variables
  EState                      eExecutionState;
};

#endif /* CREPORTER_H_ */
