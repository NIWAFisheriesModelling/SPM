//============================================================================
// Name        : CBetaEstimate.h
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science ©2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CBETAESTIMATE_H_
#define CBETAESTIMATE_H_

// headers
#include "../CEstimate.h"

/**
 * class definition
 */
class CBetaEstimate : public CEstimate {
public:
  CBetaEstimate();
  virtual                     ~CBetaEstimate() = default;
  void                        validate() override final;
  double                      getScore() override final;

protected:
  // Variables
  double                     dMu;
  double                     dSigma;
  double                     dA;
  double                     dB;

private:
   // Variables
  double                     dV;
  double                     dT;
  double                     dM;
  double                     dN;
};

#endif /* CBETAESTIMATE_H_ */
