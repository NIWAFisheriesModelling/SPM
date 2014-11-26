//============================================================================
// Name        : CGaussianPreferenceFunction.h
// Author      :
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
//============================================================================
#ifndef CGAUSSIANPREFERENCEFUNCTION_H_
#define CGAUSSIANPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

class CPDF;
class CLayers;

//**********************************************************************
//
//
//**********************************************************************
class CGaussianPreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CGaussianPreferenceFunction();
  virtual                    ~CGaussianPreferenceFunction();
  CPreferenceFunction*       clone() { return new CGaussianPreferenceFunction(*this); }
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

#endif /*CGAUSSIANPREFERENCEFUNCTION_H_*/

