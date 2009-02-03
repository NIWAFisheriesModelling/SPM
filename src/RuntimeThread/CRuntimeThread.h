//============================================================================
// Name        : CRuntimeThread.h
// Author      : S.Rasmussen
// Date        : 18/08/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CRUNTIMETHREAD_H_
#define CRUNTIMETHREAD_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes;
class CPreferenceFunctionManager;
class CEstimateManager;
class CInitializationPhaseManager;
class CLayerManager;
class CObservationManager;
class CPenaltyManager;
class CPriorManager;
class CProcessManager;
class CProfileManager;
class CCatchabilityManager;
class CSelectivityManager;
class CTimeStepManager;
class CObjectiveFunction;
class CTimeStep;
class CInitializationPhase;
class CReporterManager;

//**********************************************************************
//
//
//**********************************************************************
class CRuntimeThread : public CBaseExecute {
public:
  // Functions
  CRuntimeThread();
  virtual                     ~CRuntimeThread();
  EState                      getCurrentState() { return eCurrentState; }
  CEstimateManager*           getEstimateManager() { return pEstimateManager; }
  void                        setWaiting(bool value);
  bool                        getWaiting();
  void                        setTerminate(bool value);
  bool                        getTerminate();
  double                      getScore() { return dScore; }
  void                        validate();
  void                        build();
  void                        rebuild();
  void                        execute() { executeBasicRun(); }
  void                        executeBasicRun();
  void                        executeEstimationRun();
  void                        executeMCMC();
  void                        clone(CRuntimeThread *Thread);
  void                        startModel();

protected:
  // Variables
  EState                      eCurrentState;
  CPreferenceFunctionManager  *pDirectedProcessManager;
  CEstimateManager            *pEstimateManager;
  CInitializationPhaseManager *pInitializationManager;
  CLayerManager               *pLayerManager;
  CObjectiveFunction          *pObjectiveFunction;
  CObservationManager         *pObservationManager;
  CPenaltyManager             *pPenaltyManager;
  CPriorManager               *pPriorManager;
  CProcessManager             *pProcessManager;
  CProfileManager             *pProfileManager;
  CCatchabilityManager        *pQManager;
  CSelectivityManager         *pSelectivityManager;
  CTimeStepManager            *pTimeStepManager;
  CReporterManager            *pReporterManager;
  int                         iNumberOfYears;
  bool                        bTerminate;
  bool                        bWaiting;
  double                      dScore;
  boost::mutex                mutWaiting;
  boost::mutex                mutTerminate;
};

#endif /* CRUNTIMETHREAD_H_ */
