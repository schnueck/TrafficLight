/**
 * @file    TrafficLight.h
 * @author  Thomas Schnuecker (thomas@schnuecker.de)
 * @brief   Represents a traffic light with 3 lights (red, yellow, green).
 * @version 0.1
 * @date    2021-01-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TrafficLight_h
#define TrafficLight_h

#include <Arduino.h>

class TrafficLight
{
    int _redLedPin;
    int _yellowLedPin;
    int _greenLedPin;

public:
    // declare traffic light signals
    const static int OFF;
    const static int RED;
    const static int YELLOW;
    const static int GREEN;
    const static int RED_YELLOW;

   /**
   * @brief Construct a new Traffic Light object
   * 
   * @param red        : Red LED pin
   * @param yellow     : Yellow LED pin
   * @param green      : Green LED pin
   */
    TrafficLight(int red, int yellow, int green);

    void switchToSignal(int signal);

private:
};

#endif