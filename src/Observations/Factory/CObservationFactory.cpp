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
#include "../../Translations/Translations.h"
#include "../Children/CAbundanceObservation.h"
#include "../Children/CProportionsAtAgeObservation.h"
#include "../Children/CProportionsByCategoryObservation.h"


//**********************************************************************
// CObservation* CObservationFactory::buildObservation(string type)
// Build our Observation of type
//**********************************************************************
CObservation* CObservationFactory::buildObservation(string type) {

  if (type == PARAM_ABUNDANCE)
    return new CAbundanceObservation();
  else if (type == PARAM_PROPORTIONS_AT_AGE)
    return new CProportionsAtAgeObservation();
  else if (type == PARAM_PROPORTIONS_BY_CATEGORY)
    return new CProportionsByCategoryObservation();
  else
    throw string("Unknown type: " + type); // TODO: FIX ME

  return 0;
}
