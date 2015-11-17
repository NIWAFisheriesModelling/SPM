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
#include <iostream>
#include <boost/random.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include "CMCMC.h"
#include "../Estimates/CEstimate.h"
#include "../Estimates/CEstimateManager.h"
#include "../Helpers/CComparer.h"
#include "../Helpers/CError.h"
#include "../Helpers/CMath.h"
#include "../Helpers/ForEach.h"
#include "../Minimizers/CMinimizer.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../ObjectiveFunction/CObjectiveFunction.h"
#include "../RandomNumberGenerator/CRandomNumberGenerator.h"
#include "../Reports/CReportManager.h"
#include "../RuntimeThread/CRuntimeThread.h"

// Namespaces
using namespace boost::numeric;
using std::cout;
using std::endl;

// Singleton Variable
CMCMC* CMCMC::clInstance = 0;

//**********************************************************************
// CMCMC::CMCMC()
// Default Constructor
//**********************************************************************
CMCMC::CMCMC() {
  // default variables
  iJumps = 0;
  iSuccessfulJumps = 0;
  iJumpsSinceAdapt = 0;
  iSuccessfulJumpsSinceAdapt = 0;
  dStepSize = 0.0;
  bLastItem = false;
  dAcceptanceRatio = 0.24;

  pParameterList->registerAllowed(PARAM_TYPE);
  pParameterList->registerAllowed(PARAM_START);
  pParameterList->registerAllowed(PARAM_LENGTH);
  pParameterList->registerAllowed(PARAM_KEEP);
  pParameterList->registerAllowed(PARAM_MAX_CORRELATION);
  pParameterList->registerAllowed(PARAM_COVARIANCE_ADJUSTMENT_METHOD);
  pParameterList->registerAllowed(PARAM_CORRELATION_ADJUSTMENT_DIFF);
  pParameterList->registerAllowed(PARAM_STEPSIZE);
  pParameterList->registerAllowed(PARAM_PROPOSAL_DISTRIBUTION);
  pParameterList->registerAllowed(PARAM_DF);
  pParameterList->registerAllowed(PARAM_ADAPT_STEPSIZE_AT);
  pParameterList->registerAllowed(PARAM_ACCEPTANCE_RATIO);
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

    pParameterList->checkInvalidParameters();

    // Populate the variables from parameter list
    sType                   = pParameterList->getString(PARAM_TYPE, true, PARAM_METROPOLIS_HASTINGS);
    dStart                  = pParameterList->getDouble(PARAM_START, true, 0.0);
    iLength                 = pParameterList->getInt(PARAM_LENGTH);
    iKeep                   = pParameterList->getInt(PARAM_KEEP, true, 1);
    dMaxCorrelation         = pParameterList->getDouble(PARAM_MAX_CORRELATION, true, 0.8);
    sCorrelationMethod      = pParameterList->getString(PARAM_COVARIANCE_ADJUSTMENT_METHOD, true, PARAM_COVARIANCE);
    dCorrelationDiff        = pParameterList->getDouble(PARAM_CORRELATION_ADJUSTMENT_DIFF, true, 0.0001);
    dStepSize               = pParameterList->getDouble(PARAM_STEPSIZE, true, 0.0);
    sProposalDistribution   = pParameterList->getString(PARAM_PROPOSAL_DISTRIBUTION, true, PARAM_T);
    iDF                     = pParameterList->getInt(PARAM_DF, true, 4);
    dAcceptanceRatio        = pParameterList->getDouble(PARAM_STEPSIZE, true, 0.24);
    dInverseAcceptanceRatio = 1.0/dAcceptanceRatio;

    // Validate the parameters
    if (sType != PARAM_METROPOLIS_HASTINGS)
      CError::errorNotEqual(PARAM_TYPE, PARAM_METROPOLIS_HASTINGS);
    if (iLength < 1)
      CError::errorLessThan(PARAM_LENGTH, PARAM_ONE);
    if (iKeep < 0)
      CError::errorLessThan(PARAM_KEEP, PARAM_ZERO);
    if (sCorrelationMethod != PARAM_CORRELATION && sCorrelationMethod != PARAM_COVARIANCE && sCorrelationMethod != PARAM_NONE)
      CError::errorUnknown(PARAM_COVARIANCE_ADJUSTMENT_METHOD, sCorrelationMethod);
    if (sProposalDistribution != PARAM_T && sProposalDistribution != PARAM_NORMAL)
      CError::errorUnknown(PARAM_PROPOSAL_DISTRIBUTION, sProposalDistribution);
    if (dMaxCorrelation <= 0)
      CError::errorLessThan(PARAM_MAX_CORRELATION, PARAM_ZERO);
    if (dMaxCorrelation > 1)
      CError::errorGreaterThan(PARAM_MAX_CORRELATION, PARAM_ONE);
    if (iDF <= 0)
      CError::errorLessThan(PARAM_DF, PARAM_ZERO);
    if (dStart < 0.0)
      CError::errorLessThan(PARAM_START, PARAM_ZERO);
    if (dStepSize < 0)
      CError::errorLessThan(PARAM_STEPSIZE, PARAM_ZERO);
    if (pParameterList->hasParameter(PARAM_ADAPT_STEPSIZE_AT)) {
      pParameterList->fillVector(vAdaptStepSize, PARAM_ADAPT_STEPSIZE_AT);
      for(int i = 0; i < (int)vAdaptStepSize.size(); ++i) {
        if (vAdaptStepSize[i] < 1)
          CError::errorLessThan(PARAM_ADAPT_STEPSIZE_AT, PARAM_ONE);
        if (vAdaptStepSize[i] > iLength )
          CError::errorGreaterThan(PARAM_ADAPT_STEPSIZE_AT, PARAM_LENGTH);
      }
    } else {
      vAdaptStepSize.resize(1);
      vAdaptStepSize[0] = 1;
    }

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

    // Link to our minimiser
    pMinimizer = CMinimizerManager::Instance()->getMinimizer();

    // Get the names of our parameters
    vector<CEstimate*> vEstimates;
    CEstimateManager::Instance()->fillVector(vEstimates);
    foreach(CEstimate *Estimate, vEstimates) {
      vEstimateNames.push_back(Estimate->getParameter());
    }

    // Build default stepsize
    iEstimateCount = CEstimateManager::Instance()->getEnabledEstimateCount();

    int iIgnorableEstimates = 0;
    for(int i = 0; i < iEstimateCount; ++i) {
      CEstimate *estimate = CEstimateManager::Instance()->getEnabledEstimate(i);
      if ( (estimate->getLowerBound() == estimate->getUpperBound()) || estimate->getMCMCFixed() )
        iIgnorableEstimates++;
    }
    if ((iEstimateCount - iIgnorableEstimates) < 1)
      CError::error("The number of estimated parameters must be at least one");

    if (!pParameterList->hasParameter(PARAM_STEPSIZE) || dStepSize==0.0 ) {
      dStepSize = 2.4 * pow( (double)(iEstimateCount-iIgnorableEstimates), -0.5);
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

    // Setup initial candidate vector
    vCandidates.resize(iEstimateCount);
    vbIsEnabledEstimate.resize(iEstimateCount);

    for(int i=0; i < iEstimateCount; ++i) {
      CEstimate *estimate = CEstimateManager::Instance()->getEnabledEstimate(i);
      vCandidates[i] = estimate->getValue();
      if ( (estimate->getLowerBound() == estimate->getUpperBound()) || estimate->getMCMCFixed() )
        vbIsEnabledEstimate[i] = false;
      else
        vbIsEnabledEstimate[i] = true;
    }

    // Build initial covariance matrix
    buildCovarianceMatrix();

    // Create Cholskey decomposition from covariance matrix
    if ( !choleskyDecomposition() )
      THROW_EXCEPTION("Cholskey decomposition failed")

    // Get MCMC starting values
    if (dStart > 0.0 ) {
      generateRandomStart();
    }
    // reset our values
    for (int i = 0; i < iEstimateCount; ++i) {
      CEstimateManager::Instance()->getEnabledEstimate(i)->setValue(vCandidates[i]);
    }

    // Get the initial objective function value
    CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
    pThread->rebuild();
    pThread->startModel();

    // Workout our objective function value
    CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();
    pObjectiveFunction->execute();
    double dScore = pObjectiveFunction->getScore();
    // Keep the location as the first point in our chain
    {
      SChainItem newItem;
      newItem.iIteration                = 0;
      newItem.dPenalty                  = pObjectiveFunction->getPenalties();
      newItem.dScore                    = pObjectiveFunction->getScore();
      newItem.dPrior                    = pObjectiveFunction->getPriors();
      newItem.dLikelihood               = pObjectiveFunction->getLikelihoods();;
      newItem.dAcceptanceRate           = 0;
      newItem.dAcceptanceRateSinceAdapt = 0;
      newItem.dStepSize                 = dStepSize;
      newItem.vValues                   = vCandidates;
      vChain.push_back(newItem);
    }

    //===============================================================
    // Now, do our MCMC
    //===============================================================
    // Iterate over length of MCMC
    do {

      if(!(pConfig->getQuietMode())) {
        std::cerr << "." ;
      }

      // Generate a candidate value
      vector<double> vOldCandidates = vCandidates;
      updateStepSize(iJumps);
      generateNewCandidate();
      for (int j = 0; j < iEstimateCount; ++j) {
        CEstimateManager::Instance()->getEnabledEstimate(j)->setValue(vCandidates[j]);
      }

      // Run model with these parameters to get objective function score
      CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
      pThread->rebuild();
      pThread->startModel();
      // Workout our Objective Score
      CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();
      pObjectiveFunction->execute();

      // Preserve our score for later
      double dOldScore = dScore;
      dScore = pObjectiveFunction->getScore();
      double dRatio = 1.0;

      // Evaluate if the old value was better, and decide whether to jump
      if (dScore > dOldScore) {
        dRatio = exp(-dScore + dOldScore);
      }
      if (dRatio==1.0 || CRandomNumberGenerator::Instance()->getRandomUniform_01() < dRatio) {
        // accept the proposed candidate point
        iJumps++;
        iJumpsSinceAdapt++;
        iSuccessfulJumps++;
        iSuccessfulJumpsSinceAdapt++;
        // keep the score, and its component parts
        if ( ((iJumps) % iKeep) == 0) {
          newItem.iIteration                = iJumps;
          newItem.dPenalty                  = pObjectiveFunction->getPenalties();
          newItem.dScore                    = pObjectiveFunction->getScore();
          newItem.dPrior                    = pObjectiveFunction->getPriors();
          newItem.dLikelihood               = pObjectiveFunction->getLikelihoods();
          newItem.dAcceptanceRateSinceAdapt = (double)iSuccessfulJumpsSinceAdapt / (double)iJumpsSinceAdapt;
          newItem.dAcceptanceRate           = (double)iSuccessfulJumps / (double)(iJumps);
          newItem.dStepSize                 = dStepSize;
          newItem.vValues                   = vCandidates;
          vChain.push_back(newItem);
          if ( iSuccessfulJumps >= iLength ) {
            bLastItem = true;
          }
          CReportManager::Instance()->execute(STATE_ITERATION_COMPLETE);
        }

      } else {
        // reject the new proposed candidate point and use the point from the previous iteration
        iJumps++;
        iJumpsSinceAdapt++;
        dScore = dOldScore;
        vCandidates = vOldCandidates;
        newItem.iIteration                = iJumps;
        newItem.dPenalty                  = vChain[vChain.size()-1].dPenalty;
        newItem.dScore                    = vChain[vChain.size()-1].dScore;
        newItem.dPrior                    = vChain[vChain.size()-1].dPrior;
        newItem.dLikelihood               = vChain[vChain.size()-1].dLikelihood;
        newItem.dAcceptanceRateSinceAdapt = (double)iSuccessfulJumpsSinceAdapt / (double)iJumpsSinceAdapt;
        newItem.dAcceptanceRate           = (double)iSuccessfulJumps / (double)(iJumps);
        newItem.dStepSize                 = dStepSize;
        newItem.vValues                   = vCandidates;
        vChain.push_back(newItem);
      }

    } while (iJumps < iLength);

    if(!(pConfig->getQuietMode())) {
      std::cerr << "\n" ;
    }

  } catch (string &Ex) {
    Ex = "CMCMC.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::generateRandomStart()
// generateRandomStart for our MCMC
//**********************************************************************
void CMCMC::generateRandomStart() {
  try {

    vector<double> vOldCandidates = vCandidates;

    int iAttempts = 0;
    bool bCandidatesOk;

    // Sanity check
    if ((int)vCandidates.size() != iEstimateCount)
      THROW_EXCEPTION("INTERNAL ERROR: Check candidate vector size d")

    do {
      bCandidatesOk = true;

      iAttempts++;
      if (iAttempts >= 1000)
        CError::errorEqualTo("MCMC start candidate attempts", "1000");
      // reset candidates
      vCandidates = vOldCandidates;

      //Generate candidates
      fillMultivariateNormal(dStart);

      // Check bounds and regenerate candidates if they are not within the bounds.
      for (int i = 0; i < iEstimateCount; ++i) {
        CEstimate *estimate = CEstimateManager::Instance()->getEnabledEstimate(i);

        if (estimate->getLowerBound() > vCandidates[i] || estimate->getUpperBound() < vCandidates[i]) {
          // try again
          bCandidatesOk = false;
          break;
        }
      }
    } while (!bCandidatesOk);

  } catch (string &Ex) {
    Ex = "CMCMC.generateRandomStart()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::generateEstimates()
// Generate our new candidate estimates
//**********************************************************************
void CMCMC::generateNewCandidate() {

  try {

    vector<double> vOldCandidates = vCandidates;

    int iAttempts = 0;
    bool bCandidatesOk;

    do {
      bCandidatesOk = true;

      iAttempts++;
      if (iAttempts >= 10000)
        CError::errorGreaterThanEqualTo("MCMC candidate attempts", "10000");

      if (sProposalDistribution == PARAM_NORMAL)
        fillMultivariateNormal(dStepSize);
      else if (sProposalDistribution == PARAM_T)
        fillMultivariatet(dStepSize);

      // Check bounds and regenerate candidates if they are not within the bounds.
      for (int i = 0; i < iEstimateCount; ++i) {
        CEstimate *pEstimate = CEstimateManager::Instance()->getEnabledEstimate(i);
        if (pEstimate->getLowerBound() > vCandidates[i] || pEstimate->getUpperBound() < vCandidates[i]) {
          // reset candidates and try again
          bCandidatesOk = false;
          vCandidates = vOldCandidates;
          break;
        }
      }

    } while (!bCandidatesOk);

  } catch (string &Ex) {
    Ex = "CMCMC.generateEstimates()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::updateStepSize(int iIteration)
// Ypdate stepsize if required
//**********************************************************************
void CMCMC::updateStepSize(int iIteration) {

  if( (iJumpsSinceAdapt > 0) && (iSuccessfulJumpsSinceAdapt > 0) ) {
    for(int i = 0; i < (int)vAdaptStepSize.size(); ++i) {
      if( iIteration == vAdaptStepSize[i] ) {
        // modify the stepsize by the ratio = AcceptanceRate / 0.24
        dStepSize *= ((double)iSuccessfulJumpsSinceAdapt / (double)iJumpsSinceAdapt) * dInverseAcceptanceRatio;
        // Ensure the stepsize remains positive
        dStepSize = CMath::zeroFun(dStepSize, 1e-10);
        // reset counters
        iJumpsSinceAdapt = 0;
        iSuccessfulJumpsSinceAdapt = 0;
        break;
      }
    }
  }

}

//**********************************************************************
// void CMCMC::buildCovarianceMatrix()
// build our Covariance Matrix
//**********************************************************************
void CMCMC::buildCovarianceMatrix() {
  try {

    // Obtain the covariance matrix to use for the proposal distribution
    mxOriginalCovariance = pMinimizer->getCovarianceMatrix();
    mxCovariance = mxOriginalCovariance;

    if ( sCorrelationMethod == PARAM_NONE )
      return;

    // Adjust the covariance matrix for the proposal distribution
    for (int i=0; i < (int)mxCovariance.size1(); ++i) {
      for (int j=i+1; j < (int)mxCovariance.size2(); ++j) {
        if (mxCovariance(i,j) / sqrt(mxCovariance(i,i) * mxCovariance(j,j)) > dMaxCorrelation) {
          mxCovariance(i,j) = dMaxCorrelation * sqrt(mxCovariance(i,i) * mxCovariance(j,j));
        }
        if (mxCovariance(i,j) / sqrt(mxCovariance(i,i) * mxCovariance(j,j)) < -dMaxCorrelation){
          mxCovariance(i,j) = -dMaxCorrelation * sqrt(mxCovariance(i,i) * mxCovariance(j,j));
        }
      }
    }

    // Adjust any nonzero variances less than min_diff * the difference between the bounds on the parameter.
    // Obtain the estimation bounds to use to modify the covariance matrix
    vector<double> vDiffBounds;
    for (int i = 0; i < CEstimateManager::Instance()->getEnabledEstimateCount(); ++i) {
      CEstimate *estimate = CEstimateManager::Instance()->getEnabledEstimate(i);
      vDiffBounds.push_back( estimate->getUpperBound() - estimate->getLowerBound() );
    }

    for (int i=0; i < (int)mxCovariance.size1(); ++i) {
      if (mxCovariance(i,i) < (dCorrelationDiff * vDiffBounds[i]) && mxCovariance(i,i) != 0) {
        if (sCorrelationMethod == PARAM_COVARIANCE) {
          double dMultiplyCovariance = (sqrt(dCorrelationDiff) * vDiffBounds[i]) / sqrt(mxCovariance(i,i));
          for (int j=0 ; j < (int)mxCovariance.size1(); ++j) {
            mxCovariance(i,j) = mxCovariance(i,j) * dMultiplyCovariance;
            mxCovariance(j,i) = mxCovariance(j,i) * dMultiplyCovariance;
          }
        } else if(sCorrelationMethod == PARAM_CORRELATION) {
          mxCovariance(i,i) = dCorrelationDiff * vDiffBounds[i];
        }
      }
    }

  } catch (string &Ex) {
    Ex = "CMCMC.buildCovarianceMatrix()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMC:fillMultivariateNormal(double stepsize)
//
//**********************************************************************
void CMCMC::fillMultivariateNormal(double stepsize) {

  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  vector<double>  vRandomNormals(iEstimateCount,0);
  for ( int i = 0; i < iEstimateCount; ++i) {
    vRandomNormals[i] = pRandom->getRandomStandardNormal();
  }
  for ( int i = 0; i < iEstimateCount; ++i) {
    double dRowSum = 0.0;
    for (int j = 0; j < iEstimateCount; ++j ) {
      dRowSum += mxCovarianceLT(i,j) * vRandomNormals[j];
    }
    if (vbIsEnabledEstimate[i])
      vCandidates[i] += dRowSum * stepsize;
  }
}

//**********************************************************************
// CMCMC:fillMultivariatet()
//
//**********************************************************************
void CMCMC::fillMultivariatet(double stepsize) {

  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();
  vector<double>  vRandomNormals(iEstimateCount,0);
  vector<double>  vRandomChiSquare(iEstimateCount,0);
  for ( int i = 0; i < iEstimateCount; ++i) {
    vRandomNormals[i] = pRandom->getRandomStandardNormal();
    vRandomChiSquare[i] = 1 / ( pRandom->getRandomChiSquare(iDF) / iDF );
  }
  for ( int i = 0; i < iEstimateCount; ++i) {
    double dRowSum = 0.0;
    for (int j = 0; j < iEstimateCount; ++j ) {
      dRowSum += mxCovarianceLT(i,j) * vRandomNormals[j] * vRandomChiSquare[j];
    }
    if (vbIsEnabledEstimate[i])
      vCandidates[i] += dRowSum * stepsize;
  }
}

//**********************************************************************
// bool CMCMC::choleskyDecomposition()
//
//**********************************************************************
bool CMCMC::choleskyDecomposition() {

//SCOTT todo: We also have similar functionality in FMM::CholeskyDecomposition()
//            Can we put them _both_ in the same place...with the same function call interface
//            As they both use a slightly different algorithms, it might be useful to compare their output.

  //sanity check
  if (mxCovariance.size1() != mxCovariance.size2() )
    THROW_EXCEPTION("Invalid covariance matrix (size1!=size2)");

  int iN = mxCovariance.size1();
  mxCovarianceLT = mxCovariance;

  for (int i = 0; i < iN; ++i) {
    for (int j = 0; j < iN; ++j) {
      mxCovarianceLT(i,j) = 0.0;
    }
  }

  for (int i = 0; i < iN; ++i) {
    mxCovarianceLT(i,i) = 1.0;
  }

  if (mxCovariance(0,0) < 0)
    return false;

  double dSum = 0.0;

  mxCovarianceLT(0,0) = sqrt(mxCovariance(0,0));

  for (int i = 1; i < iN; ++i)
    mxCovarianceLT(i,0) = mxCovariance(i,0)/mxCovarianceLT(0,0);

  for (int i = 1; i < iN; ++i) {
    dSum = 0.0;
    for (int j = 0; j < i; ++j)
      dSum += mxCovarianceLT(i,j) * mxCovarianceLT(i,j);

    if (mxCovariance(i,i) <= dSum)
      return false;

    mxCovarianceLT(i,i) = sqrt(mxCovariance(i,i)-dSum);
    for (int j = i+1; j < iN; ++j) {
      dSum = 0.0;
      for (int k = 0; k < i; ++k)
        dSum += mxCovarianceLT(j,k) * mxCovarianceLT(i,k);
      mxCovarianceLT(j,i) = (mxCovariance(j,i)-dSum)/mxCovarianceLT(i,i);
    }
  }

  dSum = 0.0;
  for (int i = 0; i < (iN-1); ++i)
    dSum += mxCovarianceLT(iN-1,i) * mxCovarianceLT(iN-1,i);
  if (mxCovariance(iN-1,iN-1) <= dSum)
    return false;
  mxCovarianceLT(iN-1,iN-1) = sqrt(mxCovariance(iN-1,iN-1) - dSum);

  return true;
}

//**********************************************************************
// CMCMC::~CMCMC()
// Default De-Constructor
//**********************************************************************
CMCMC::~CMCMC() {
}



