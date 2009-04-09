//============================================================================
// Name        : CLayerDerivedWorldViewReport.h
// Author      : S.Rasmussen
// Date        : 9/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLAYERDERIVEDWORLDVIEWREPORT_H_
#define CLAYERDERIVEDWORLDVIEWREPORT_H_

// Local Headers
#include "Base/CFileReport.h"

// Forward Dec
class CTimeStepManager;
class CLayerManager;
class CStringLayer;
class CLayerDerivedWorldView;

//**********************************************************************
//
//
//**********************************************************************
class CLayerDerivedWorldViewReport : public CFileReport {
public:
  // Functions
  CLayerDerivedWorldViewReport();
  virtual                     ~CLayerDerivedWorldViewReport();
  CReport*                    clone() { return new CLayerDerivedWorldViewReport(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Variables
  int                         iYear;
  int                         iTimeStep;
  string                      sTimeStep;
  CTimeStepManager            *pTimeStepManager;
  string                      sLayer;
  CStringLayer                *pLayer;
  CLayerManager               *pLayerManager;
  CLayerDerivedWorldView      *pWorldView;
  map<string, int>            mAreas;
};

#endif /* CLAYERDERIVEDWORLDVIEWREPORT_H_ */
