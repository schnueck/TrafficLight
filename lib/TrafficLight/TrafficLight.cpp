/**
 * @file    TrafficLight.cpp
 * @author  Thomas Schnuecker (thomas@schnuecker.de)
 * @brief   Represents a traffic light with 3 lights (red, yellow, green).
 * @version 0.1
 * @date    2021-01-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Arduino.h"
#include <TrafficLight.h>

const int TrafficLight::OFF = 0;
const int TrafficLight::RED = 1;
const int TrafficLight::RED_YELLOW = 2;
const int TrafficLight::GREEN = 3;
const int TrafficLight::YELLOW = 4;
const int TrafficLight::MAINTENANCE = 5; // yellow blinking light

/**
 * @brief Construct a new TrafficLight object
 * 
 * @param red       PIN to which red LED is connected.
 * @param yellow    PIN to which yellow LED is connected.
 * @param green     PIN to which green LED is connected.
 */
TrafficLight::TrafficLight(int red, int yellow, int green) {
    _redLedPin = red;
    _yellowLedPin = yellow;
    _greenLedPin = green;

    pinMode(_redLedPin, OUTPUT);
    pinMode(_yellowLedPin, OUTPUT);
    pinMode(_greenLedPin, OUTPUT);

    this->switchToPhase(TrafficLight::RED);
}

/**
 * @brief Switches to a specific traffic light phase
 * 
 * @param phase ID of a phase. Use one out of TrafficLight::RED, TrafficLight::YELLOW,
 * TrafficLight::GREEN, TrafficLight::RED_YELLOW.
 */
void TrafficLight::switchToPhase(int phase) {
    _currentPhase = phase;
    switch(phase) {
        case TrafficLight::OFF:
            digitalWrite(_redLedPin, LOW);
            digitalWrite(_yellowLedPin, LOW);
            digitalWrite(_greenLedPin, LOW);
        break;
        case TrafficLight::RED: default:
            digitalWrite(_redLedPin, HIGH);
            digitalWrite(_yellowLedPin, LOW);
            digitalWrite(_greenLedPin, LOW);
        break;
        case TrafficLight::YELLOW:
            digitalWrite(_redLedPin, LOW);
            digitalWrite(_yellowLedPin, HIGH);
            digitalWrite(_greenLedPin, LOW);
        break;
        case TrafficLight::GREEN:
            digitalWrite(_redLedPin, LOW);
            digitalWrite(_yellowLedPin, LOW);
            digitalWrite(_greenLedPin, HIGH);
        break;
        case TrafficLight::RED_YELLOW:
            digitalWrite(_redLedPin, HIGH);
            digitalWrite(_yellowLedPin, HIGH);
            digitalWrite(_greenLedPin, LOW);
        break;
    }
}

/**
 * @brief Switches TrafficLight to next phase.
 * 
 */
void TrafficLight::nextPhase() {
    if(_currentPhase >= TrafficLight::YELLOW) {
        _currentPhase = TrafficLight::OFF;
    }
   
    this->switchToPhase(_currentPhase + 1);
}

/**
 * @brief Sets TrafficLight into maintenance mode (yellow blinking);
 * 
 */
void TrafficLight::switchToMaintenance() {
    _isMaintenance = true;
}

void TrafficLight::switchToNormalOperations() {
    _isMaintenance = false;
}
