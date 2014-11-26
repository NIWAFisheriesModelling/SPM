//============================================================================
// Name        : CFrankPreferenceFunction.h
// Author      : 
// Copyright   : 
//============================================================================
#ifndef CFRANKPREFERENCEFUNCTION_H_
#define CFRANKPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

class CPDF;
class CLayers;

//**********************************************************************
//
//
//**********************************************************************
class CFrankPreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CFrankPreferenceFunction();
  virtual                    ~CFrankPreferenceFunction();
  CPreferenceFunction*       clone() { return new CFrankPreferenceFunction(*this); }
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

#endif /*CFRANKPREFERENCEFUNCTION_H_*/

