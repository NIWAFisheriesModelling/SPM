//============================================================================
// Name        : DerivedLayer.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef DERIVEDLAYER_H_
#define DERIVEDLAYER_H_

const string derived_layer_abundance =
  "@derived_layer derived_layer_abundance\n"
  "type abundance\n"
  "time_step step_one\n"
  "categories immature mature spawning\n"
  "layer double\n"
  "selectivities constant constant constant\n";

const string derived_layer_biomass =
  "@derived_layer derived_layer_biomass\n"
  "type biomass\n"
  "time_step step_one\n"
  "categories immature mature spawning\n"
  "layer double\n"
  "selectivities constant constant constant\n";

#endif /* DERIVEDLAYER_H_ */
#endif /* TEST */
