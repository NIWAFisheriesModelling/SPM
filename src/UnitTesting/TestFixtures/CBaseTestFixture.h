//============================================================================
// Name        : CBaseTestFixture.h
// Author      : S.Rasmussen
// Date        : 30/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST
#ifndef CBASETESTFIXTURE_H_
#define CBASETESTFIXTURE_H_

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../CConfiguration.h"
#include "../../CWorld.h"
#include "../../CRuntimeController.h"
#include "../../CLayerManager.h"
#include "../../CSelectivityManager.h"
#include "../../CPenaltyManager.h"
#include "../../CDirectedProcessManager.h"

// Namespace
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
class CBaseTestFixture {
public:
  // Functions
  CBaseTestFixture();
  virtual                    ~CBaseTestFixture();

  // Variables -- These Are Pubic so our Test's Can Use Them
  CConfiguration             *pConfig;
  CRuntimeController         *pRuntime;
  CWorld                     *pWorld;
  CLayerManager              *pLayerManager;
  CSelectivityManager        *pSelectivityManager;
  CPenaltyManager            *pPenaltyManager;
  CPreferenceFunctionManager    *pPreferenceFunctionManager;
  int                        immatureIndex;
  int                        matureIndex;
  int                        spawningIndex;

protected:
  // Functions
  void                       setupConfiguration();
  void                       setupWorld();
  void                       setupRuntime();
  void                       setupLayers();
  void                       setupSelectivities();
  void                       setupPenalties();
  void                       setupDirectedProcesses();
  void                       validateAll();
  void                       buildAll();
};

#endif /* CBASETESTFIXTURE_H_ */
#endif // UNITTEST
