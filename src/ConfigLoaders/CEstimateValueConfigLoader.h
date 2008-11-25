//============================================================================
// Name        : CEstimateValueConfigLoader.h
// Author      : S.Rasmussen
// Date        : 12/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CESTIMATEVALUECONFIGLOADER_H_
#define CESTIMATEVALUECONFIGLOADER_H_

// Local Headers
#include "CBaseConfigLoader.h"
#include "../CEstimateManager.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimateValueConfigLoader: public CBaseConfigLoader {
public:
  // Functions
  CEstimateValueConfigLoader(string Directory);
  virtual                    ~CEstimateValueConfigLoader();
  void                       processConfigFile();

protected:
  // Variables
  CEstimateManager           *pEstimateManager;
};

#endif /* CESTIMATEVALUECONFIGLOADER_H_ */
