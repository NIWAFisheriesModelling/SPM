//============================================================================
// Name        : CGammaDiff.h
// Author      : S.Rasmussen
// Date        : 8/09/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#ifndef CGAMMADIFF_H_
#define CGAMMADIFF_H_

// Local Headers
#include "../CMinimizer.h"

//**********************************************************************
//
//
//**********************************************************************
class CGammaDiff : public CMinimizer {
public:
  // Functions
  CGammaDiff();
  virtual                     ~CGammaDiff();
  void                        runEstimation();
};

#endif /* CGAMMADIFF_H_ */
