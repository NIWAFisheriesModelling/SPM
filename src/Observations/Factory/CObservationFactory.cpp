//============================================================================
// Name        : CObservationFactory.cpp
// Author      : S.Rasmussen
// Date        : 9/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CObservationFactory.h"
#include "../CObservationManager.h"
#include "../../Translations/Translations.h"
#include "../Children/CAbundanceObservation.h"
#include "../Children/CProportionsAtAgeObservation.h"
#include "../Children/CProportionsByCategoryObservation.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CObservation* CObservationFactory::buildObservation(string type, bool registerWithManager)
// Build our Observation of type
//**********************************************************************
CObservation* CObservationFactory::buildObservation(string type, bool registerWithManager) {

  CObservation *pObservation = 0;

  if (type == PARAM_ABUNDANCE)
    pObservation = new CAbundanceObservation();
  else if (type == PARAM_PROPORTIONS_AT_AGE)
    pObservation = new CProportionsAtAgeObservation();
  else if (type == PARAM_PROPORTIONS_BY_CATEGORY)
    pObservation = new CProportionsByCategoryObservation();
  else
    CError::errorUnknown(PARAM_OBSERVATION, type);

  if (registerWithManager)
    CObservationManager::Instance()->addObservation(pObservation);

  return pObservation;
}
