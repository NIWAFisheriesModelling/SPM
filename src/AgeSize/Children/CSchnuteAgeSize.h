//============================================================================
// Name        : CSchnuteAgeSize.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSCHNUTEAGESIZE_H_
#define CSCHNUTEAGESIZE_H_

#include "../CAgeSize.h"

//**********************************************************************
//
//
//**********************************************************************
class CSchnuteAgeSize: public CAgeSize {
public:
  // Functions
  CSchnuteAgeSize();
  virtual                     ~CSchnuteAgeSize();
  CAgeSize*                   clone() { return new CSchnuteAgeSize(*this); }
  void                        validate();
  void                        build();
  void                        rebuild();
  double                      getMeanSize(double &age);
  double                      getMeanWeight(double &age);

protected:
  double                      dY1;
  double                      dY2;
  double                      dTau1;
  double                      dTau2;
  double                      dA;
  double                      dB;
  double                      dCV;
  std::string                 sDistribution;
  string                      sSizeWeight;
  CSizeWeight*                pSizeWeight;

};

#endif /* CSCHNUTEAGESIZE_H_ */
