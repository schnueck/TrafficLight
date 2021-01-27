/**
 * @file    TrafficLightController.cpp
 * @author  Thomas Schnuecker (thomas@schnuecker.de)
 * @brief   Controller class for traffic lights.
 * @version 0.1
 * @date    2021-01-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Arduino.h"
#include <TrafficLightController.h>

const int TrafficLightController::OFF = 0;
const int TrafficLightController::NORMAL = 1;
const int TrafficLightController::MAINTENANCE = 2;

/**
 * @brief Construct a new TrafficLightController::TrafficLightController object
 * 
 * @param tl1 traffic light 1
 * @param tl2 traffic light 2
 */
TrafficLightController::TrafficLightController(TrafficLight *tl1, TrafficLight *tl2) {
    _trafficLights[0] = tl1;
    _trafficLights[1] = tl2;
    switchOff();
}

void TrafficLightController::setProgram(int program[][3]){
   
}

/**
 * @brief TrafficLightController loop to be called within main loop.
 * This loop will check whether or not time is up for next traffic light 
 * phase change.
 */
void TrafficLightController::loop(){
    switch (_currentMode) {
        case TrafficLightController::OFF:
            break;
        case TrafficLightController::MAINTENANCE:
            _maintenanceLoop();
            break;
        case TrafficLightController::NORMAL:default:
            _standardLoop();
            break;
    }
}

/**
 * @brief Run through traffic light phases.
 * 
 */
void TrafficLightController::_standardLoop() {
    if (millis() > _timer) {
        _currentPhase = _getNextPhase(_currentPhase);

        for (int i = 0; i < MAX_TRAFFIC_LIGHTS; i++) {
            _trafficLights[i]->switchToSignal(_phases[_currentPhase][i+1]);
        }

        // set new timer, add duration of curren phase to millis()
        _setNewTimer(_phases[_currentPhase][0]);
    }
}

/**
 * @brief Run through maintenance loop.
 * 
 */
void TrafficLightController::_maintenanceLoop() {
    if (millis() > _timer) {
        _currentPhase = ++_currentPhase % 2;

        for (int i = 0; i < MAX_TRAFFIC_LIGHTS; i++) {
            _trafficLights[i]->switchToSignal(_maintenanceMode[_currentPhase][i+1]);
        }

        // set new timer, add duration of curren phase to millis()
        _setNewTimer(_maintenanceMode[_currentPhase][0]);
    }
}

/**
 * @brief Switch traffic lights to normal operations.
 * 
 */
void TrafficLightController::switchToNormal() {
    switchOff();
    _currentMode = TrafficLightController::NORMAL;
    _currentPhase = 0;
}

/**
 * @brief Switch traffic lights to maintenance mode (yellow blinking).
 * 
 */
void TrafficLightController::switchToMaintenance() {
    switchOff();
    _currentMode = TrafficLightController::MAINTENANCE;
}

/**
 * @brief Switch traffic lights off.
 * 
 */
void TrafficLightController::switchOff() {
    _currentMode = TrafficLightController::OFF;
    _timer = 0;
    for (int i = 0; i < MAX_TRAFFIC_LIGHTS; i++) {
        _trafficLights[i]->switchToSignal(TrafficLight::OFF);
    }
}

int TrafficLightController::mode() {
    return _currentMode;
}

/**
 * @brief Return ID of next traffic light pase.
 * 
 * @param phase current phase.
 * @return int  next phase.
 */
int TrafficLightController::_getNextPhase(unsigned int phase) {
    phase++;
    if (phase >= (sizeof(_phases)/sizeof(_phases[0]))) {
        phase = 1;
    }
    return phase;
}

/**
 * @brief Set new timer, add duration of current phase to millis()
 * 
 * @param phaseDuration in seconds
 */
void TrafficLightController::_setNewTimer(int phaseDuration) {
        _timer = millis() + (phaseDuration * 1000);
}