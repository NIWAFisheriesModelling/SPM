//============================================================================
// Name        : CWorldStateReporter.h
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CWORLDSTATEREPORTER_H_
#define CWORLDSTATEREPORTER_H_

// Local headers
#include "Base/CFileReporter.h"

// Forward Dec
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CWorldStateReporter: public CFileReporter {
public:
  // Functions
  CWorldStateReporter();
  virtual                     ~CWorldStateReporter();
  CReporter*                  clone() { return new CWorldStateReporter(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Variables
  int                         iYear;
  int                         iTimeStep;
  string                      sTimeStep;
  CTimeStepManager            *pTimeStepManager;
};

#endif /* CWORLDSTATEREPORTER_H_ */
