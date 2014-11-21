//============================================================================
// Name        : CCopulaPreferenceFunction.cpp
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CCopulaPreferenceFunction.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../PDFs/Children/CNormalPDF.h"
#include "../../PDFs/CPDF.h"
#include "../../PDFs/CPDFManager.h"

//**********************************************************************
// CCopulaPreferenceFunction::CCopulaPreferenceFunction()
// Default Constructor
//**********************************************************************
CCopulaPreferenceFunction::CCopulaPreferenceFunction() {

  // Register Estimables
  registerEstimable(PARAM_RHO, &dRho);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_PDFS);
  pParameterList->registerAllowed(PARAM_LAYERS);

}

//**********************************************************************
// void CCopulaPreferenceFunction::validate()
// Validate
//**********************************************************************
void CCopulaPreferenceFunction::validate() {
  try {

    // Assign our variables
    dRho  = pParameterList->getDouble(PARAM_RHO);
    pParameterList->fillVector(vPDFNames, PARAM_PDFS);
    pParameterList->fillVector(vLayerNames, PARAM_LAYERS);

    // Validate parent
    CPreferenceFunction::validate();

    //Local validation
    if (dRho <= 0.0)
      CError::errorLessThanEqualTo(PARAM_RHO, PARAM_ZERO);

    //Ensure exactly 2 PDFs
    if (vPDFNames.size() != 2)
      CError::errorNotEqual(PARAM_PDFS, "two");

    //Ensure exactly 2 layers
    if (vLayerNames.size() != 2)
      CError::errorNotEqual(PARAM_LAYERS, "two");

  } catch (string &Ex) {
    Ex = "CCopulaPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCopulaPreferenceFunction::build()
// Validate
//**********************************************************************
void CCopulaPreferenceFunction::build() {

  // Build parent
  CPreferenceFunction::build();

  // Get PDFs
  CPDFManager *pPDFManager = CPDFManager::Instance();

  for (int i=0; i< (int)vPDFNames.size(); ++i) {
    vPDFs.push_back( pPDFManager->getPDF(vPDFNames[i]) );
    vPDFTypes.push_back(vPDFs[i]->getPDFType());
  }

  // Get Layers
  CLayerManager *pLayerManager = CLayerManager::Instance();

  for (int i=0; i< (int)vLayerNames.size(); ++i) {
    vLayers.push_back( pLayerManager->getNumericLayer(vLayerNames[i]) );
  }

  // Validate values for this combination of PDFs
  //if ( vPDFNames[0] =="PARAM_NORMAL" && vPDFNames[1] =="PARAM_NORMAL")) {
  //  if (dRho <= 0.0)
  //    CError::errorLessThanEqualTo(PARAM_RHO, PARAM_ZERO);
  //}

}

//**********************************************************************
// double CCopulaPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CCopulaPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    vector<double> dValue;
    vector<double> dLayerValue;

    for (int i=0; i < (int)vLayers.size(); ++i) {
      dLayerValue[i] = vLayers[i]->getValue(TRIndex, TCIndex, RIndex, CIndex);
    }

    // Evaluate using copula
    if((vPDFTypes[0] == PARAM_NORMAL) && (vPDFTypes[1] == PARAM_NORMAL)) {

      CNormalPDF *pNormalPDF1 = dynamic_cast<CNormalPDF*>(vPDFs[0]);
      CNormalPDF *pNormalPDF2 = dynamic_cast<CNormalPDF*>(vPDFs[1]);

      double x1 = dLayerValue[0];
      double mu1 = pNormalPDF1->getMu();
      double sigma1 = pNormalPDF1->getSigma();
      double dPDF1 = pNormalPDF1->getPDFResult(dLayerValue[0]);
      double dCDF1 = pNormalPDF1->getCDFResult(dLayerValue[0]);

      double x2 = dLayerValue[1];
      double mu2 = pNormalPDF2->getMu();
      double sigma2 = pNormalPDF2->getSigma();
      double dPDF2 = pNormalPDF2->getPDFResult(dLayerValue[1]);
      double dCDF2 = pNormalPDF2->getCDFResult(dLayerValue[1]);

      dRet = dRho; // alter to be appropriate function of dValue1/dValue2/dRho

    } else {
      CError::errorUnknown(PARAM_COPULA,vPDFNames[0]);
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CCopulaPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CCopulaPreferenceFunction::~CCopulaPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CCopulaPreferenceFunction::~CCopulaPreferenceFunction() {
}
