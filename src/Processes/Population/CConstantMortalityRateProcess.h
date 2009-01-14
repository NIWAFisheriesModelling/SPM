//============================================================================
// Name        : CConstantMortalityRateProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONSTANTMORTALITYRATEPROCESS_H_
#define CCONSTANTMORTALITYRATEPROCESS_H_

// Local headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CConstantMortalityRateProcess : public CProcess {
public:
  // Functions
  CConstantMortalityRateProcess(CConstantMortalityRateProcess *Process = 0);
  virtual                     ~CConstantMortalityRateProcess();
  CProcess*                   clone() { return (new CConstantMortalityRateProcess(this)); }
  void                        validate();
  void                        build();
  void                        execute();
};

#endif /* CCONSTANTMORTALITYRATEPROCESS_H_ */
