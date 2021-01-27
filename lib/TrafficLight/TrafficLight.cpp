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

// define traffic light signals
const int TrafficLight::OFF = 0;
const int TrafficLight::RED = 1;
const int TrafficLight::RED_YELLOW = 2;
const int TrafficLight::GREEN = 3;
const int TrafficLight::YELLOW = 4;

/**
 * @brief Construct a new TrafficLight object that is in state OFF.
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

    this->switchToSignal(TrafficLight::OFF);
}

/**
 * @brief Switches to a specific traffic light signal
 * 
 * @param signal ID of a signal. Use one out of TrafficLight::RED, TrafficLight::YELLOW,
 * TrafficLight::GREEN, TrafficLight::RED_YELLOW.
 */
void TrafficLight::switchToSignal(int signal) {
    switch(signal) {
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

