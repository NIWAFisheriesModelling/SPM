//============================================================================
// Name        : CEstimateSummaryReporter.h
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CESTIMATESUMMARYREPORTER_H_
#define CESTIMATESUMMARYREPORTER_H_

// Local headers
#include "Base/CFileReporter.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimateSummaryReporter: public CFileReporter {
public:
  CEstimateSummaryReporter();
  virtual                     ~CEstimateSummaryReporter();
  CReporter*                  clone() { return new CEstimateSummaryReporter(*this); }
  void                        execute();
};

#endif /* CESTIMATESUMMARYREPORTER_H_ */
