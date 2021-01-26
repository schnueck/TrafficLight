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
    int _currentPhase;
    unsigned long _timer = 0;
    bool _isMaintenance = false;

public:
    const static int OFF;
    const static int RED;
    const static int YELLOW;
    const static int GREEN;
    const static int RED_YELLOW;
    const static int MAINTENANCE;
    const static int PHASES[4];

   /**
   * @brief Construct a new Traffic Light object
   * 
   * @param red        : Red LED pin
   * @param yellow     : Yellow LED pin
   * @param green      : Green LED pin
   */
    TrafficLight(int red, int yellow, int green);

    void switchToPhase(int phase);
    void nextPhase();
    void switchToMaintenance();
    void switchToNormalOperations();

private:
};

#endif