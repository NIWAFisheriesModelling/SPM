//============================================================================
// Name        : CGumbelPreferenceFunction.h
// Author      : 
// Copyright   : 
//============================================================================
#ifndef CGUMBELPREFERENCEFUNCTION_H_
#define CGUMBELPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

class CPDF;
class CLayers;

//**********************************************************************
//
//
//**********************************************************************
class CGumbelPreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CGumbelPreferenceFunction();
  virtual                    ~CGumbelPreferenceFunction();
  CPreferenceFunction*       clone() { return new CGumbelPreferenceFunction(*this); }
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
  vector<CLayers*>           vLayers;
};

#endif /*CGUMBELPREFERENCEFUNCTION_H_*/

