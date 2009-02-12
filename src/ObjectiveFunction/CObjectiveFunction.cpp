//============================================================================
// Name        : CObjectiveFunction.cpp
// Author      : S.Rasmussen
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#include <iostream>
using std::cout;
using std::endl;

// Local Headers
#include "CObjectiveFunction.h"
#include "../Observations/CObservationManager.h"
#include "../Observations/CObservation.h"
#include "../Penalties/CPenaltyManager.h"
#include "../Estimates/CEstimateManager.h"
#include "../Estimates/CEstimate.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Single Static variable
boost::thread_specific_ptr<CObjectiveFunction> CObjectiveFunction::clInstance;

//**********************************************************************
// CObjectiveFunction::CObjectiveFunction()
// Default Constructor
//**********************************************************************
CObjectiveFunction::CObjectiveFunction() {

  // Variables
  sLabel = PARAM_OBJECTIVE;
  dScore = 0.0;
}

//**********************************************************************
// CObjectiveFunction* CObjectiveFunction::Instance()
// Instance Method - Singleton
//**********************************************************************
CObjectiveFunction* CObjectiveFunction::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CObjectiveFunction());
  return clInstance.get();
}

//**********************************************************************
// void CObjectiveFunction::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CObjectiveFunction::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// SScore* CObjectiveFunction::getScore(int Index)
// Get A Score From Our List
//**********************************************************************
SScore* CObjectiveFunction::getScore(int Index) {
#ifndef OPTIMIZE
  try {
    // Validate
    if (Index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (Index >= (int)vScoreList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_SCORES_INDEX);
#endif

    return &vScoreList[Index];

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CObjectiveFunction.getScore()->" + Ex;
    throw Ex;
  }

  return 0;
#endif
}

//**********************************************************************
// void CObjectiveFunction::addScore(string Label, double Value)
// Add a score to our Vector
//**********************************************************************
void CObjectiveFunction::addScore(string Label, double Value) {
  // Create Structure
  SScore stScore;
  stScore.Label = Label;
  stScore.Score = Value;

  // Push into vector
  vScoreList.push_back(stScore);
}

//**********************************************************************
// void CObjectiveFunction::build()
// Build our Objective Function
//**********************************************************************
void CObjectiveFunction::build() {
  try {
    throw string(ERROR_SUPPORTED_FUNCTION);

  } catch (string Ex) {
    Ex = "CObjectiveFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObjectiveFunction::execute()
// Execute our Object Function
//**********************************************************************
void CObjectiveFunction::execute() {

  // Variables
  CObservationManager   *pObservationManager  = CObservationManager::Instance();
  CPenaltyManager       *pPenaltyManager      = CPenaltyManager::Instance();
  CEstimateManager      *pEstimateManager     = CEstimateManager::Instance();
                        dScore                = 0;
                        vScoreList.clear();
  string                sLabel;
  double                dValue;

  // Loop Through Observations
  int iCount = pObservationManager->getObservationCount();
  for (int i = 0; i < iCount; ++i) {
   CObservation *pObservation = pObservationManager->getObservation(i);

   // Get Vars
   sLabel = PARAM_OBS + string("->") + pObservation->getLabel();
   dValue = pObservation->getScore();

   // Increment Score, and Add Value to Vector
   dScore += dValue;
   addScore(sLabel, dValue);

  }

  // Loop Through Penalties
  iCount = pPenaltyManager->getFlaggedPenaltyCount();
  for (int i = 0; i < iCount; ++i) {
    SFlaggedPenalty *pPenalty = pPenaltyManager->getFlaggedPenalty(i);

    // Get Vars
    sLabel = PARAM_PENALTY + string("->") + pPenalty->Label;
    dValue = pPenalty->Score;

    // Inc Score, Add Value to Vector
    dScore += dValue;
    addScore(sLabel, dValue);

  }

  // Loop Through Priors
  iCount = pEstimateManager->getEstimateCount();
  for (int i = 0; i < iCount; ++i) {
    CEstimate *pEstimate = pEstimateManager->getEstimate(i);

    // Check if we are using a prior on this estimate
    if (pEstimate->getPrior() == "")
      continue;

    // Get Vars
    sLabel = PARAM_PRIOR + string("->") + pEstimate->getParameter();
    dValue = pEstimate->getPriorScore();

    // Inc Score, Add Value to vector
    dScore += dValue;
    addScore(sLabel, dValue);

  }
}

//**********************************************************************
// CObjectiveFunction::~CObjectiveFunction()
// Default De-Constructor
//**********************************************************************
CObjectiveFunction::~CObjectiveFunction() {
}
