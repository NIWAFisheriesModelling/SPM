//============================================================================
// Name        : CMinimizer.h
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMINIMIZER_H_
#define CMINIMIZER_H_

// Global headers
#include <boost/numeric/ublas/matrix.hpp>

// Local headers
#include "../BaseClasses/CBaseBuild.h"

// Usings
using namespace boost::numeric;

//**********************************************************************
// class CMinimzer
//
//**********************************************************************
class CMinimizer : public CBaseBuild {
public:
  // Functions
  CMinimizer();
  virtual                    ~CMinimizer();
  int                        getMaxIterations() { return iMaxIterations; }
  int                        getMaxEvaluations() { return iMaxEvaluations; }
  double                     getGradientTolerance() { return dGradientTolerance; }
  double                     getStepSize() { return dStepSize; }
  double                     getBuildCovariance() { return bCovariance; }
  double                     getHessianValue(int row, int col) { return pHessian[row][col]; }
  void                       buildCovarianceMatrix();
  virtual void               runEstimation() = 0;
  virtual void               validate();
  virtual void               build();

protected:
  // Variables
  int                         iMaxIterations;
  int                         iMaxEvaluations;
  double                      dGradientTolerance;
  double                      dStepSize;
  double                      **pHessian;
  ublas::matrix<double>       mxCovariance;
  int                         iEstimateCount;
  bool                        bCovariance;
};

#endif /*CMINIMIZER_H_*/
