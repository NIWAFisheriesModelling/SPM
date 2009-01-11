//============================================================================
// Name        : CDirectedProcessFactory.cpp
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CDirectedProcessFactory.h"
#include "../../Translations/Translations.h"
#include "../Children/CConstantDirectedProcess.h"
#include "../Children/CDoubleNormalDirectedProcess.h"
#include "../Children/CExponentialDirectedProcess.h"
#include "../Children/CInverseLogisticDirectedProcess.h"
#include "../Children/CLogisticDirectedProcess.h"
#include "../Children/CNormalDirectedProcess.h"
#include "../Children/CThresholdDirectedProcess.h"

//**********************************************************************
// CDirectedProcess* CDirectedProcessFactory::buildDirectedProcess(string type)
// Build our Directed Process
//**********************************************************************
CDirectedProcess* CDirectedProcessFactory::buildDirectedProcess(string type) {

  if (type == PARAM_CONSTANT)
    return new CConstantDirectedProcess();
  else if (type == PARAM_DOUBLE_NORMAL)
    return new CDoubleNormalDirectedProcess();
  else if (type == PARAM_EXPONENTIAL)
    return new CExponentialDirectedProcess();
  else if (type == PARAM_INVERSE_LOGISTIC)
    return new CInverseLogisticDirectedProcess();
  else if (type == PARAM_NORMAL)
    return new CNormalDirectedProcess();
  else if (type == PARAM_THRESHOLD)
    return new CThresholdDirectedProcess();
  else
    throw string("Unknown type: " + type); // TODO: ADD CErrir Handler

  return 0;
}
