//============================================================================
// Name        : CRuntimeController.h
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CRUNTIMECONTROLLER_H_
#define CRUNTIMECONTROLLER_H_

// Global Headers
#include <string>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/thread/barrier.hpp>

// Namespaces
using std::string;

// Forward Prototyping our Classes
// Use this instead of #include to prevent
// Cyclic-Dependencies
class CRuntimeThread;

// Enums
typedef enum {
  RUN_MODE_INVALID,
  RUN_MODE_BASIC,
  RUN_MODE_ESTIMATION,
  RUN_MODE_PROFILE,
  RUN_MODE_MARKOV_CHAIN_MONTE_CARLO,
  RUN_MODE_FORWARD_PROJECTION
} ERunMode;

typedef enum {
  STATE_INVALID,
  STATE_VALIDATION,
  STATE_CONSTRUCTION,
  STATE_INITIALIZATION,
  STATE_MODELLING,
  STATE_FINALIZATION
} EState;

// Typedefs
typedef boost::mutex::scoped_lock lock;

//**********************************************************************
//
//
//**********************************************************************
class CRuntimeController {
public:
  static CRuntimeController* Instance();
  static void                Destroy();

  // Functions
  void                       setRunMode(string value);
  void                       setRunMode(ERunMode value) { eRunMode = value; }
  ERunMode                   getRunMode() { return eRunMode; }
  EState                     getCurrentState();
  CRuntimeThread*            getCurrentThread();
  void                       loadConfiguration();
  void                       run();

protected:
  // Functions
	CRuntimeController();
	virtual                    ~CRuntimeController();
	void                       startEstimation();
	static void                initEstimationThread();
	void                       startMCMC();
	static void                initMCMCThread();

	// Variables
	ERunMode                   eRunMode;
	int                        iCurrentEstimateValue;
  CRuntimeThread*            pBaseThread;

private:
  // Variables
  static CRuntimeController* clInstance;
  boost::mutex               mutLock;
  boost::barrier             *runtimeBarrier;
};

#endif /*CRUNTIMECONTROLLER_H_*/
