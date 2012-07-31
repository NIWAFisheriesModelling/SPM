//============================================================================
// Name        : CMCMC.h
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CMCMC_H_
#define CMCMC_H_

// Global Headers
#include <boost/numeric/ublas/matrix.hpp>

// Local Headers
#include "../BaseClasses/CBaseExecute.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../Minimizers/CMinimizer.h"

// Structs
struct SChainItem {
  int             iIteration;
  double          dScore;
  double          dLikelihood;
  double          dPrior;
  double          dPenalty;
  double          dAcceptanceRate;
  double          dAcceptanceRateSinceAdapt;
  double          dStepSize;
  vector<double>  vValues;
};

// Classes
class CRuntimeThread;

using namespace boost::numeric;

//**********************************************************************
//
//
//**********************************************************************
class CMCMC : public CBaseExecute {
public:
  static CMCMC*              Instance();
  static void                Destroy();

  // Methods
  void                       validate();
  void                       build();
  void                       execute();
  vector<SChainItem>         getMCMCChain() { return vChain; }
  ublas::matrix<double>      getOriginalCovariance() { return mxOriginalCovariance; }
  ublas::matrix<double>      getCovariance() { return mxCovariance; }
  ublas::matrix<double>      getCovarianceLT() { return mxCovarianceLT; }  // Cholesky decomposition (lower triangle) of mxCovariance
  vector<string>             getEstimateNames() { return vEstimateNames; }

protected:
  // Functions
  CMCMC();
  virtual                    ~CMCMC();
  void                       buildCovarianceMatrix();
  void                       generateEstimates();
  void                       generateRandomStart();
  void                       generateNewCandidate();
  void                       fillMultivariateNormal(double stepsize);
  void                       fillMultivariatet(double stepsize);
  bool                       choleskyDecomposition();
  void                       updateStepSize(int iteration);

  // Variables
  string                     sType;
  double                     dStart;
  int                        iLength;
  int                        iKeep;
  int                        iEstimateCount;
  int                        iJumps;
  int                        iSuccessfulJumps;
  int                        iJumpsSinceAdapt;
  int                        iSuccessfulJumpsSinceAdapt;
  double                     dMaxCorrelation;
  string                     sCorrelationMethod;
  double                     dCorrelationDiff;
  double                     dStepSize;
  string                     sProposalDistribution;
  int                        iDF;
  ublas::matrix<double>      mxOriginalCovariance;
  ublas::matrix<double>      mxCovariance;
  ublas::matrix<double>      mxCovarianceLT;
  vector<double>             vCandidates;
  vector<bool>               vbIsEnabledEstimate;
  vector<SChainItem>         vChain;
  vector<int>                vAdaptStepSize;
  CMinimizer                 *pMinimizer;
  vector<string>             vEstimateNames;

private:
  static CMCMC*              clInstance;
};

#endif /*CMCMC_H_*/
