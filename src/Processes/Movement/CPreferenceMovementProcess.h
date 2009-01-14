//============================================================================
// Name        : CPreferenceMovementProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPREFERENCEMOVEMENTPROCESS_H_
#define CPREFERENCEMOVEMENTPROCESS_H_

// Local headers
#include "Base/CMovementProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CPreferenceMovementProcess : public CMovementProcess {
public:
  // Functions
  CPreferenceMovementProcess(CPreferenceMovementProcess *Process = 0);
  virtual                     ~CPreferenceMovementProcess();
  CProcess*                  clone() { return (new CPreferenceMovementProcess(this)); }
  void                       validate();
  void                       build();
  void                       execute();
};

#endif /* CPREFERENCEMOVEMENTPROCESS_H_ */
