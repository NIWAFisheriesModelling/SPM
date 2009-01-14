//============================================================================
// Name        : CBHRecruitmentProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBHRecruitmentProcess.h"

//**********************************************************************
// CBHRecruitmentProcess::CBHRecruitmentProcess(CBHRecruitmentProcess *Process)
// Default constructor
//**********************************************************************
CBHRecruitmentProcess::CBHRecruitmentProcess(CBHRecruitmentProcess *Process)
: CProcess(Process) {

  // Register Allowed variables
  pParameterList->registerAllowed(PARAM_R0);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_AGES);
  pParameterList->registerAllowed(PARAM_STEEPNESS);
  pParameterList->registerAllowed(PARAM_SIGMA_R);
  pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_SSB);
  pParameterList->registerAllowed(PARAM_YCS_VALUES);
  pParameterList->registerAllowed(PARAM_YCS_YEARS);
}

//**********************************************************************
// void CBHRecruitmentProcess::validate()
// Validate the process
//**********************************************************************
void CBHRecruitmentProcess::validate() {
  try {
    // Validate parent
    CProcess::validate();

    // Assign our variables
    dR0           = pParameterList->getDouble(PARAM_R0);
    dSteepness    = pParameterList->getDouble(PARAM_STEEPNESS);
    dSigmaR       = pParameterList->getDouble(PARAM_SIGMA_R);
    dRho          = pParameterList->getDouble(PARAM_RHO);
    sSSB          = pParameterList->getString(PARAM_SSB);

    pParameterList->fillVector(vProportions, PARAM_PROPORTIONS);
    pParameterList->fillVector(vAges, PARAM_AGES);
    pParameterList->fillVector(vYCSValues, PARAM_YCS_VALUES);
    pParameterList->fillVector(vYCSYears, PARAM_YCS_YEARS);

  } catch (string Ex) {
    Ex = "CBHRecruitment.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBHRecruitmentProcess::build()
// Build the process
//**********************************************************************
void CBHRecruitmentProcess::build() {
  try {
    // TODO: Implement this function
    throw string("Not implemented");
  } catch (string Ex) {
    Ex = "CBHRecruitment.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBHRecruitmentProcess::execute()
// Execute this process
//**********************************************************************
void CBHRecruitmentProcess::execute() {
  try {
    // TODO: Implement this function
    throw string("Not implemented");
  } catch (string Ex) {
    Ex = "CBHRecruitment.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CBHRecruitmentProcess::~CBHRecruitmentProcess()
// Destructor
//**********************************************************************
CBHRecruitmentProcess::~CBHRecruitmentProcess() {
}
