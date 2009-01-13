//============================================================================
// Name        : CPopulationConfigLoader.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CPopulationConfigLoader.h"
#include "../Processes/Population/CAgeingProcess.h"
#include "../Processes/Population/CConstantRecruitmentProcess.h"
#include "../Processes/Population/CNaturalMortalityProcess.h"
#include "../Processes/Population/CCategoryTransitionProcess.h"
#include "../Processes/Population/CEventMortalityProcess.h"
#include "../Processes/Movement/CUniformMovementProcess.h"
#include "../Processes/Movement/CDirectedMovementProcess.h"
#include "../Processes/Movement/Base/CMovementProcess.h"
#include "../Layers/Numeric/CDoubleLayer.h"
#include "../Layers/Numeric/CDistanceLayer.h"
#include "../Layers/Numeric/CAbundanceLayer.h"
#include "../Layers/String/CStringLayer.h"
#include "../Selectivities/Children/CConstantSelectivity.h"
#include "../Selectivities/Children/CLogisticSelectivity.h"
#include "../Selectivities/Children/CLogisticProducingSelectivity.h"
#include "../Selectivities/Children/CDoubleNormalSelectivity.h"
#include "../Selectivities/Children/CKnifeEdgeSelectivity.h"
#include "../PrintStates/CPrintState.h"
#include "../DirectedProcesses/Children/CExponentialDirectedProcess.h"
#include "../DirectedProcesses/Children/CThresholdDirectedProcess.h"
#include "../DirectedProcesses/Children/CNormalDirectedProcess.h"
#include "../DirectedProcesses/Children/CDoubleNormalDirectedProcess.h"
#include "../DirectedProcesses/Children/CLogisticDirectedProcess.h"
#include "../DirectedProcesses/Children/CInverseLogisticDirectedProcess.h"
#include "../DirectedProcesses/Children/CConstantDirectedProcess.h"
#include "../TimeSteps/CTimeStep.h"
#include "../DirectedProcesses/Factory/CDirectedProcessFactory.h"

//**********************************************************************
// CPopulationConfigLoader::CPopulationConfigLoader()
// Default Constructor
//**********************************************************************
CPopulationConfigLoader::CPopulationConfigLoader(string Directory) {
  // Set File Name and Load The File
  setDirectory(Directory);
  setFileName(CONFIG_FILE_POPULATION);
  loadConfigFile();

  pTimeStepManager           = CTimeStepManager::Instance();
  pProcessManager            = CProcessManager::Instance();
  pLayerManager              = CLayerManager::Instance();
  pSelectivityManager        = CSelectivityManager::Instance();
  pDirectedProcessManager    = CDirectedProcessManager::Instance();
  pInitializationManager     = CInitializationPhaseManager::Instance();
}

//**********************************************************************
// void CPopulationConfigLoader::processConfigFile()
// Process Our Config File
//**********************************************************************
void CPopulationConfigLoader::processConfigFile() {
  try {
    if (vConfigList.size() == 0)
      throw string(ERROR_EMPTY_FILE);

    // Loop Through Our Lines
    vConfigPtr = vConfigList.begin();
    while(vConfigPtr != vConfigList.end()) {
      if ((int)(*vConfigPtr).find(CONFIG_SECTION_SYMBOL) >= 0) {

        // Populate Our Parameters
        populateParameters();
        if (vParameterList.size() == 0)
          throw string(ERROR_EMPTY_PARAMETER);

        // Check What Section we are in
        if (vParameterList[0] == CONFIG_SECTION_SPATIAL_STRUCT)
          loadSpatialStructure();
        else if (vParameterList[0] == CONFIG_SECTION_POPULATION_STRUCT)
          loadPopulationStructure();
        else if (vParameterList[0] == CONFIG_SECTION_INITIALIZATION)
          loadInitialization();
        else if (vParameterList[0] == CONFIG_SECTION_ANNUAL_CYCLE)
          loadAnnualCycle();
        else if (vParameterList[0] == CONFIG_SECTION_TIME_STEP)
          loadTimeStep();
        else if (vParameterList[0] == CONFIG_SECTION_INITIALIZATION_PHASE)
          loadInitialisationPhase();
        else if (vParameterList[0] == CONFIG_SECTION_POPULATION_PROCESS)
          loadPopulationProcess();
        else if (vParameterList[0] == CONFIG_SECTION_MOVEMENT_PROCESS)
          loadMovementProcess();
        else if (vParameterList[0] == CONFIG_SECTION_LAYER)
          loadLayer();
        else if (vParameterList[0] == CONFIG_SECTION_SELECTIVITY)
          loadSelectivity();
        else if (vParameterList[0] == CONFIG_SECTION_DIRECTED_PROCESS)
          loadDirectedProcess();
        else
          throw string(ERROR_UNKNOWN_SECTION + vParameterList[0]);

        continue; // We Incremented Elsewhere
      } else
        throw string(ERROR_UNKNOWN_SYNTAX + (*vConfigPtr));

      vConfigPtr++;
    }
  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.processConfigFile()->" + Ex;
    throw Ex;
  }

  return;
}

//**********************************************************************
// void CPopulationConfigLoader::loadSpatialStructure()
// Load Population.sfm Section - Spatial_Structure
//**********************************************************************
void CPopulationConfigLoader::loadSpatialStructure() {
  try {
    // @spatial_structure should have no extra parameters
    if (vParameterList.size() != 1)
      throw string(ERROR_QTY_MORE_PARAMETERS);

    mSection.clear();

    // Loop until we hit a new section.
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if ( ((int)vParameterList.size() == 0) || (newSection()) ) {
        vConfigPtr++;
        continue;
      }

      for (int i = 1; i < (int)vParameterList.size(); ++i)
        mSection[vParameterList[0]].push_back(vParameterList[i]);

      if ((int)vParameterList.size() == 1) {
        mSection[vParameterList[0]].push_back("true");
      }

      vConfigPtr++;
    }

    CWorld *pWorld = CWorld::Instance();
    map<string, vector<string> >::iterator mPtr = mSection.begin();
    while (mPtr != mSection.end()) {

      vector<string>::iterator vPtr = (*mPtr).second.begin();
      while (vPtr != (*mPtr).second.end()) {
        pWorld->addParameter((*mPtr).first, (*vPtr));
        vPtr++;
      }
    }

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadSpatialStructure()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadPopulationStructure()
// Load @population_structure from population.sfm
//**********************************************************************
void CPopulationConfigLoader::loadPopulationStructure() {
  try {
    // @population_structure should have no extra parameters
    if (vParameterList.size() != 1)
      throw string(ERROR_QTY_MORE_PARAMETERS);

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
    /*    if (checkLine(PARAM_CATEGORIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pConfig->addCategory(vParameterList[i]);
        else if (checkLine(PARAM_MIN_AGE))
          pConfig->setMinAge(getIntValue(1));
        else if (checkLine(PARAM_MAX_AGE))
          pConfig->setMaxAge(getIntValue(1));
        else if (checkLine(PARAM_AGE_PLUS_GROUP))
          pConfig->setUseAgePlus(getBoolValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);*/
      }
      vConfigPtr++;
    }
    return;
  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadPopulationStructure()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadInitialization()
// Load Population Initialization Section
//**********************************************************************
void CPopulationConfigLoader::loadInitialization() {
  try {
    // No extra parameters allowed
    if (vParameterList.size() != 1)
      throw string(ERROR_QTY_MORE_PARAMETERS);

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        /*if (checkLine(PARAM_RUN_YEARS))
          pConfig->setNumberOfYearsToRun(getIntValue(1));
        else if (checkLine(PARAM_START_YEAR))
          pConfig->setHumanStartYear(getIntValue(1));
        else if (checkLine(PARAM_PROJECTION_YEARS))
          pConfig->setNumberOfYearsToProject(getIntValue(1));
        else if (checkLine(PARAM_INITIALIZATION_PHASES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pConfig->addInitializationPhase(vParameterList[i]);
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);*/
      }
      vConfigPtr++;
    }
  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadInitialization()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadAnnualCycle()
// Load @annual_cycle Section
//**********************************************************************
void CPopulationConfigLoader::loadAnnualCycle() {
  try {
    // @annual_cycle should have no extra parameters
    if (vParameterList.size() != 1)
      throw string(ERROR_QTY_MORE_PARAMETERS);

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
       /* if (checkLine(PARAM_TIME_STEPS))
          pConfig->setNumberOfTimeSteps(getIntValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);*/
      }
      vConfigPtr++;
    }
  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadAnnualCycle()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadTimeStep()
// Load a @time_step section
//**********************************************************************
void CPopulationConfigLoader::loadTimeStep() {
  try {
    /*CTimeStep *pTimeStep = new CTimeStep();
    pTimeStep->setStep(atoi(getLabel().c_str()));

    // Load Next Line
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_POPULATION_PROCESSES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pTimeStep->addPopulationProcess(vParameterList[i]);
        else if (checkLine(PARAM_MOVEMENT_PROCESSES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pTimeStep->addMovementProcess(vParameterList[i]);
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pTimeStepManager->addTimeStep(pTimeStep);*/

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadTimeStep()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadInitialisationPhase()
// Load @initialisation_phase
//**********************************************************************
void CPopulationConfigLoader::loadInitialisationPhase() {
  try {
    /*CTimeStep *pTimeStep = new CTimeStep();
    pTimeStep->setLabel(getLabel());

    // Load Next Line
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_YEARS))
          pTimeStep->setNumberOfYears(getIntValue(1));
        else if (checkLine(PARAM_PROCESSES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pTimeStep->addPopulationProcess(vParameterList[i]);
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pInitializationManager->addInitialisationPhase(pTimeStep);*/

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadInitialisationPhase()->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CPopulationConfigLoader::loadPopulationProcess()
// Load @population_process
//**********************************************************************
void CPopulationConfigLoader::loadPopulationProcess() {
  try {
    // @population_process should have 1 parameter (Label)
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Inc
    vConfigPtr++;

    // Populate Parameters
    populateParameters();

    if (vParameterList.size() == 0)
      throw string(ERROR_EMPTY_PARAMETER);

    // Must Be Type
    if (vParameterList[0] != PARAM_TYPE)
      throw string(ERROR_MISSING_SECTION_TYPE);

    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Check Parameters
    if (vParameterList[1] == PARAM_AGEING)
      loadPopulationProcess_Ageing();
    else if (vParameterList[1] == PARAM_RECRUITMENT)
      loadPopulationProcess_Recruitment();
    else if (vParameterList[1] == PARAM_NATURAL_MORTALITY)
      loadPopulationProcess_NaturalMortality();
    else if (vParameterList[1] == PARAM_EVENT_MORTALITY)
      loadPopulationProcess_EventMortality();
    else if (vParameterList[1] == PARAM_CATEGORY_TRANSITION)
      loadPopulationProcess_CategoryTransition();
    else
      throw string(ERROR_UNKNOWN_TYPE + vParameterList[1]);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadPopulationProcess()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadPopulationProcess_Ageing()
// Ageing type of @population_process
//**********************************************************************
void CPopulationConfigLoader::loadPopulationProcess_Ageing() {
  try {
    // Get Label
    CAgeingProcess *pProcess = new CAgeingProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseProcessAttributes(pProcess))
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }

    pProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadPopulationProcess_Ageing()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadPopulationProcess_Recruitment()
// @type = recruitment
//**********************************************************************
void CPopulationConfigLoader::loadPopulationProcess_Recruitment() {
 /* try {
    // Get Label
    CConstantRecruitmentProcess *pProcess = new CConstantRecruitmentProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseProcessAttributes(pProcess)) {
          if (checkLine(PARAM_PROPORTIONS, 1, MAX_PARAMS))
            for (int i = 1; i < (int)vParameterList.size(); ++i)
              pProcess->addProportion(getDoubleValue(i));
          else if (checkLine(PARAM_R0))
            pProcess->setR0(getIntValue(1));
          else if (checkLine(PARAM_STEEPNESS))
            pProcess->setSteepness(getDoubleValue(1));
          else if (checkLine(PARAM_SIGMA_R))
            pProcess->setSigmaR(getDoubleValue(1));
          else if (checkLine(PARAM_RHO))
            pProcess->setRho(getDoubleValue(1, true));
          else if (checkLine(PARAM_AGES, 1, MAX_PARAMS))
            for (int i = 1; i < (int)vParameterList.size(); ++i)
              pProcess->addAges(getIntValue(i));
          else if (checkLine(PARAM_METHOD))
            pProcess->setMethod(vParameterList[1]);
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadPopulationProcess_Recruitment()->" + Ex;
    throw Ex;
  }*/
}

//**********************************************************************
// void CPopulationConfigLoader::loadPopulationProcess_NaturalMortality()
// type = natural_mortality
//**********************************************************************
void CPopulationConfigLoader::loadPopulationProcess_NaturalMortality() {
  try {
    CNaturalMortalityProcess *pProcess = new CNaturalMortalityProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseProcessAttributes(pProcess)) {
          if (checkLine(PARAM_M))
            pProcess->setM(getDoubleValue(1));
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadPopulationProcess_NaturalMortality()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadPopulationProcess_EventMortality()
// load type = event_mortality
//**********************************************************************
void CPopulationConfigLoader::loadPopulationProcess_EventMortality() {
  try {
    CEventMortalityProcess *pProcess = new CEventMortalityProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseProcessAttributes(pProcess)) {
          if (checkLine(PARAM_YEARS,1,MAX_PARAMS))
            for (int i = 1; i < (int)vParameterList.size(); ++i)
              pProcess->addYears(getIntValue(i));
          else if (checkLine(PARAM_LAYERS,1,MAX_PARAMS))
            for (int i = 1; i < (int)vParameterList.size(); ++i)
              pProcess->addLayers(vParameterList[i]);
          else if (checkLine(PARAM_UMAX))
            pProcess->setUMax(getDoubleValue(1));
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadPopulationProcess_EventMortality()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadPopulationProcess_CategoryTransition()
// type = category_transition
//**********************************************************************
void CPopulationConfigLoader::loadPopulationProcess_CategoryTransition() {
  try {
    CCategoryTransitionProcess *pProcess = new CCategoryTransitionProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseProcessAttributes(pProcess)) {
          if (checkLine(PARAM_FROM))
            pProcess->setFrom(vParameterList[1]);
          else if (checkLine(PARAM_TO))
            pProcess->setTo(vParameterList[1]);
          else if (checkLine(PARAM_PROPORTION))
            pProcess->setProportion(getDoubleValue(1));
          else if (checkLine(PARAM_SELECTIVITY))
            pProcess->addSelectivity(vParameterList[1]);
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadPopulationProcess_CategoryTransition()->"  + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::LoadMovementProcess()
// Load Our @movement_process
//**********************************************************************
void CPopulationConfigLoader::loadMovementProcess() {
  try {
    // @movement_proces should have 1 parameter (Label)
    if (vParameterList.size() != 2)
      throw string("Invalid amount of parameters, expected 1 (Label)");

    // Inc
    vConfigPtr++;

    // Populate Parameters
    populateParameters();

    if (vParameterList.size() == 0)
      throw string(ERROR_EMPTY_PARAMETER);
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Must Be Type
    if (vParameterList[0] != PARAM_METHOD)
      throw string(ERROR_MISSING_SECTION_METHOD);

    if (vParameterList[1] == PARAM_SQUARE_UNIFORM)
      loadMovementProcess_Uniform();
    else if (vParameterList[1] == PARAM_HEX_UNIFORM)
      loadMovementProcess_Uniform();
    else if (vParameterList[1] == PARAM_DIRECTED)
      loadMovementProcess_Directed();
    else
      throw string(ERROR_UNKNOWN_PARAM + vParameterList[1]);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadMovementProcess()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadMovementProcess_Uniform()
// type = Uniform
//**********************************************************************
void CPopulationConfigLoader::loadMovementProcess_Uniform() {
  try {
    CUniformMovementProcess *pProcess = new CUniformMovementProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseProcessAttributes(pProcess)) {
          if (checkLine(PARAM_METHOD))
            pProcess->setMethod(vParameterList[1]);
          else if (checkLine(PARAM_PROPORTION))
            pProcess->setProportion(getDoubleValue(1));
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pProcessManager->addProcess(pProcess);
  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadMovementProcess_Uniform()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadMovementProcess_Directed()
// type = distributed
//**********************************************************************
void CPopulationConfigLoader::loadMovementProcess_Directed() {
  try {
    CDirectedMovementProcess *pProcess = new CDirectedMovementProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseProcessAttributes(pProcess)) {
          if (checkLine(PARAM_DIRECTED_PROCESSES, 1, MAX_PARAMS))
            for (int i = 1; i < (int)vParameterList.size(); ++i)
              pProcess->addDirectedProcess(vParameterList[i]);
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }

    pProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadMovementProcess_Directed()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadLayer()
// Load Layers
//**********************************************************************
void CPopulationConfigLoader::loadLayer() {
  try {
  // @label should have 1 parameter (Label)
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Inc
    vConfigPtr++;
    // Populate Parameters
    populateParameters();

    if (vParameterList.size() == 0)
      throw string(ERROR_EMPTY_PARAMETER);
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Must Be Type
    if (vParameterList[0] != PARAM_TYPE)
      throw string(ERROR_MISSING_SECTION_TYPE);
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    if (vParameterList[1] == PARAM_NUMERIC)
      loadLayer_Double();
    else if (vParameterList[1] == PARAM_CATEGORY)
      loadLayer_String();
    else if (vParameterList[1] == PARAM_DISTANCE)
      loadLayer_Distance();
    else if (vParameterList[1] == PARAM_ABUNDANCE)
      loadLayer_Abundance();
    else
      throw string(ERROR_UNKNOWN_PARAM + vParameterList[1]);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadLayer()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadLayer_Double()
// type = int
//**********************************************************************
void CPopulationConfigLoader::loadLayer_Double() {
  try {
    CDoubleLayer *pLayer = new CDoubleLayer();
    pLayer->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        int iRowNum = -1;
        // Check Section
        if (vParameterList[0].substr(0, 3) == PARAM_ROW) {
          if (vParameterList[0].length() > 3) {
            iRowNum = atoi(vParameterList[0].substr(3, vParameterList[0].length()-3).c_str());
            for (int i = 1; i < (int)vParameterList.size(); ++i)
              pLayer->setValue(iRowNum, i, getIntValue(i, true));
          } else
            throw string(ERROR_MISSING_ROW_NUMBER);

        } else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pLayerManager->addLayer(pLayer);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadLayer_Double()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadLayer_String()
// type = string
//**********************************************************************
void CPopulationConfigLoader::loadLayer_String() {
  try {
    CStringLayer *pLayer = new CStringLayer();
    pLayer->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        // Check For New Section
        if (newSection())
          break;

        int iRowNum = -1;

        // Check Section
        if (vParameterList[0].substr(0, 3) == PARAM_ROW) {
          if (vParameterList[0].length() > 3) {
            iRowNum = atoi(vParameterList[0].substr(3, vParameterList[0].length()-3).c_str());
            for (int i = 1; i < (int)vParameterList.size(); ++i)
              pLayer->setValue(iRowNum, i, vParameterList[i]);
          } else
            throw string(ERROR_MISSING_ROW_NUMBER);

        } else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }

    pLayerManager->addLayer(pLayer);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadLayer_String()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadLayer_Distance()
// type = distance
//**********************************************************************
void CPopulationConfigLoader::loadLayer_Distance() {
  try {
    CDistanceLayer *pLayer = new CDistanceLayer();
    pLayer->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }

    pLayerManager->addLayer(pLayer);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadLayer_Distance()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadLayer_Abundance()
//  type = abundance
//**********************************************************************
void CPopulationConfigLoader::loadLayer_Abundance() {
  try {
    CAbundanceLayer *pLayer = new CAbundanceLayer();
    pLayer->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        if (checkLine(PARAM_CATEGORIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pLayer->addCategory(vParameterList[i]);
        else if (checkLine(PARAM_SELECTIVITIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pLayer->addSelectivity(vParameterList[i]);
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }

    pLayerManager->addLayer(pLayer);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadLayer_Abundance()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadSelectivity()
// Load Selectivity
//**********************************************************************
void CPopulationConfigLoader::loadSelectivity() {
  try {
  // @selectivity should have 1 parameter (Label)
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Inc
    vConfigPtr++;
    // Populate Parameters
    populateParameters();

    if (vParameterList.size() == 0)
      throw string(ERROR_EMPTY_PARAMETER);
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Must Be Type
    if (vParameterList[0] != PARAM_TYPE)
      throw string(ERROR_MISSING_SECTION_TYPE);

    if (vParameterList[1] == PARAM_CONSTANT)
      loadSelectivity_Constant();
    else if (vParameterList[1] == PARAM_DOUBLE_NORMAL)
      loadSelectivity_DoubleNormal();
    else if (vParameterList[1] == PARAM_KNIFE_EDGE)
      loadSelectivity_KnifeEdge();
    else if (vParameterList[1] == PARAM_LOGISTIC_PRODUCING)
      loadSelectivity_LogisticProducing();
    else if (vParameterList[1] == PARAM_LOGISTIC)
      loadSelectivity_Logistic();
    else
      throw string(ERROR_UNKNOWN_PARAM + vParameterList[1]);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadSelectivity()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadSelectivity_Constant()
//
//**********************************************************************
void CPopulationConfigLoader::loadSelectivity_Constant() {
  try {
    CConstantSelectivity *pSelectivity = new CConstantSelectivity();
    pSelectivity->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_C))
          pSelectivity->setC(getIntValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pSelectivityManager->addSelectivity(pSelectivity);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadSelectivity_Constant()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadSelectivity_Logistic()
//
//**********************************************************************
void CPopulationConfigLoader::loadSelectivity_Logistic() {
  try {
    CLogisticSelectivity *pSelectivity = new CLogisticSelectivity();
    pSelectivity->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_A50))
          pSelectivity->setA50(getDoubleValue(1));
        else if (checkLine(PARAM_ATO95))
          pSelectivity->setAto95(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pSelectivityManager->addSelectivity(pSelectivity);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadSelectivity_Logistic()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadSelectivity_Logistic()
//
//**********************************************************************
void CPopulationConfigLoader::loadSelectivity_LogisticProducing() {
  try {
    CLogisticProducingSelectivity *pSelectivity = new CLogisticProducingSelectivity();
    pSelectivity->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_L))
          pSelectivity->setL(getIntValue(1));
        else if (checkLine(PARAM_H))
          pSelectivity->setH(getIntValue(1));
        else if (checkLine(PARAM_A50))
          pSelectivity->setA50(getDoubleValue(1));
        else if (checkLine(PARAM_ATO95))
          pSelectivity->setAto95(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pSelectivityManager->addSelectivity(pSelectivity);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadSelectivity_LogisticProducing()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadSelectivity_KnifeEdge()
//
//**********************************************************************
void CPopulationConfigLoader::loadSelectivity_KnifeEdge() {
  try {
    CKnifeEdgeSelectivity *pSelectivity = new CKnifeEdgeSelectivity();
    pSelectivity->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_C))
          pSelectivity->setC(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pSelectivityManager->addSelectivity(pSelectivity);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadSelectivity_KnifeedgeProducing()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadSelectivity_DoubleNormal()
//
//**********************************************************************
void CPopulationConfigLoader::loadSelectivity_DoubleNormal() {
  try {
    CDoubleNormalSelectivity *pSelectivity = new CDoubleNormalSelectivity();
    pSelectivity->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_MU))
          pSelectivity->setMu(getDoubleValue(1));
        else if (checkLine(PARAM_SIGMA_L))
          pSelectivity->setSigmaL(getDoubleValue(1));
        else if (checkLine(PARAM_SIGMA_R))
          pSelectivity->setSigmaR(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pSelectivityManager->addSelectivity(pSelectivity);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadSelectivity_Doublenormal()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
//
//
//**********************************************************************
void CPopulationConfigLoader::loadDirectedProcess() {
  try {
    // Should have 1 parameter (Label)
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    mSection.clear();

    // Save label for a second
    string sLabel = vParameterList[1];
    string sType  = "";

    // Loop until we hit a new section.
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if ( ((int)vParameterList.size() == 0) || (newSection()) ) {
        vConfigPtr++;
        continue;
      }

      for (int i = 1; i < (int)vParameterList.size(); ++i)
        mSection[vParameterList[0]].push_back(vParameterList[i]);

      if ((int)vParameterList.size() == 1) {
        mSection[vParameterList[0]].push_back("true");
      }

      vConfigPtr++;
    }

    // Did we hit a type parameter?
    if ((int)mSection[PARAM_TYPE].size() == 0)
      throw string("MISSING TYPE PARAM"); // ToDo: FIX THIS
    if ((int)mSection[PARAM_TYPE].size() > 1)
      throw string("TYPE MUST BE A SINGLE WORD, NO SPACES");

    sType = mSection[PARAM_TYPE][0];

    CDirectedProcess *pProcess = CDirectedProcessFactory::buildDirectedProcess(sType);
    pProcess->addParameter(PARAM_LABEL, sLabel);

    map<string, vector<string> >::iterator mPtr = mSection.begin();
    while (mPtr != mSection.end()) {

      vector<string>::iterator vPtr = (*mPtr).second.begin();
      while (vPtr != (*mPtr).second.end()) {
        pProcess->addParameter((*mPtr).first, (*vPtr));
        vPtr++;
      }
    }

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadDirectedProcess()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadDirectedProcess_Exponential()
// type = exponential
//**********************************************************************
void CPopulationConfigLoader::loadDirectedProcess_Exponential() {
  try {
    CExponentialDirectedProcess *pProcess = new CExponentialDirectedProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
          /*if (!loadBaseDirectedProcessAttributes(pProcess)) {
            if (checkLine(PARAM_LAMBDA))
              pProcess->setLambda(getDoubleValue(1));
            else
              throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
          }*/
      }
      vConfigPtr++;
    }
    pDirectedProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadDirectedProcess_Exponential()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadDirectedProcess_Threshold()
// type = threshold
//**********************************************************************
void CPopulationConfigLoader::loadDirectedProcess_Threshold() {
  try {
    CThresholdDirectedProcess *pProcess = new CThresholdDirectedProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        /*if (!loadBaseDirectedProcessAttributes(pProcess)) {
          if (checkLine(PARAM_N))
            pProcess->setN(getDoubleValue(1));
          else if (checkLine(PARAM_LAMBDA))
            pProcess->setLambda(getDoubleValue(1));
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }*/
      }
      vConfigPtr++;
    }
    pDirectedProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadDirectedProcess_Threshhold()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadDirectedProcess_Normal()
// type = normal
//**********************************************************************
void CPopulationConfigLoader::loadDirectedProcess_Normal() {
  try {
    CNormalDirectedProcess *pProcess = new CNormalDirectedProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
         /* if (!loadBaseDirectedProcessAttributes(pProcess)) {
            if (checkLine(PARAM_MU))
              pProcess->setMu(getDoubleValue(1));
            else if (checkLine(PARAM_SIGMA))
              pProcess->setSigma(getDoubleValue(1));
            else
              throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
          }*/
      }
      vConfigPtr++;
    }
    pDirectedProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadDirectedProcess_Normal()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadDirectedProcess_DoubleNormal()
// type = double_normal
//**********************************************************************
void CPopulationConfigLoader::loadDirectedProcess_DoubleNormal() {
  try {
    CDoubleNormalDirectedProcess *pProcess = new CDoubleNormalDirectedProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        /*if (!loadBaseDirectedProcessAttributes(pProcess)) {
          if (checkLine(PARAM_MU))
            pProcess->setMu(getDoubleValue(1));
          else if (checkLine(PARAM_SIGMA_L))
            pProcess->setSigmaL(getDoubleValue(1));
          else if (checkLine(PARAM_SIGMA_R))
            pProcess->setSigmaR(getDoubleValue(1));
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }*/
      }
      vConfigPtr++;
    }
    pDirectedProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadDirectedProcess_DoubleNormal()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadDirectedProcess_Logisitic()
// type = logistic
//**********************************************************************
void CPopulationConfigLoader::loadDirectedProcess_Logistic() {
  try {
    CLogisticDirectedProcess *pProcess = new CLogisticDirectedProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
         /* if (!loadBaseDirectedProcessAttributes(pProcess)) {
            if (checkLine(PARAM_A50))
              pProcess->setA50(getDoubleValue(1));
            else if (checkLine(PARAM_ATO95))
              pProcess->setAto95(getDoubleValue(1));
            else
              throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
          }*/
      }
      vConfigPtr++;
    }
    pDirectedProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadDirectedProcess_Logistic()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadDirectedProcess_InverseLogisitic()
// type = inverse_logistic
//**********************************************************************
void CPopulationConfigLoader::loadDirectedProcess_InverseLogistic() {
  try {
    CInverseLogisticDirectedProcess *pProcess = new CInverseLogisticDirectedProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
         /* if (!loadBaseDirectedProcessAttributes(pProcess)) {
            if (checkLine(PARAM_A50))
              pProcess->setA50(getDoubleValue(1));
            else if (checkLine(PARAM_ATO95))
              pProcess->setAto95(getDoubleValue(1));
            else
              throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
         }*/
      }
      vConfigPtr++;
    }
    pDirectedProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadDirectedProcess_InverseLogistic()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPopulationConfigLoader::loadDirectedProcess_Constant()
// type = constant
//**********************************************************************
void CPopulationConfigLoader::loadDirectedProcess_Constant() {
  try {
    CConstantDirectedProcess *pProcess = new CConstantDirectedProcess();
    pProcess->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseDirectedProcessAttributes(pProcess)) {
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }
    pDirectedProcessManager->addProcess(pProcess);

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadDirectedProcess_Constant()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// bool CPopulationConfigLoader::loadBaseProcessAttributes(CProcess *Process)
// Load The Base (Common) Process Attributes
//**********************************************************************
bool CPopulationConfigLoader::loadBaseProcessAttributes(CProcess *Process) {
  try {
    if (checkLine(PARAM_LAYER_NAME))
      Process->setLayerName(vParameterList[1]);
    else if (checkLine(PARAM_LAYER_MIN))
      Process->setLayerMin(getDoubleValue(1,1));
    else if (checkLine(PARAM_LAYER_MAX))
      Process->setLayerMax(getDoubleValue(1));
    else if (checkLine(PARAM_LAYER_CATEGORIES, 1, MAX_PARAMS))
      for (int i = 1; i < (int)vParameterList.size(); ++i)
        Process->addLayerCategory(vParameterList[i]);
    else if (checkLine(PARAM_CATEGORIES, 1, MAX_PARAMS))
      for (int i = 1; i < (int)vParameterList.size(); ++i)
        Process->addCategory(vParameterList[i]);
    else if (checkLine(PARAM_SELECTIVITIES, 1, MAX_PARAMS))
      for (int i = 1; i < (int)vParameterList.size(); ++i)
        Process->addSelectivity(vParameterList[i]);
    else if (checkLine(PARAM_PENALTY))
      Process->setPenalty(vParameterList[1]);
    else
      return false;

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadBaseProcessAttributes()->" + Ex;
    throw Ex;
  }

  return true;
}

//**********************************************************************
// bool CPopulationConfigLoader::loadBaseDirectedProcessAttributes(CDirectedProcess *Process)
// Load the base (common) DirectedProcess attributes
//**********************************************************************
bool CPopulationConfigLoader::loadBaseDirectedProcessAttributes(CDirectedProcess *Process) {
  try {
    /*if (checkLine(PARAM_ALPHA))
      Process->setAlpha(getDoubleValue(1));
    else if (checkLine(PARAM_LAYER_NAME))
      Process->addParameter(vParameterList[0], vParameterList[1]);
    else
      return false;*/

  } catch (string Ex) {
    Ex = "CPopulationConfigLoader.loadBaseDirectedProcessAttributes()->" + Ex;
    throw Ex;
  }
  return true;
}

//**********************************************************************
// CPopulationConfigLoader::~CPopulationConfigLoader()
// Default De-Constructor
//**********************************************************************
CPopulationConfigLoader::~CPopulationConfigLoader() {
  pTimeStepManager      = 0;
  pProcessManager       = 0;
  pLayerManager         = 0;
  pSelectivityManager   = 0;
}
