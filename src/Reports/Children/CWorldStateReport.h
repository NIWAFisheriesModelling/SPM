//============================================================================
// Name        : CWorldStateReport.h
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CWORLDSTATEREPORT_H_
#define CWORLDSTATEREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward Dec
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CWorldStateReport: public CFileReport {
public:
  // Functions
  CWorldStateReport();
  virtual                     ~CWorldStateReport();
  CReport*                    clone() { return new CWorldStateReport(*this); }
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

#endif /* CWORLDSTATEREPORT_H_ */
