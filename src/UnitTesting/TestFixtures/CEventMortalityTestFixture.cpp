//============================================================================
// Name        : CEventMortalityTestFixture.cpp
// Author      : S.Rasmussen
// Date        : 4/06/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef UNITTEST

// Local Headers
#include "CEventMortalityTestFixture.h"
#include "../../Layers/NumericLayers/CDoubleLayer.h"

//**********************************************************************
// CEventMortalityTestFixture::CEventMortalityTestFixture()
// Default Constructor
//**********************************************************************
CEventMortalityTestFixture::CEventMortalityTestFixture() {
  setupCustomLayers();
}

//**********************************************************************
// void CEventMortalityTestFixture::setupCustomLayers()
// Setup Our Custom Layers
//**********************************************************************
void CEventMortalityTestFixture::setupCustomLayers() {

  //***************************************************
  // Double Layer Varient
  CDoubleLayer *pLayer   = 0;
  BOOST_CHECK_NO_THROW(pLayer = new CDoubleLayer());
  BOOST_CHECK_NO_THROW(pLayer->setLabel("double_layer_2000"));

  for (int i = 0; i < pWorld->getHeight(); ++i)
    for (int j = 0; j < pWorld->getWidth(); ++j)
      BOOST_CHECK_NO_THROW(pLayer->setValue( (i+1), (j+1), 100-(i+j) ) );

  BOOST_CHECK_NO_THROW(pLayerManager->addLayer(pLayer));
  BOOST_CHECK_NO_THROW(pLayerManager->validate());
  BOOST_CHECK_NO_THROW(pLayerManager->build());
}

//**********************************************************************
// CEventMortalityTestFixture::~CEventMortalityTestFixture()
// Destructor
//**********************************************************************
CEventMortalityTestFixture::~CEventMortalityTestFixture() {
}

#endif // UNITTEST
