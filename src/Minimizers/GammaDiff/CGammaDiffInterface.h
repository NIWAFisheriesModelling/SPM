//============================================================================
// Name        : CGammaDiffInterface.h
// Author      : S.Rasmussen
// Date        : 8/09/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#ifndef CGAMMADIFFINTERFACE_H_
#define CGAMMADIFFINTERFACE_H_

// Local Headers
#include "../CMinimizer.h"

//**********************************************************************
//
//
//**********************************************************************
class CGammaDiffInterface : public CMinimizer {
public:
  // Functions
  CGammaDiffInterface();
  virtual                     ~CGammaDiffInterface();
  void                        runEstimation();
};

#endif /* CGAMMADIFFINTERFACE_H_ */
