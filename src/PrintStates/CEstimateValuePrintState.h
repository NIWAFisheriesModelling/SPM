//============================================================================
// Name        : CEstimateValuePrintState.h
// Author      : S.Rasmussen
// Date        : 12/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CESTIMATEVALUEPRINTSTATE_H_
#define CESTIMATEVALUEPRINTSTATE_H_

// Local Headers
#include "CPrintState.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimateValuePrintState: public CPrintState {
public:
  // Functions
  CEstimateValuePrintState();
  virtual                    ~CEstimateValuePrintState();
  void                       execute();

protected:
  // Variables
  bool                       bHeaderWritten;
};

#endif /* CESTIMATEVALUEPRINTSTATE_H_ */
