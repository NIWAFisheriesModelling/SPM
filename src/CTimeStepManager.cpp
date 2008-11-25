//============================================================================
// Name        : CTimeStepManager.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CTimeStepManager.h >>
// $Date$
//============================================================================

// Local Headers
#include "CTimeStepManager.h"
#include "TimeSteps/CTimeStep.h"

// Single Static variable
 boost::thread_specific_ptr<CTimeStepManager> CTimeStepManager::clInstance;

//**********************************************************************
// CTimeStepManager::CTimeStepManager()
// Default Constructor
//**********************************************************************
CTimeStepManager::CTimeStepManager() {
  // Vars
  vTimeStepList.clear();
}

//**********************************************************************
// CTimeStepManager* CTimeStepManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CTimeStepManager* CTimeStepManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CTimeStepManager());
  return clInstance.get();
}

//**********************************************************************
// void CTimeStepManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CTimeStepManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CTimeStepManager::addTimeStep(CTimeStep *value)
// Add New Time Step To The List
//**********************************************************************
void CTimeStepManager::addTimeStep(CTimeStep *value) {
  vTimeStepList.push_back(value);
}

//**********************************************************************
// CTimeStep* CTimeStepManager::getTimeStep(int index)
// Get the timestep from our vector @ index
//**********************************************************************
CTimeStep* CTimeStepManager::getTimeStep(int index) {
  try {
    if (index >= (int)vTimeStepList.size())
      errorGreaterThanEqualTo(PARAM_INDEX, PARAM_TIME_STEPS);
    if (index < 0)
      errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vTimeStepList[index];

  } catch (string Ex) {
    Ex = "CTimeStepManager.getTimeStep()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CTimeStepManager::clone(CTimeStepManager *Manager)
// Clone the TimeStepManager with the parameter
//**********************************************************************
void CTimeStepManager::clone(CTimeStepManager *Manager) {
  try {

    for (int i = 0; i < Manager->getTimeStepCount(); ++i) {
      CTimeStep *pTimeStep = Manager->getTimeStep(i);
      vTimeStepList.push_back(pTimeStep->clone());
    }

  } catch (string Ex) {
    Ex = "CTimeStepManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStepManager::validate()
// Validate The Time Steps
//**********************************************************************
void CTimeStepManager::validate() {
  try {
    // Vars
    CConfiguration                *pConfig            = CConfiguration::Instance();
    int                           iSteps              = pConfig->getNumberOfTimeSteps();
    map<int, int>                 mTimeStepList;

    // Make Sure We Have Right Amount Loaded
    if (iSteps > (int)vTimeStepList.size())
      throw string(ERROR_QTY_LESS_TIME_STEPS + convertInt(iSteps));
    if (iSteps < (int)vTimeStepList.size())
      throw string(ERRRO_QTY_MORE_TIME_STEPS + convertInt(iSteps));

    // Loop Through And Check For Duplicates
    foreach( CTimeStep *TimeStep, vTimeStepList) {
      if (TimeStep->getStep() > iSteps)
        errorGreaterThan(PARAM_STEP, PARAM_TIME_STEPS);

      mTimeStepList[TimeStep->getStep()] += 1;

      if (mTimeStepList[TimeStep->getStep()] > 1)
        throw string(ERROR_DUPLICATE_TIME_STEP + convertInt(TimeStep->getStep()));
    }

    // Loop through and check for Invalid/Missing Numbers
    for (int i = 0; i < iSteps; ++i) {
      if (mTimeStepList[i+1] == 0)
        throw string(ERROR_MISSING_TIME_STEP + convertInt(i+1));
    }

    // Now, Call TimeStep Validations
    foreach( CTimeStep *TimeStep, vTimeStepList) {
      TimeStep->validate();
    }

  } catch(string Ex) {
    Ex = "CTimeStepManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStepManager::build()
// Build out TimeSteps
//**********************************************************************
void CTimeStepManager::build() {
#ifndef OPTIMISE
  try {
#endif

    foreach(CTimeStep *TimeStep, vTimeStepList) {
      TimeStep->build();
    }

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CTimeStepManager.build()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CTimeStepManager::executeTimeSteps(int Step)
// Execute Our TimeSteps
//**********************************************************************
void CTimeStepManager::execute(int Year, int Step) {
#ifndef OPTIMISE
  try {
    if (Step > (int)vTimeStepList.size())
      throw string(ERROR_INVALID_TIME_STEP + convertInt(Step));
#endif
    iCurrentYear     = Year;
    iCurrentTimeStep = Step;

    // Execute
    vTimeStepList[(Step-1)]->execute();

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CTimeStepManager.executeTimeSteps()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CTimeStepManager::~CTimeStepManager()
// Default De-constructor
//**********************************************************************
CTimeStepManager::~CTimeStepManager() {
  // Delete Our Layers
  foreach( CTimeStep *TimeStep, vTimeStepList) {
    delete TimeStep;
  }

  // Clear Vector
  vTimeStepList.clear();
}
