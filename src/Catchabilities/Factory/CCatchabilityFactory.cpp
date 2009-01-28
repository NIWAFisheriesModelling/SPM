//============================================================================
// Name        : CCatchabilityFactory.cpp
// Author      : S.Rasmussen
// Date        : 26/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CCatchabilityFactory.h"
#include "../CCatchabilityManager.h"
#include "../CCatchability.h"

//**********************************************************************
// CCatchability* CCatchabilityFactory::buildCatchability(string type, bool registerWithManager)
// Build a catchability of type
//**********************************************************************
CCatchability* CCatchabilityFactory::buildCatchability(string type, bool registerWithManager) {

  CCatchability *pCatchability = 0;

  if (type == "")
    pCatchability = new CCatchability();
  else
    throw string("unknown type: " + type); // TODO: Add Error

  if (registerWithManager)
    CCatchabilityManager::Instance()->addCatchability(pCatchability);

  return pCatchability;
}
