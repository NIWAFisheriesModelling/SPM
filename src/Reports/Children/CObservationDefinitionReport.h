//============================================================================
// Name        : CObservationDefinitionReport.h
// Author      : S.Rasmussen
// Date        : 13/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBSERVATIONDEFINITIONREPORT_H_
#define COBSERVATIONDEFINITIONREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Dec
class CObservation;

//**********************************************************************
//
//
//**********************************************************************
class CObservationDefinitionReport: public CFileReport {
public:
  // Functions
  CObservationDefinitionReport();
  virtual                     ~CObservationDefinitionReport();
  CReport*                    clone() { return new CObservationDefinitionReport(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Variables
  string                      sObservation;
  CObservation                *pObservation;
};

#endif /* COBSERVATIONDEFINITIONREPORT_H_ */
