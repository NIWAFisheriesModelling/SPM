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
#include "../CProcessManager.h"
#include "../../Translations/Translations.h"
#include "../Movement/CPreferenceMovementProcess.h"
#include "../Population/CAgeingProcess.h"
#include "../Population/CCategoryTransitionProcess.h"
#include "../Population/CCategoryTransitionRateProcess.h"
#include "../Population/CEventMortalityProcess.h"
#include "../Population/CNaturalMortalityProcess.h"
#include "../Population/CConstantRecruitmentProcess.h"

//**********************************************************************
// CProcessFactory::CProcessFactory()
// Default Constructor
//**********************************************************************
CProcess* CProcessFactory::buildProcess(string type, bool registerWithManager) {

  CProcess *pProcess = 0;

  if (type == PARAM_AGEING)
    pProcess = new CAgeingProcess();
  else if (type == PARAM_CONSTANT_RECRUITMENT)
    pProcess = new CConstantRecruitmentProcess();
  else if (type == PARAM_NATURAL_MORTALITY)
    pProcess = new CNaturalMortalityProcess();
  else if (type == PARAM_EVENT_MORTALITY)
    pProcess = new CEventMortalityProcess();
  else if (type == PARAM_CATEGORY_TRANSITION)
    pProcess = new CCategoryTransitionProcess();
  else if (type == PARAM_CATEGORY_TRANSITION_RATE)
    pProcess = new CCategoryTransitionRateProcess();
  else if (type == PARAM_PREFERENCE)
    pProcess = new CPreferenceMovementProcess();
  else
    throw string("Unknown process type: " + type); // TODO: Finish This

  if (registerWithManager)
    CProcessManager::Instance()->addProcess(pProcess);

  return pProcess;
}
