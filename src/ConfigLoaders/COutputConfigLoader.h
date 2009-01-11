//============================================================================
// Name        : COutputConfigLoader.h
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COUTPUTCONFIGLOADER_H_
#define COUTPUTCONFIGLOADER_H_

// Local Headers
#include "CBaseConfigLoader.h"
#include "../PrintStates/CPrintStateManager.h"

//**********************************************************************
//
//
//**********************************************************************
class COutputConfigLoader : public CBaseConfigLoader {
public:
  // Functions
	COutputConfigLoader(string Directory);
	virtual                    ~COutputConfigLoader();
	void                       processConfigFile();
  void                       loadPrintState();
  void                       loadPrintState_WorldGrid();
  void                       loadPrintState_Objective();
  void                       loadPrintState_Estimate();
  void                       loadPrintState_EstimateValue();
  bool                       loadBasePrintStateAttributes(CPrintState *PrintState);

protected:
  // Variables
  CPrintStateManager        *pPrintStateManager;
};

#endif /*COUTPUTCONFIGLOADER_H_*/
