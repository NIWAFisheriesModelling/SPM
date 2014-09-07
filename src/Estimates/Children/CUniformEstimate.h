//============================================================================
// Name        : CUniformEstimate.h
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science ©2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CUNIFORMESTIMATE_H_
#define CUNIFORMESTIMATE_H_

// headers
#include "../CEstimate.h"

/**
 * Class definition
 */
class CUniformEstimate : public CEstimate {
public:
  // methods
  CUniformEstimate();
  virtual                     ~CUniformEstimate() = default;
  void                        validate() override final { CEstimate::validate(); }
  double                      getScore() override final { return 0; }
};

#endif /* CUNIFORMESTIMATE_H_ */
