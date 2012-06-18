/*
 * CTestDerivedQuantity.cpp
 *
 *  Created on: 18/06/2012
 *      Author: Admin
 */

#include "CTestDerivedQuantity.h"

CTestDerivedQuantity::CTestDerivedQuantity() {

}

CTestDerivedQuantity::~CTestDerivedQuantity() {

}

void CTestDerivedQuantity::calculate() {
  vValues.push_back(vValues.size());
}

void CTestDerivedQuantity::calculate(int initialisationPhase) {

  if ((int)vvInitialisationValues.size() <= initialisationPhase)
    vvInitialisationValues.resize(initialisationPhase+1);

  double value = (vvInitialisationValues[initialisationPhase].size()+1) * ((initialisationPhase+1) * 100);
  vvInitialisationValues[initialisationPhase].push_back(value);
}

