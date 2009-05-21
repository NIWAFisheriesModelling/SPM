//============================================================================
// Name        : CNormalDistribution.h
// Author      : S.Rasmussen
// Date        : 7/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALDISTRIBUTION_H_
#define CNORMALDISTRIBUTION_H_

// Global Headers
#include <boost/math/distributions/normal.hpp>

// Local headers
#include "../BaseClasses/CBaseManager.h"

using boost::math::normal;

//**********************************************************************
//
//
//**********************************************************************
class CNormalDistribution: public CBaseManager {
public:
  static CNormalDistribution* Instance();
  static void                 Destroy();
  void                        validate();
  void                        build();
  double                      getCDF(double x, double mu, double sigma);

protected:
  // Functions
  CNormalDistribution();
  virtual                     ~CNormalDistribution();

private:
  static CNormalDistribution* clInstance;
};

#endif /* CNORMALDISTRIBUTION_H_ */
