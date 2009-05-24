//============================================================================
// Name        : CAgeSize.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGESIZE_H_
#define CAGESIZE_H_

// Local headers
#include "../BaseClasses/CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CAgeSize : public CBaseBuild {
public:
  // Functions
  CAgeSize();
  virtual                     ~CAgeSize();
  void                        validate();
  void                        build();
  virtual void                rebuild();
  virtual double              getMeanSize(double &age) { return 1; }

};

#endif /* CAGESIZE_H_ */
