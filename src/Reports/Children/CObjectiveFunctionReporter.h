//============================================================================
// Name        : CObjectiveFunctionReporter.h
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBJECTIVEFUNCTIONREPORTER_H_
#define COBJECTIVEFUNCTIONREPORTER_H_

// Local Headers
#include "Base/CFileReporter.h"

//**********************************************************************
//
//
//**********************************************************************
class CObjectiveFunctionReporter: public CFileReporter {
public:
  CObjectiveFunctionReporter();
  virtual                     ~CObjectiveFunctionReporter();
  CReporter*                  clone() { return new CObjectiveFunctionReporter(*this); }
  void                        execute();
};

#endif /* COBJECTIVEFUNCTIONREPORTER_H_ */
