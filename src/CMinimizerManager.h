//============================================================================
// Name        : CMinimizerManager.h
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMINIMIZERMANAGER_H_
#define CMINIMIZERMANAGER_H_

// Local Headers
#include "BaseClasses/CBaseExecutableObject.h"

// Forward Declarations
class CRuntimeThread;
class CMinimizer;

//**********************************************************************
//
//
//**********************************************************************
class CMinimizerManager : public CBaseExecutableObject {
public:
  static CMinimizerManager*   Instance();
  static void                 Destroy();

  // Functions
  void                        addMinimizer(CMinimizer *value);
  void                        setActiveMinimizer(string value) { sMinimizer = value; }
  void                        addThread(CRuntimeThread *Thread);
  CMinimizer*                 getMinimizer() { return pMinimizer; }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Functions
  CMinimizerManager();
  virtual                     ~CMinimizerManager();

  // Variables
  string                      sMinimizer;
  CMinimizer                  *pMinimizer;
  int                         iMaxIterations;
  int                         iMaxEvaluations;
  double                      dGradientTolerance;
  double                      dStepsize;
  vector<CMinimizer*>         vMinimizerList;
  vector<CRuntimeThread*>     vThreadList;
  boost::mutex                mutThread;

private:
  static CMinimizerManager*   clInstance;
};

#endif /*CMINIMIZERMANAGER_H_*/
