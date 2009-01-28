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

  // Functions
  void                       addThread(CRuntimeThread *Thread);
	void                       setStart(int value) { iStart = value; }
	int                        getStart() { return iStart; }
	void                       setLength(int value) { iLength = value; }
	int                        getLength() { return iLength; }
	void                       setKeep(int value) { iKeep = value; }
	int                        getKeep() { return iKeep; }
	void                       setAdaptiveStepsize(bool value) { bAdaptiveStepsize = value; }
	bool                       getAdaptiveStepsize() { return bAdaptiveStepsize; }
	void                       addAdaptAt(int value);
	int                        getAdaptAtCount() { return vAdaptAtList.size(); }
	void                       setProposalT(bool value) { bProposalT = value; }
	bool                       getProposalT() { return bProposalT; }
	void                       setDf(int value) { iDf = value; }
	int                        getDf() { return iDf; }
	void                       validate();
	void                       build();
	void                       execute();

protected:
  // Functions
  CMCMC();
  virtual                    ~CMCMC();
  void                       sleep(int milliseconds);
  void                       buildCovarianceMatrix();
  bool                       generateEstimates();
  bool                       choleskyDecomposition();

  // Variables
  int                        iStart;
  int                        iLength;
  int                        iKeep;
  bool                       bAdaptiveStepsize;
  vector<int>                vAdaptAtList;
  int                        iBurnIn;
  bool                       bProposalT;
  int                        iDf;
  vector<double>             vLastAcceptedList;
  vector<CRuntimeThread*>    vThreadList;
  boost::mutex               mutThread;
  ublas::matrix<double>      mxCovariance;
  ublas::matrix<double>      mxCovarianceLT;
  vector<double>             vCandidates;
  vector<double>             vMeans;

private:
  static CMCMC*              clInstance;
};

#endif /*CMCMC_H_*/
