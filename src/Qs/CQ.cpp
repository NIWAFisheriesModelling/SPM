//============================================================================
// Name        : CQ.cpp
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CQ.h"

//**********************************************************************
// CQ::CQ(CQ *Q = 0)
// Default Constructor
//**********************************************************************
CQ::CQ(CQ *Q)
: CBaseExecutableObject(Q) {
  // Variables
  dQ      = 0.0;

  registerEstimable(PARAM_Q, &dQ);

  // Copy Construct
  if (Q != 0) {
    dQ = Q->getQ();
  }
}

//**********************************************************************
// CQ::~CQ()
// Default De-Constructor
//**********************************************************************
CQ::~CQ() {
}
