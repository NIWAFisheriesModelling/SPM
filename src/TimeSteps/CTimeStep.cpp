//============================================================================
// Name        : CTimeStep.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CTimeStep.h"
#include "../CProcessManager.h"
#include "../Processes/CProcess.h"

//**********************************************************************
// CTimeStep::CTimeStep(CTimeStep *TimeStep = 0)
// Default Constructor
//**********************************************************************
CTimeStep::CTimeStep(CTimeStep *TimeStep)
: CBaseExecutableObject(TimeStep) {

  // Vars
  iStep           = -1;
  iNumberOfYears  = -1;

  // Clear
  vPopulationList.clear();
  vMovementList.clear();
  vProcessList.clear();

  // Copy Construct
  if (TimeStep != 0) {
    iStep           = TimeStep->getStep();
    iNumberOfYears  = TimeStep->getNumberOfYears();

    // Copy Vectors
    for (int i = 0; i < TimeStep->getPopulationProcessCount(); ++i)
      vPopulationList.push_back(TimeStep->getPopulationProcess(i));
    for (int i = 0; i < TimeStep->getMovementProcessCount(); ++i)
      vMovementList.push_back(TimeStep->getMovementProcess(i));
  }
}

//**********************************************************************
// void CTimeStep::addPopulationProcess(string value)
// Add Population Process
//**********************************************************************
void CTimeStep::addPopulationProcess(string value) {
  vPopulationList.push_back(value);
}

//**********************************************************************
// string CTimeStep::getPopulationProcess(int index)
// Return population process from our vector @ index
//**********************************************************************
string CTimeStep::getPopulationProcess(int index) {
  return vPopulationList[index];
}

//**********************************************************************
// void CTimeStep(string value)
// Add Movement Process
//**********************************************************************
void CTimeStep::addMovementProcess(string value) {
  vMovementList.push_back(value);
}

//**********************************************************************
// string CTimeStep::getMovementProcess(int index)
// Return movement process from vector @ index
//**********************************************************************
string CTimeStep::getMovementProcess(int index) {
  return vMovementList[index];
}

//**********************************************************************
// void CTimeStep::validate()
// Validate Time Step
//**********************************************************************
void CTimeStep::validate() {
  try {

    // Make sure we have some processes
    if (getPopulationProcessCount() == 0)
      if (getMovementProcessCount() == 0)
        errorMissing(PARAM_PROCESSES);

    if ( (iStep == -1) && (iNumberOfYears == -1) )
      throw string(ERROR_MISSING_YEARS_STEP);

    // Make sure the StepNumber is < TotalSteps
    // IF We are using Steps
    if (iStep >= 0)
      if (iStep > pConfig->getNumberOfTimeSteps())
        errorGreaterThan(PARAM_STEP, PARAM_TIME_STEPS);

  } catch(string Ex) {
    Ex = "CTimeStep.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStep::build()
//
//**********************************************************************
void CTimeStep::build() {
  try {
    // If we don't have any years,
    // Set it to 1
    if (iNumberOfYears == -1)
          iNumberOfYears = 1;

    // Now Lets Build Our Relationships
    CProcessManager *pProcessManager = CProcessManager::Instance();

    // Loop Through Our Population Processes and Get Pointers To Each
    foreach(string Label, vPopulationList) {
      vProcessList.push_back(pProcessManager->getProcess(Label));
    }

    // Do The Same For Movements
    foreach(string Label, vMovementList) {
      vProcessList.push_back(pProcessManager->getProcess(Label));
    }

  } catch (string Ex) {
    Ex = "CTimeStep.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStep::execute()
// Execute This TimeStep
//**********************************************************************
void CTimeStep::execute() {
#ifndef OPTIMISE
  try {
#endif
    // Loop Through and Execute
    for (int i = 0; i < iNumberOfYears; i++) {
      foreach(CProcess* Process, vProcessList) {
        Process->execute();
        pWorld->mergeDifferenceGrid();
      }
    }

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CTimeStep.execute()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CTimeStep::~CTimeStep()
// Default De-Constructor
//**********************************************************************
CTimeStep::~CTimeStep() {
  // Don't need to delete process.
  // This is done in process manager.
  vPopulationList.clear();
  vMovementList.clear();
  vProcessList.clear();
}
