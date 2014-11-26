//============================================================================
// Name        : CGumbelPreferenceFunction.cpp
// Author      : 
// Copyright   :
//============================================================================

// Local Headers
#include "CGumbelPreferenceFunction.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../PDFs/CPDF.h"
#include "../../PDFs/CPDFManager.h"

//**********************************************************************
// CGumbelPreferenceFunction::CGumbelPreferenceFunction()
// Default Constructor
//**********************************************************************
CGumbelPreferenceFunction::CGumbelPreferenceFunction() {

  // Register Estimables
  registerEstimable(PARAM_RHO, &dRho);		

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_PDFS);
  pParameterList->registerAllowed(PARAM_LAYERS);

}

//**********************************************************************
// void CGumbelPreferenceFunction::validate()
// Validate
//**********************************************************************
void CGumbelPreferenceFunction::validate() {
  try {

    // Assign our variables
    dRho  = pParameterList->getDouble(PARAM_RHO);
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
    if (vPDFNames.size() != 2)
      CError::errorNotEqual(PARAM_PDFS, "two");

    //Ensure exactly 2 layers
    if (vLayerNames.size() != 2)
      CError::errorNotEqual(PARAM_LAYERS, "two");

  } catch (string &Ex) {
    Ex = "CGumbelPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CGumbelPreferenceFunction::build()
// Validate
//**********************************************************************
void CGumbelPreferenceFunction::build() {

  // Build parent
  CGumbelPreferenceFunction::build();

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
// double CGumbelPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CGumbelPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    vector<double> dValue;
    vector<double> dLayerValue;

    for (int i=0; (int)i < vLayers.size(); ++i) {
      dLayerValue[i] = vLayers[i]->getValue(TRIndex, TCIndex, RIndex, CIndex);
    }

		double u1 = vPDFs[0]->getCDFResult(dLayerValue[0]);
		double u2 = vPDFs[1]->getCDFResult(dLayerValue[1])
   
//		dRet = exp(- ((-log(u1))^dRho + (-log(u2))^dRho)^(1/dRho) * (((-log(u1))^(dRho-1))/u1) * (((-log(u2))^(dRho-1))/u2) *
//		(((-log(u1))^dRho + (-log(u2))^dRho)^((2/dRho)-2) + ((dRho-1) * ((-log(u1))^dRho + (-log(u2))^Theta)^((1/(dRho)-2)))))* vPDFs[0]->getPDFResult(dLayerValue[0]) * vPDFs[1]->getPDFResult(dLayerValue[1]);

	// Evaluate using Gumbel copula
    if((vPDFTypes[0] == "PARAM_NORMAL") && (vPDFTypes[1] == "PARAM_NORMAL")){		// Margins Normal, Normal
	  double dPDF1 = vPDFs[0]->getPDFResult(x1);
	  double dPDF2 = vPDFs[1]->getPDFResult(x2);

	  double dCDF1 = vPDFs[0]->getCDFResult(x1);
	  double dCDF2 = vPDFs[1]->getCDFResult(x2);

		dRet = exp(- ((-log(dCDF1))^dRho + (-log(dCDF2))^dRho)^(1/dRho) * (((-log(dCDF1))^(dRho-1))/dCDF1) * (((-log(dCDF2))^(dRho-1))/dCDF2) *
	(((-log(dCDF1))^dRho + (-log(dCDF2))^dRho)^((2/dRho)-2) + ((dRho-1) * ((-log(dCDF1))^dRho + (-log(dCDF2))^Theta)^((1/(dRho)-2)))))* dPDF1 * dPDF2;


    } else if {
		((vPDFTypes[0] == "PARAM_NORMAL") && (vPDFTypes[1] == "PARAM_EXPONENTIAL")) || ((vPDFTypes[1] == "PARAM_NORMAL") && (vPDFTypes[0] == "PARAM_EXPONENTIAL")) {	// Margins Normal, Exponential

	  double dPDF1 = vPDFs[0]->getPDFResult(x1);
	  double dPDF2 = vPDFs[1]->getPDFResult(x2);

	  double dCDF1 = vPDFs[0]->getCDFResult(x1);
	  double dCDF2 = vPDFs[1]->getCDFResult(x2);

		dRet = exp(- ((-log(dCDF1))^dRho + (-log(dCDF2))^dRho)^(1/dRho) * (((-log(dCDF1))^(dRho-1))/dCDF1) * (((-log(dCDF2))^(dRho-1))/dCDF2) *
	(((-log(dCDF1))^dRho + (-log(dCDF2))^dRho)^((2/dRho)-2) + ((dRho-1) * ((-log(dCDF1))^dRho + (-log(dCDF2))^Theta)^((1/(dRho)-2)))))* dPDF1 * dPDF2;

    } else if {
		((vPDFTypes[0] == "PARAM_EXPONENTIAL") && (vPDFTypes[1] == "PARAM_EXPONENTIAL"))) {	// Margins Exponential, Exponential
	 
	  double dPDF1 = vPDFs[0]->getPDFResult(x1);
	  double dPDF2 = vPDFs[1]->getPDFResult(x2);

	  double dCDF1 = vPDFs[0]->getCDFResult(x1);
	  double dCDF2 = vPDFs[1]->getCDFResult(x2);

		dRet = exp(- ((-log(dCDF1))^dRho + (-log(dCDF2))^dRho)^(1/dRho) * (((-log(dCDF1))^(dRho-1))/dCDF1) * (((-log(dCDF2))^(dRho-1))/dCDF2) *
	(((-log(dCDF1))^dRho + (-log(dCDF2))^dRho)^((2/dRho)-2) + ((dRho-1) * ((-log(dCDF1))^dRho + (-log(dCDF2))^Theta)^((1/(dRho)-2)))))* dPDF1 * dPDF2;

   
	} else {
      CError::errorUnknown(PARAM_COPULA,vPDFNames[0]);
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CGumbelPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CGumbelPreferenceFunction::~CGumbelPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CGumbelPreferenceFunction::~CGumbelPreferenceFunction() {
}
