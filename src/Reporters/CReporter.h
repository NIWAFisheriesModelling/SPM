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
#include "../BaseClasses/CBaseExecutableObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CReporter : public CBaseExecutableObject {
public:
  // Functions
  CReporter();
  virtual                     ~CReporter();
  virtual void                validate() { };
  virtual void                build() { };
  virtual void                start() = 0;
  virtual void                execute() = 0;
  virtual void                end() = 0;

};

#endif /* CREPORTER_H_ */
