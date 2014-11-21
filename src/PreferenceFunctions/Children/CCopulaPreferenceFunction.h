//============================================================================
// Name        : CCopulaPreferenceFunction.h
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
//============================================================================
#ifndef CCOPULAPREFERENCEFUNCTION_H_
#define CCOPULAPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

class CPDF;
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CCopulaPreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CCopulaPreferenceFunction();
  virtual                    ~CCopulaPreferenceFunction();
  CPreferenceFunction*       clone() { return new CCopulaPreferenceFunction(*this); }
  double                     getRho() { return dRho; }
  double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void                       validate();
  void                       build();

protected:
  // Variables
  double                     dRho;
  vector<string>             vPDFNames;
  vector<string>             vLayerNames;
  vector<string>             vPDFTypes;
  vector<CPDF*>              vPDFs;
  vector<CNumericLayer*>     vLayers;
};

#endif /*CCOPULAPREFERENCEFUNCTION_H_*/

