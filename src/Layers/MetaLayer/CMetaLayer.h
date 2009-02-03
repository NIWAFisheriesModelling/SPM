//============================================================================
// Name        : CMetaLayer.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMETALAYER_H_
#define CMETALAYER_H_

// Global Headers
#include <vector>

// Local headers
#include "../CLayer.h"

// Using
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CMetaLayer : public CLayer {
public:
  // Functions
  CMetaLayer();
  virtual                     ~CMetaLayer();
  CLayer*                     clone() { return new CMetaLayer(*this); }
  void                        validate();
  void                        build();

protected:
  // Variables
  vector<int>                vYears;
  vector<string>             vLayerNames;
};

#endif /* CMETALAYER_H_ */
