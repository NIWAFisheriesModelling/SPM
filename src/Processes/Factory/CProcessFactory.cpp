//============================================================================
// Name        : CProcessFactory.cpp
// Author      : S.Rasmussen
// Date        : 5/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CProcessFactory.h"
#include "../../Translations/Translations.h"
#include "../Movement/CDirectedMovementProcess.h"
#include "../Population/CAgeingProcess.h"
#include "../Population/CCategoryTransitionProcess.h"
#include "../Population/CEventMortalityProcess.h"
#include "../Population/CNaturalMortalityProcess.h"
#include "../Population/CConstantRecruitmentProcess.h"

//**********************************************************************
// CProcessFactory::CProcessFactory()
// Default Constructor
//**********************************************************************
CProcess* CProcessFactory::buildProcess(string type) {

  if (type == PARAM_AGEING)
    return new CAgeingProcess();
  else if (type == PARAM_CONSTANT_RECRUITMENT)
    return new CConstantRecruitmentProcess();
  else if (type == PARAM_NATURAL_MORTALITY)
    return new CNaturalMortalityProcess();
  else if (type == PARAM_EVENT_MORTALITY)
    return new CEventMortalityProcess();
  else if (type == PARAM_CATEGORY_TRANSITION)
    return new CCategoryTransitionProcess();
  else if (type == PARAM_DIRECTED)
    return new CDirectedMovementProcess();
  else
    throw string("Unknown process type: " + type); // TODO: Finish This

  return 0;
}
