//============================================================================
// Name        : CNoneAgeSize.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNONEAGESIZE_H_
#define CNONEAGESIZE_H_

#include "../CAgeSize.h"

//**********************************************************************
//
//
//**********************************************************************
class CNoneAgeSize: public CAgeSize {
public:
  // Functions
  CNoneAgeSize();
  virtual                     ~CNoneAgeSize();
  void                        validate();
  void                        build();
  void                        rebuild();
  double                      getMeanSize(double &size) { return 1; };

};

#endif /* CNONEAGESIZE_H_ */
