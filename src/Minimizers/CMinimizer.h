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

// Local Includes
#include "../BaseClasses/CBaseBuildableObject.h"

//**********************************************************************
// class CMinimzer
//
//**********************************************************************
class CMinimizer : public CBaseBuildableObject {
public:
  // Functions
  CMinimizer();
	virtual                    ~CMinimizer();
  void                       setMaxIterations(int value) { iMaxIterations = value; }
  int                        getMaxIterations() { return iMaxIterations; }
  void                       setMaxEvaluations(int value) { iMaxEvaluations = value; }
  int                        getMaxEvaluations() { return iMaxEvaluations; }
  void                       setGradientTolerance(double value) { dGradientTolerance = value; }
  double                     getGradientTolerance() { return dGradientTolerance; }
  void                       setStepSize(double value) { dStepSize = value; }
  double                     getStepSize() { return dStepSize; }
  double                     getHessianValue(int row, int col) { return pHessian[row][col]; }
  virtual void               runEstimation() = 0;
  virtual void               validate() { }
  virtual void               build();

protected:
  // Variables
  int                         iMaxIterations;
  int                         iMaxEvaluations;
  double                      dGradientTolerance;
  double                      dStepSize;
  double                      **pHessian;
  int                         iEstimateCount;
};

#endif /*CMINIMIZER_H_*/
