//============================================================================
// Name        : CNoneSizeWeight.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNONESIZEWEIGHT_H_
#define CNONESIZEWEIGHT_H_

#include "../CSizeWeight.h"

//**********************************************************************
//
//
//**********************************************************************
class CNoneSizeWeight: public CSizeWeight {
public:
  // Functions
  CNoneSizeWeight();
  virtual                     ~CNoneSizeWeight();
  CSizeWeight*                clone() { return new CNoneSizeWeight(*this); }
  void                        validate();
  void                        build();
  void                        rebuild();
  double                      getMeanWeight(double &size) { return 1; }

};

#endif /* CNONESIZEWEIGHT_H_ */
