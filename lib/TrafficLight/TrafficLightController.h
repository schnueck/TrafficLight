/**
 * @file    TrafficLightController.h
 * @author  Thomas Schnuecker (thomas@schnuecker.de)
 * @brief   Controller class for traffic lights.
 * @version 0.1
 * @date    2021-01-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TrafficLightController_h
#define TrafficLightController_h

#include <Arduino.h>
#include <TrafficLight.h>

#define MAX_TRAFFIC_LIGHTS 2

class TrafficLightController
{

    TrafficLight *_trafficLights[MAX_TRAFFIC_LIGHTS];
    int _phases[9][3] = {
        {0, TrafficLight::OFF, TrafficLight::OFF},
        {2, TrafficLight::RED, TrafficLight::RED},
        {1, TrafficLight::RED_YELLOW, TrafficLight::RED},
        {8, TrafficLight::GREEN, TrafficLight::RED},
        {2, TrafficLight::YELLOW, TrafficLight::RED},
        {2, TrafficLight::RED, TrafficLight::RED},
        {1, TrafficLight::RED, TrafficLight::RED_YELLOW},
        {8, TrafficLight::RED, TrafficLight::GREEN},
        {2, TrafficLight::RED, TrafficLight::YELLOW}
    };
    byte _currentPhase = 0;

    int _maintenanceMode[2][3] = {
        {1, TrafficLight::YELLOW, TrafficLight::OFF},
        {1, TrafficLight::OFF, TrafficLight::YELLOW},
    };

    unsigned long _timer = 0;

public:

    const static int OFF;
    const static int NORMAL;
    const static int MAINTENANCE;

   /**
   * @brief Construct a new Traffic Light Controller object
   * 
   */
    TrafficLightController(TrafficLight *tl1, TrafficLight *tl2);
    void loop();
    void switchToMaintenance();
    void switchToNormal();
    void switchOff();
    int mode();

private:
    void _standardLoop();
    void _maintenanceLoop();
    int _getNextPhase(unsigned int phase);
    int _currentMode;
};

#endif