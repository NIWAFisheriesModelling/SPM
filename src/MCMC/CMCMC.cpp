//============================================================================
// Name        : CMCMC.cpp
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Headers
#include <limits>
#include <numeric>
#include <boost/random.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include "CMCMC.h"
#include "../ObjectiveFunction/CObjectiveFunction.h"
#include "../Estimates/CEstimateManager.h"
#include "../RuntimeThread/CRuntimeThread.h"
#include "../Estimates/CEstimate.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../Minimizers/CMinimizer.h"
#include "../RandomNumberGenerator/CRandomNumberGenerator.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CComparer.h"
#include "../Helpers/CError.h"

// Namespaces
using namespace boost::numeric;

// Singleton Variable
CMCMC* CMCMC::clInstance = 0;

//**********************************************************************
// CMCMC::CMCMC()
// Default Constructor
//**********************************************************************
CMCMC::CMCMC() {

  pParameterList->registerAllowed(PARAM_TYPE);
  pParameterList->registerAllowed(PARAM_START);
  pParameterList->registerAllowed(PARAM_LENGTH);
  pParameterList->registerAllowed(PARAM_KEEP);
  pParameterList->registerAllowed(PARAM_MAX_CORRELATION);
  pParameterList->registerAllowed(PARAM_CORRELATION_ADJUSTMENT_METHOD);
  pParameterList->registerAllowed(PARAM_CORRELATION_ADJUSTMENT_DIFF);
  pParameterList->registerAllowed(PARAM_STEP_SIZE);
  pParameterList->registerAllowed(PARAM_PROPOSAL_DISTRIBUTION);
  pParameterList->registerAllowed(PARAM_DF);
}

//**********************************************************************
// CMCMC* CMCMC::Instance()
// Instance Method - Singleton
//**********************************************************************
CMCMC* CMCMC::Instance() {
  if (clInstance == 0)
    clInstance = new CMCMC();
  return clInstance;
}

//**********************************************************************
// void CMCMC::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CMCMC::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CMCMC::validate()
// Validate our MCMC
//**********************************************************************
void CMCMC::validate() {
  try {
    // Populate the variables from parameter list
    dStart                  = pParameterList->getDouble(PARAM_START, true, 0.0);
    iLength                 = pParameterList->getInt(PARAM_LENGTH);
    iKeep                   = pParameterList->getInt(PARAM_KEEP, true, 1);
    dMaxCorrelation         = pParameterList->getDouble(PARAM_MAX_CORRELATION, true, 0.8);
    sCorrelationMethod      = pParameterList->getString(PARAM_CORRELATION_ADJUSTMENT_METHOD, true, "correlation");
    dCorrelationDiff        = pParameterList->getDouble(PARAM_CORRELATION_ADJUSTMENT_DIFF, true, 0.0001);
    dStepSize               = pParameterList->getDouble(PARAM_STEP_SIZE, true, 0.0);
    sProposalDistribution   = pParameterList->getString(PARAM_PROPOSAL_DISTRIBUTION, true, "t");
    iDf                     = pParameterList->getInt(PARAM_DF, true, 4);

    // Validate the parameters
    if (iLength < 0)
      CError::errorLessThan(PARAM_LENGTH, PARAM_ZERO);
    if (iKeep < 0)
      CError::errorLessThan(PARAM_KEEP, PARAM_ZERO);
    if (sCorrelationMethod != "correlation" && sCorrelationMethod != "covariance")
      CError::errorUnknown(PARAM_CORRELATION_ADJUSTMENT_METHOD, sCorrelationMethod);
    if (sProposalDistribution != "t" && sProposalDistribution != "normal")
      CError::errorUnknown(PARAM_PROPOSAL_DISTRIBUTION, sProposalDistribution);
    if (dMaxCorrelation <= 0)
      CError::errorLessThan(PARAM_MAX_CORRELATION, PARAM_ZERO);
    if (dMaxCorrelation > 1)
      CError::errorGreaterThan(PARAM_MAX_CORRELATION, PARAM_ONE);

  } catch (string &Ex) {
    Ex = "CMCMC.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::build()
// Build our MCMC
//**********************************************************************
void CMCMC::build() {
  try {
    // Build a default step size if one doesn't exist. Leave this here
    // because we want to ensure the estimates have all been validated
    // before we get the enabled count.
    if (!pParameterList->hasParameter(PARAM_STEP_SIZE)) {
      int estimateCount = CEstimateManager::Instance()->getEnabledEstimateCount();
      dStepSize = 2.4 * pow( (double)estimateCount, -0.5);
    }

  } catch (string &Ex) {
    Ex = "CMCMC.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::execute()
// Execute our MCMC
//**********************************************************************
void CMCMC::execute() {
  try {
    dBestScore = std::numeric_limits<double>::max();

    // Build our choleskyDecomp of the Covariance
    if (!choleskyDecomposition())
      CError::error("Cholesky Decomposition failed");

    // Resize our vectors
    int iEstimateCount      = CEstimateManager::Instance()->getEnabledEstimateCount();
    vCandidates.resize(iEstimateCount);
    vMeans.resize(iEstimateCount);
    vMeans.assign(iEstimateCount, 0);

    for (int i = 0; i < iLength; ++i) {
      generateEstimates();

      for (int i = 0; i < iEstimateCount; ++i) {
        CEstimateManager::Instance()->getEnabledEstimate(i)->setValue(vCandidates[i]);
      }

      // Re-Run
      CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
      pThread->rebuild();
      pThread->startModel();

      // Workout our Objective Score
      CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();
      pObjectiveFunction->execute();

      double dRandom = CRandomNumberGenerator::Instance()->getRandomUniform_01();
      double dScore = pObjectiveFunction->getScore();
      if (dScore < dBestScore || dRandom < 0.3) {
        dBestScore = fmin(dBestScore, dScore);

        // Keep this entry for our chain
      }
    }

  } catch (string &Ex) {
   Ex = "CMCMC.execute()->" + Ex;
   throw Ex;
  }
}


//**********************************************************************
// bool CMCMC::generateEstimates()
// Generate some estimate values
//**********************************************************************
bool CMCMC::generateEstimates() {

  int iEstimateCount = CEstimateManager::Instance()->getEnabledEstimateCount();

  // generate the standard normal random numbers
  //fill_randn(s);

  for (int i = 0; i < iEstimateCount; ++i)
    vCandidates[i] *= mxCovarianceLT(i,i) + vMeans[i];

  return true;
}

//**********************************************************************
//
//
//**********************************************************************
bool CMCMC::choleskyDecomposition() {

  CMinimizer *pMinimizer = CMinimizerManager::Instance()->getMinimizer();
  ublas::matrix<double>& mxCovariance = pMinimizer->getCovarianceMatrix();

  int n = mxCovariance.size1();

  for (unsigned int i = 0; i < mxCovariance.size1(); ++i)
    for (unsigned int j = 0; j < mxCovariance.size2(); ++j)
      mxCovarianceLT(i,j) = 0.0;

  for (int i = 0; i < n; ++i)
    mxCovarianceLT(i, i) = 1.0;

  if (mxCovariance(0,0) < 0)
    return false;

  double dSum = 0.0;

  mxCovarianceLT(0,0) = sqrt(mxCovariance(0,0));
  for (int i = 1; i < n; ++i) {
    dSum = 0.0;

    for (int j = 0; j < i; ++j)
      dSum += mxCovarianceLT(i,j) * mxCovarianceLT(i,j);

    if (mxCovariance(i,i) <= dSum)
      return false;

    mxCovarianceLT(i,i) = sqrt(mxCovariance(i,i)-dSum);
    for (int j = i+1; j < n; ++j) {
      dSum = 0.0;
      for (int k = 0; k < i; ++k)
        dSum += mxCovarianceLT(j,k) * mxCovarianceLT(i,k);
      mxCovarianceLT(j,i) = (mxCovariance(j,i)-dSum)/mxCovarianceLT(i,i);
    }
  }

  dSum = 0.0;
  for (int i = 0; i < (n-1); ++i)
    dSum += mxCovarianceLT(n,i) * mxCovarianceLT(n,i);
  if (mxCovariance(n,n) <= dSum)
    return false;
  mxCovarianceLT(n,n) = sqrt(mxCovariance(n,n) - dSum);

  return true;
}

//**********************************************************************
// CMCMC::~CMCMC()
// Default De-Constructor
//**********************************************************************
CMCMC::~CMCMC() {
}
