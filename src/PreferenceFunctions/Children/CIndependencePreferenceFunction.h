//============================================================================
// Name        : CIndependencePreferenceFunction.h
// Author      : 
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
//============================================================================
#ifndef CINDEPENDENCEPREFERENCEFUNCTION_H_
#define CINDEPENDENCEPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

class CPDF;
class CLayers;

//**********************************************************************
//
//
//**********************************************************************
class CIndependencePreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CIndependencePreferenceFunction();
  virtual                    ~CIndependencePreferenceFunction();
  CPreferenceFunction*       clone() { return new CIndependencePreferenceFunction(*this); }
  //double                     getRho() { return dRho; }
  double                     getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void                       validate();
  void                       build();

protected:
  // Variables
  //double                     dRho;
  vector<string>             vPDFNames;
  vector<string>             vLayerNames;
  vector<string>             vPDFTypes;
  vector<CPDF*>              vPDFs;
  vector<CLayers*>           vLayers;
};

#endif /*CINDEPENDENCEPREFERENCEFUNCTION_H_*/

