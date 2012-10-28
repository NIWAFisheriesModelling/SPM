//============================================================================
// Name        : CSampleDerivedLayer.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
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
