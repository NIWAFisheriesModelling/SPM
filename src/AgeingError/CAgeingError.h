//============================================================================
// Name        : CAgeingError.h
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGEINGERROR_H_
#define CAGEINGERROR_H_

// Local headers
#include "../BaseClasses/CBaseValidate.h"

//**********************************************************************
//
//
//**********************************************************************
class CAgeingError : public CBaseValidate {
public:
  // Functions
  CAgeingError();
  virtual                     ~CAgeingError();
  void                        validate() { }
};

#endif /* CAGEINGERROR_H_ */
