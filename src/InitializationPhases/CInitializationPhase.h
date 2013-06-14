//============================================================================
// Name        : CInitializationPhase.h
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINITIALIZATIONPHASE_H_
#define CINITIALIZATIONPHASE_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes
class CTimeStep;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationPhase : public CBaseExecute {
public:
  CInitializationPhase();
  virtual                     ~CInitializationPhase();
  void                        validate();
  void                        build();
  void                        execute();
  int                         getCurrentTimeStep() { return iCurrentTimeStep; }
  vector<string>              getTimeStepNames() { return vTimeStepNames; }
  void                        setExecutionOrderIndex(int index) { iExecutionOrderIndex = index; }
  bool                        getConvergenceCheck() { return bConvergenceCheck; }
  vector<int>                 getConvergedYears() { return vConvergedYears; }
  vector<double>              getConvergedLambda() { return vConvergedLambda; }

protected:
  int                           iYears;
  int                           iCurrentTimeStep;
  int                           iExecutionOrderIndex;
  vector<string>                vTimeStepNames;
  vector<CTimeStep*>            vTimeSteps;
  bool                          bConvergenceCheck;
  double                        dLambda;
  double                        dDiffLambda;
  double                        dTotalLambda;
  vector<int>                   vLambdaYears;
  vector<vector<vector<vector<double> > > >  vvWorldCopy;
  CWorldSquare                  *pPreviousSquare;

  vector<int>                   vConvergedYears;
  vector<double>                vConvergedLambda;

};

#endif /* CINITIALIZATIONPHASE_H_ */
