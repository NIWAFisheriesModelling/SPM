//============================================================================
// Name        : CDerivedLayer.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDERIVEDLAYER_H_
#define CDERIVEDLAYER_H_

// Global Headers
#include <boost/shared_ptr.hpp>

// Local headers
#include "../BaseClasses/CBaseExecute.h"
#include "../Layers/Numeric/CDoubleLayer.h"

// Namespace
using boost::shared_ptr;


typedef vector<vector<double> > Data;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedLayer : public CBaseBuild {
public:
  // Functions
  CDerivedLayer();
  virtual                     ~CDerivedLayer();
  vector<vector<double> >     getValue(int offset);
  void                        incrementInitialisationPhase() { iCurrentInitialisationPhase++; }
  int                         getValuesSize() { return vValues.size(); }
  virtual void                calculate() = 0;
  virtual void                calculate(int initialisationPhase) = 0;
  int                         getInitialisationSize() { return vvInitialisationValues.size(); }
  int                         getInitialisationValuesSize(int initialisationPhase = 0) { return vvInitialisationValues[initialisationPhase].size(); }
  vector<vector<double> >     getInitialisationValue(int initialisationPhase = 0, int index = 0) { return vvInitialisationValues[initialisationPhase][index]; }
  void                        build();
  void                        rebuild();

protected:
  // Members
  vector<vector<double> >     vBlankData;
  int                         iCurrentInitialisationPhase;
  vector<vector<Data> >       vvInitialisationValues;
  vector<Data>                vValues;

};

#endif /* CDERIVEDLAYER_H_ */
