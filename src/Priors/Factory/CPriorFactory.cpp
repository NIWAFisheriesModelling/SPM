//============================================================================
// Name        : CPriorFactory.cpp
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPriorFactory.h"
#include "../../Translations/Translations.h"
#include "../Children/CBetaPrior.h"
#include "../Children/CLogNormalPrior.h"
#include "../Children/CNormalByStdevPrior.h"
#include "../Children/CNormalLogPrior.h"
#include "../Children/CNormalPrior.h"
#include "../Children/CUniformLogPrior.h"
#include "../Children/CUniformPrior.h"

//**********************************************************************
//
//
//**********************************************************************
CPrior* CPriorFactory::buildPrior(string type) {

  if (type == PARAM_BETA)
    return new CBetaPrior();
  else if (type == PARAM_LOG_NORMAL)
    return new CLogNormalPrior();
  else if (type == PARAM_NORMAL_BY_STDEV)
    return new CNormalByStdevPrior();
  else if (type == PARAM_NORMAL_LOG)
    return new CNormalLogPrior();
  else if (type == PARAM_NORMAL)
    return new CNormalPrior();
  else if (type == PARAM_UNIFORM_LOG)
    return new CUniformLogPrior();
  else if (type == PARAM_UNIFORM)
    return new CUniformPrior();
  else
    throw string("Unknown type: " + type); // TODO: FIX THIS

  return 0;
}
