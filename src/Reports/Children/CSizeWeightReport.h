//============================================================================
// Name        : CSizeWeightReport.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSIZEWEIGHTREPORT_H_
#define CSIZEWEIGHTREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CSizeWeight;

//**********************************************************************
//
//
//**********************************************************************
class CSizeWeightReport: public CFileReport {
public:
  CSizeWeightReport();
  virtual                     ~CSizeWeightReport();
  CReport*                    clone() { return new CSizeWeightReport(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  string                      sSizeWeight;
  CSizeWeight                *pSizeWeight;
  vector<double>              vSizeList;

};

#endif /* CSIZEWEIGHTREPORT_H_ */
