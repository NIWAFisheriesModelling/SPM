//============================================================================
// Name        : CParameterListReport.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPARAMETERLISTREPORT_H_
#define CPARAMETERLISTREPORT_H_

// Local headers
#include "Base/CFileReport.h"

//**********************************************************************
//
//
//**********************************************************************
class CParameterListReport: public CFileReport {
public:
  CParameterListReport();
  virtual                     ~CParameterListReport();
  CReport*                    clone() { return new CParameterListReport(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  string                      sParameter;
  CBaseObject                 *pTarget;
};

#endif /* CPARAMETERLISTREPORT_H_ */
