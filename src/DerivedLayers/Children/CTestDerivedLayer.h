//============================================================================
// Name        : CSampleDerivedLayer.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description : This derived layer exists only for unit testing
//               the parent class
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CTESTDERIVEDLAYER_H_
#define CTESTDERIVEDLAYER_H_

#include "../CDerivedLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CTestDerivedLayer : public CDerivedLayer {
public:
  CTestDerivedLayer();
  virtual                     ~CTestDerivedLayer();
  void                        calculate();
  void                        calculate(int initialisationPhase);
  void                        build() { };
};

#endif /* CTESTDERIVEDLAYER_H_ */
