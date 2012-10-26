//============================================================================
// Name        : CDerivedQuantityReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDERIVEDLAYERREPORT_H_
#define CDERIVEDLAYERREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CDerivedLayer;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedLayerReport: public CFileReport {
public:
  CDerivedLayerReport();
  virtual                  ~CDerivedLayerReport();
  CReport*                 clone() { return new CDerivedLayerReport(*this); }
  void                     validate();
  void                     build();
  void                     execute();

protected:
  string                   sDerivedLayer;
  CDerivedLayer            *pDerivedLayer;
  bool                     bPrintInitialisation;
};

#endif /* CDERIVEDLAYERREPORT_H_ */
