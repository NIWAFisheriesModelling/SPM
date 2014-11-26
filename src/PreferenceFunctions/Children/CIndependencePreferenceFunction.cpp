//============================================================================
// Name        : CIndependencePreferenceFunction.cpp
// Author      : 
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CIndependencePreferenceFunction.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../PDFs/CPDF.h"
#include "../../PDFs/CPDFManager.h"

//**********************************************************************
// CIndependencePreferenceFunction::CIndependencePreferenceFunction()
// Default Constructor
//**********************************************************************
CIndependencePreferenceFunction::CIndependencePreferenceFunction() {

  // Register Estimables
  // registerEstimable(PARAM_RHO, &dRho);		// There is no rho in the independence copula

  // Register user allowed variables
  //pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_PDFS);
  pParameterList->registerAllowed(PARAM_LAYERS);

}

//**********************************************************************
// void CIndependencePreferenceFunction::validate()
// Validate
//**********************************************************************
void CIndependencePreferenceFunction::validate() {
  try {

    // Assign our variables
    //dRho  = pParameterList->getDouble(PARAM_RHO);
    pParameterList->fillVector(vPDFNames, PARAM_PDFS);
    pParameterList->fillVector(vLayerNames, PARAM_LAYERS);

    // Validate parent
    CPreferenceFunction::validate();

    //Local validation
    //if (dRho <= 0.0)
    //  CError::errorLessThanEqualTo(PARAM_RHO, PARAM_ZERO);

	//********************************************
	//	This is the only copula that I will allow to have 1 or two PDF's
	//*********************************************
    //Ensure exactly 2 PDFs
    if (vPDFNames.size() != 1 || vPDFNames.size() != 2)
      CError::errorNotEqual(PARAM_PDFS, "One or Two only");

    //Ensure exactly 2 layers
    if (vPDFNames.size() != 1 || vPDFNames.size() != 2)
      CError::errorNotEqual(PARAM_LAYERS, "One or Two only");

  } catch (string &Ex) {
    Ex = "CIndependencePreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CIndependencePreferenceFunction::build()
// Validate
//**********************************************************************
void CIndependencePreferenceFunction::build() {

  // Build parent
  CIndependencePreferenceFunction::build();

  // Get PDFs
  CPDFManager *pPDFManager = CPDFManager::Instance();

  for (int i=0; i< (int)vPDFNames.size(); ++i) {
    vPDFs.push_back( pPDFManager->getPDF(vPDFNames[i]) );
    vPDFTypes.push_back(vPDFs[i]->getPDFType());
  }

  // Get Layers
  CLayerManager *pLayerManager = CLayerManager::Instance();

  for (int i=0; i< (int)vLayerNames.size(); ++i) {
    vLayers.push_back( pLayerManager->getLayer(vLayerNames[i]) );
  }

  // Validate values for this combination of PDFs
  //if ( vPDFNames[0] =="PARAM_NORMAL" && vPDFNames[1] =="PARAM_NORMAL")) {
  //  if (dRho <= 0.0)
  //    CError::errorLessThanEqualTo(PARAM_RHO, PARAM_ZERO);
  //}

}

//**********************************************************************
// double CIndependencePreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CIndependencePreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    vector<double> dValue;
    vector<double> dLayerValue;

    for (int i=0; (int)i < vLayers.size(); ++i) {
      dLayerValue[i] = vLayers[i]->getValue(TRIndex, TCIndex, RIndex, CIndex);
    }
	 double x1 = dLayervalue[0];
	 double x2 = dLayervalue[1];
    // Evaluate using copula
    if((vPDFTypes[0] == "PARAM_NORMAL") && (vPDFTypes[1] == "PARAM_NORMAL")){		// Margins Normal, Normal
	  double dPDF1 = vPDFs[0]->getPDFResult(x1);
	  double dPDF2 = vPDFs[1]->getPDFResult(x2);

      dRet = dPDF1 * dPDF2;

    } else if {
		((vPDFTypes[0] == "PARAM_NORMAL") && (vPDFTypes[1] == "PARAM_EXPONENTIAL")) || ((vPDFTypes[1] == "PARAM_NORMAL") && (vPDFTypes[0] == "PARAM_EXPONENTIAL")) {	// Margins Normal, Exponential
	 
	  double dPDF1 = vPDFs[0]->getPDFResult(x1);
	  double dPDF2 = vPDFs[1]->getPDFResult(x2);

      dRet = dPDF1 * dPDF2;

    } else if {
		((vPDFTypes[0] == "PARAM_EXPONENTIAL") && (vPDFTypes[1] == "PARAM_EXPONENTIAL"))) {	// Margins Exponential, Exponential
	 
	  double dPDF1 = vPDFs[0]->getPDFResult(x1);
	  double dPDF2 = vPDFs[1]->getPDFResult(x2);

      dRet = dPDF1 * dPDF2;


/*} else if {
	// Comment out lognormal we will just start with exponential and normal

		((vPDFTypes[0] == "PARAM_LOGNORMAL") && (vPDFTypes[1] == "PARAM_EXPONENTIAL")) || ((vPDFTypes[1] == "PARAM_LOGNORMAL") && (vPDFTypes[0] == "PARAM_EXPONENTIAL")) {	// Margins Log Normal, Exponential

	  double dPDF1 = vPDFs[0]->getPDFResult(x1);
	  double dPDF2 = vPDFs[0]->getPDFResult(x2);

      dRet = dPDF1 * dPDF2;

	} else if {
		((vPDFTypes[0] == "PARAM_NORMAL") && (vPDFTypes[1] == "PARAM_LOGNORMAL")) || ((vPDFTypes[1] == "PARAM_NORMAL") && (vPDFTypes[0] == "PARAM_LOGNORMAL")) {	// Margins Log Normal, Normal

	  double dPDF1 = vPDFs[0]->getPDFResult(x1);
	  double dPDF2 = vPDFs[0]->getPDFResult(x2);

      dRet = dPDF1 * dPDF2;
 */
	} else {
      CError::errorUnknown(PARAM_COPULA,vPDFNames[0]);
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CIndependencePreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CCIndependencePreferenceFunction::~CIndependencePreferenceFunction()
// Default De-Constructor
//**********************************************************************
CIndependencePreferenceFunction::~CIndependencePreferenceFunction() {
}
