//============================================================================
// Name        : CEstimateValueReporter.h
// Author      : S.Rasmussen
// Date        : 4/03/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CESTIMATEVALUEREPORTER_H_
#define CESTIMATEVALUEREPORTER_H_

// Local headers
#include "Base/CFileReporter.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimateValueReporter: public CFileReporter {
public:
  CEstimateValueReporter();
  virtual                     ~CEstimateValueReporter();
  CReporter*                  clone() { return new CEstimateValueReporter(*this); }
  void                        execute();

protected:
  bool                        bWrittenHeader;
};

#endif /* CESTIMATEVALUEREPORTER_H_ */
