//============================================================================
// Name        : CBiomassEventMortalityProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBIOMASSEVENTMORTALITYPROCESS_H_
#define CBIOMASSEVENTMORTALITYPROCESS_H_

// Local headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CBiomassEventMortalityProcess : public CProcess {
public:
  // Functions
  CBiomassEventMortalityProcess();
  virtual                     ~CBiomassEventMortalityProcess();
  CProcess*                   clone() { return new CBiomassEventMortalityProcess(*this); }
  void                        validate();
  void                        build();
  void                        execute();
};

#endif /* CBIOMASSEVENTMORTALITYPROCESS_H_ */
