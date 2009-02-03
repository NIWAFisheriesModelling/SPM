//============================================================================
// Name        : CAnnualMortalityRateProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CANNUALMORTALITYRATEPROCESS_H_
#define CANNUALMORTALITYRATEPROCESS_H_

// Local headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CAnnualMortalityRateProcess : public CProcess {
public:
  // Functions
  CAnnualMortalityRateProcess();
  virtual                     ~CAnnualMortalityRateProcess();
  CProcess*                   clone() { return new CAnnualMortalityRateProcess(*this); }
  void                        validate();
  void                        build();
  void                        execute();
};

#endif /* CANNUALMORTALITYRATEPROCESS_H_ */
