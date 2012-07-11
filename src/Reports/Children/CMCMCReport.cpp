//============================================================================
// Name        : CMCMCReport.cpp
// Author      : S.Rasmussen
// Date        : 26/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CMCMCReport.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../MCMC/CMCMC.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CMCMCReport::CMCMCReport()
// Default Constructor
//**********************************************************************
CMCMCReport::CMCMCReport() {
  // Variables
  //eExecutionState     = STATE_MODELLING;

}

//**********************************************************************
// void CMCMCReport::validate()
// Validate this reporter
//**********************************************************************
void CMCMCReport::validate() {
  try {

    // Validate parent
    CFileReport::validate();

  } catch (string &Ex) {
    Ex = "CMCMCReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCReport::build()
// Build this reporter
//**********************************************************************
void CMCMCReport::build() {
  try {
    // Base
    CFileReport::build();

  } catch (string &Ex) {
    Ex = "CMCMCReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCReport::execute()
// Execute reporter
//**********************************************************************
void CMCMCReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;

    this->start();

    // Print Out
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();

  } catch (string &Ex) {
    Ex = "CMCMCReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// CMCMCReport::~CMCMCReport()
// Destructor
//**********************************************************************
CMCMCReport::~CMCMCReport() {
}
