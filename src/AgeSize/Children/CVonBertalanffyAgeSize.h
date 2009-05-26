//============================================================================
// Name        : CVonBertalanffyAgeSize.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CVONBERTALANFFYAGESIZE_H_
#define CVONBERTALANFFYAGESIZE_H_

#include "../CAgeSize.h"

//**********************************************************************
//
//
//**********************************************************************
class CVonBertalanffyAgeSize: public CAgeSize {
public:
  // Functions
  CVonBertalanffyAgeSize();
  virtual                     ~CVonBertalanffyAgeSize();
  CAgeSize*                   clone() { return new CVonBertalanffyAgeSize(*this); }
  void                        validate();
  void                        build();
  void                        rebuild();
  double                      getMeanSize(double &age);
  double                      getMeanWeight(double &age);

protected:
  double                      dLinf;
  double                      dK;
  double                      dT0;
  double                      dCV;
  std::string                 sDistribution;
  string                      sSizeWeight;
  CSizeWeight*                pSizeWeight;

};

#endif /* CVONBERTALANFFYAGESIZE_H_ */
