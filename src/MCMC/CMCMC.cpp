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
#include "../Helpers/CMath.h"

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
  iAcceptedJumps = 0;
  iSuccessfulJumps = 0;
  iJumps = 0;

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
  pParameterList->registerAllowed(PARAM_ADAPT_STEPSIZE_AT);
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
    sCorrelationMethod      = pParameterList->getString(PARAM_CORRELATION_ADJUSTMENT_METHOD, true, PARAM_COVARIANCE);
    dCorrelationDiff        = pParameterList->getDouble(PARAM_CORRELATION_ADJUSTMENT_DIFF, true, 0.0001);
    dStepSize               = pParameterList->getDouble(PARAM_STEP_SIZE, true, 0.0);
    sProposalDistribution   = pParameterList->getString(PARAM_PROPOSAL_DISTRIBUTION, true, PARAM_T);
    iDF                     = pParameterList->getInt(PARAM_DF, true, 4);

    if (pParameterList->hasParameter(PARAM_ADAPT_STEPSIZE_AT)) {
      pParameterList->fillVector(vAdaptStepSize, PARAM_ADAPT_STEPSIZE_AT);
    } else {
      vAdaptStepSize.resize(1);
      vAdaptStepSize[0] = 1;
    }

    // Validate the parameters
    if (iLength < 1)
      CError::errorLessThan(PARAM_LENGTH, PARAM_ONE);
    if (iKeep < 0)
      CError::errorLessThan(PARAM_KEEP, PARAM_ZERO);
    if (sCorrelationMethod != PARAM_CORRELATION && sCorrelationMethod != PARAM_COVARIANCE)
      CError::errorUnknown(PARAM_CORRELATION_ADJUSTMENT_METHOD, sCorrelationMethod);
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
    for(int i = 0; i < (int)vAdaptStepSize.size(); ++i) {
      if (vAdaptStepSize[i] < 1)
        CError::errorLessThan(PARAM_ADAPT_STEPSIZE_AT, PARAM_ONE);
      if (vAdaptStepSize[i] > iLength )
        CError::errorGreaterThan(PARAM_ADAPT_STEPSIZE_AT, PARAM_LENGTH);
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

    // Build default step size
    iEstimateCount = CEstimateManager::Instance()->getEnabledEstimateCount();
    if (!pParameterList->hasParameter(PARAM_STEP_SIZE)) {
      dStepSize = 2.4 * pow( (double)iEstimateCount, -0.5);
    } else if ( dStepSize==0.0 ) {
      dStepSize = 2.4 * pow( (double)iEstimateCount, -0.5);
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

    // Build initial covariance matrix
    buildCovarianceMatrix();

    // Setup initial candidate vector
    vCandidates.resize(iEstimateCount);

    for(int i=0; i < iEstimateCount; ++i) {
      vCandidates[i] = CEstimateManager::Instance()->getEnabledEstimate(i)->getValue();
    }

    // Get MCMC starting values
    if (dStart > 0.0 ) {
      generateRandomStart();
    }
    for (int i = 0; i < iEstimateCount; ++i) {
      CEstimateManager::Instance()->getEnabledEstimate(i)->setValue(vCandidates[i]);
    }

    // Get the initial objective function value -> we need to set the value of the estimates here calculated in the lines above
    CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
    pThread->rebuild();
    pThread->startModel();

    // Workout our objective function value
    CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();
    pObjectiveFunction->execute();
    double dScore = pObjectiveFunction->getScore();

    // Create Cholskey decomposition for new candidates
    if ( !choleskyDecomposition() )
      THROW_EXCEPTION("Cholskey decomposition failed")

    //===============================================================
    // Now, do our MCMC
    //===============================================================
    // Iterate over length of MCMC
    for (int i =0; i < iLength; ++i) {
    // Generate a candidate value
      vector<double> vOldCandidates = vCandidates;
      updateStepSize(i);
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
      if (dScore < dOldScore) {
        dRatio = exp(dOldScore - dScore);
      }
      if (CRandomNumberGenerator::Instance()->getRandomUniform_01() < dRatio) {
        // accept the candidate point
        // keep the score, and its compontent parts
        if ( ((i+1) % iKeep) == 0) {
          SChainItem newItem;
          newItem.iIteration      = i+1;
          newItem.dPenalty        = pObjectiveFunction->getPenalties();
          newItem.dScore          = pObjectiveFunction->getScore();
          newItem.dPrior          = pObjectiveFunction->getPriors();
          newItem.dLikelihood     = pObjectiveFunction->getLikelihoods();;
          newItem.dAcceptanceRate = (double)iAcceptedJumps / (double)(i+1);
          newItem.dStepSize       = dStepSize;
          newItem.vValues         = vCandidates;

          vChain.push_back(newItem);
        }

        iJumps++;
        iSuccessfulJumps++;
        iAcceptedJumps++;
      } else {
        // reject the candidate point and reset our Candidate back to what they were
        dScore = dOldScore;
        vCandidates = vOldCandidates;
        iJumps++;
      }
    }

std::cerr<< "MCMC output:\n";
for(int i=0; i<(int)vChain.size(); ++i) {
  std::cerr << vChain[i].iIteration << " " << vChain[i].dScore << " " << vChain[i].dPenalty << " " << vChain[i].dPrior  << " " << vChain[i].dLikelihood << " " << vChain[i].dAcceptanceRate << " " << vChain[i].dStepSize << " : ";
  for(int j=0; j<iEstimateCount; ++j) {
    std:: cerr << vChain[i].vValues[j] << " ";
  }
  std::cerr << "\n";
}
std::cerr << "\n\n";



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

    fillMultivariateNormal(dStart);

    int iAttempts = 0;
    bool bCandidatesOk;
    int iEnabledEstimateCount = CEstimateManager::Instance()->getEnabledEstimateCount();

    // Sanity check
    if ((int)vCandidates.size() != iEnabledEstimateCount)
      THROW_EXCEPTION("Candidate vector size d")

    do {
      bCandidatesOk = true;

      iAttempts++;
      if (iAttempts >= 1000)
        CError::errorEqualTo("MCMC start candidate attempts", "1000");
      vCandidates = vOldCandidates;
      fillMultivariateNormal(dStart);

      // Check bounds and regenerate candidates if
      // they are not within the bounds.
      for (int i = 0; i < iEnabledEstimateCount; ++i) {
        CEstimate *estimate = CEstimateManager::Instance()->getEnabledEstimate(i);
        if (estimate->getLowerBound() > vCandidates[i] || estimate->getUpperBound() < vCandidates[i]) {
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
    int iEnabledEstimateCount = CEstimateManager::Instance()->getEnabledEstimateCount();

    do {
      bCandidatesOk = true;

      iAttempts++;
      if (iAttempts >= 1000)
        CError::errorEqualTo("MCMC candidate attempts", "1000");

      if (sProposalDistribution == PARAM_NORMAL)
        fillMultivariateNormal(dStepSize);
      else if (sProposalDistribution == PARAM_T)
        fillMultivariatet(dStepSize);

      // Check bounds and regenerate candidates if
      // they are not within the bounds.
      for (int i = 0; i < iEnabledEstimateCount; ++i) {
        CEstimate *pEstimate = CEstimateManager::Instance()->getEnabledEstimate(i);
        if (pEstimate->getLowerBound() > vCandidates[i] || pEstimate->getUpperBound() < vCandidates[i]) {
          bCandidatesOk = false;
          // reset candidates and try again
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


  if(iJumps > 0) {
    for(int i = 0; i < (int)vAdaptStepSize.size(); ++i) {
      if(vAdaptStepSize[i] == iIteration ) {
        double dAcceptanceRate = (double)iSuccessfulJumps / (double)iJumps ;
        if (dAcceptanceRate > 0.5) {
          dStepSize *= 2;
          iSuccessfulJumps = 0;
          iJumps = 0;
          break;
        } else if (dAcceptanceRate < 0.2) {
          dStepSize /= 2;
          iSuccessfulJumps = 0;
          iJumps = 0;
          break;
        }
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
    mxCovariance = pMinimizer->getCovarianceMatrix();

    // Adjust the covariance matrix for the proposal distribution
    for (int i=0; i < (int)mxCovariance.size1(); ++i) {
      for (int j=i+1; j < (int)mxCovariance.size2(); ++j) {
        if (mxCovariance(i,j) / sqrt(mxCovariance(i,j) * mxCovariance(j,j)) > dMaxCorrelation) {
          mxCovariance(i,j) = dMaxCorrelation * sqrt(mxCovariance(i,i) * mxCovariance(j,j));
          mxCovariance(j,i) = mxCovariance(i,j);
        }
        if (mxCovariance(i,j) / sqrt(mxCovariance(i,i) * mxCovariance(j,j)) < -dMaxCorrelation){
          mxCovariance(i,j) = -dMaxCorrelation * sqrt(mxCovariance(i,i) * mxCovariance(j,j));
          mxCovariance(j,i) = mxCovariance(i,j);
        }
      }
    }

    // Adjust any nonzero variances less than min_diff x the difference between the bounds on the parameter.
    // Obtain the estimation bounds to use to modify the covariance matrix
    vector<double> vDiffBounds;
    for (int i = 0; i < CEstimateManager::Instance()->getEnabledEstimateCount(); ++i) {
      CEstimate *estimate = CEstimateManager::Instance()->getEnabledEstimate(i);
      vDiffBounds.push_back( estimate->getUpperBound() - estimate->getLowerBound() );
    }

    for (int i=0; i < (int)mxCovariance.size1(); ++i) {
      if (mxCovariance(i,i) < dCorrelationDiff * vDiffBounds[i] && mxCovariance(i,i) != 0) {
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

/*  // set zero variances to 1 as above
  ublas::matrix<double>  mxTemp = mxCovariance;
  vector<bool> bHasZeroVariances;
  bHasZeroVariances.resize(mxTemp.size1());
  for ( int i = 0; i <= (int)mxTemp.size1(); ++i ) {
    if ( mxTemp(i,i) == 0.0 ) {
      mxTemp(i,i) = 1.0;
      bHasZeroVariances[i] = true;
    } else{
      bHasZeroVariances[i] = false;
    }
  }
*/

  vector<double>  vRandomNormals(iEstimateCount,0);
  for ( int i = 0; i < iEstimateCount; ++i) {
    vRandomNormals[i] = pRandom->getRandomStandardNormal();
  }
  for ( int i = 0; i < iEstimateCount; ++i) {
    double dRowSum = 0.0;
    for (int j = 0; j < iEstimateCount; ++j ) {
      dRowSum += mxCovarianceLT(i,j) * vRandomNormals[j];
    }
    vCandidates[i] += dRowSum * stepsize;
  }

  // find the elements with 0 variances and set them to their means
//  for (int i=covar.rowmin(); i<=covar.rowmax(); i++){
//    if (zero_variances[i]){
//      (*this)[i] = mean[i];
//    }
//  }

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
    vCandidates[i] += dRowSum * stepsize;
  }

}

//**********************************************************************
// bool CMCMC::choleskyDecomposition()
//
//**********************************************************************
bool CMCMC::choleskyDecomposition() {

  //sanity check
  if (mxCovariance.size1() != mxCovariance.size2() )
    THROW_EXCEPTION("Invalid covariance matrix (size1!=size2)");

  int n = mxCovariance.size1();
  mxCovarianceLT = mxCovariance;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      mxCovarianceLT(i,j) = 0.0;
    }
  }

  for (int i = 0; i < n; ++i)
    mxCovarianceLT(i,i) = 1.0;

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
    dSum += mxCovarianceLT(n-1,i) * mxCovarianceLT(n-1,i);
  if (mxCovariance(n-1,n-1) <= dSum)
    return false;
  mxCovarianceLT(n-1,n-1) = sqrt(mxCovariance(n-1,n-1) - dSum);

  return true;
}

//**********************************************************************
// CMCMC::~CMCMC()
// Default De-Constructor
//**********************************************************************
CMCMC::~CMCMC() {
}
