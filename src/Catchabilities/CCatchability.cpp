//============================================================================
// Name        : CCatchability.cpp
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CCatchability.h"

//**********************************************************************
// CCatchability::CCatchability(CCatchability *Catchability = 0)
// Default Constructor
//**********************************************************************
CCatchability::CCatchability(CCatchability *Catchability)
: CBaseExecutableObject(Q) {
  // Variables
  dQ      = 0.0;

  registerEstimable(PARAM_Q, &dQ);
}

//**********************************************************************
// CCatchability::~CCatchability()
// Default De-Constructor
//**********************************************************************
CCatchability::~CCatchability() {
}
