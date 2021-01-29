/**
 * @file   example.cpp
 * @author Thomas Schnuecker (thomas@schnuecker.de)
 * @brief  Example to show how to use traffic light controller to control
 * a set of traffic lights.
 * 
 * @version 0.1
 * @date 2021-01-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <TrafficLight.h>
#include <TrafficLightController.h>

/**
 * @brief Instantiate two traffic light objects and provide PIN numbers.
 * 
 */
TrafficLight tl1(4,5,6);  
TrafficLight tl2(8,9,10);
TrafficLightController tlControl(&tl1, &tl2);

/**
 * @brief Define PIN for button.
 * 
 */
const int yellowButtonPIN = 13;
const int redButtonPIN = 12;

/**
 * @brief Initialize stuff.
 * 
 */
void setup()
{
  // put your setup code here, to run once:
  pinMode(yellowButtonPIN, INPUT_PULLUP);
  pinMode(redButtonPIN, INPUT_PULLUP);
  tlControl.switchToNormal();
}

/**
 * @brief Main loop.
 * 
 */
void loop()
{
  // If YELLOW button is pressed, switch between maintenance and 
  // normal operations.
  if (digitalRead(yellowButtonPIN) == LOW)
  {
    if (tlControl.mode() == TrafficLightController::NORMAL)
    {
      tlControl.switchToMaintenance();
    }
    else if (tlControl.mode() == TrafficLightController::MAINTENANCE)
    {
      tlControl.switchToNormal();
    }
    while (digitalRead(yellowButtonPIN) == LOW); // wait until button no longer pressed
  }

  // If RED button is pressed, switch traffic lights on/off.
  if (digitalRead(redButtonPIN) == LOW)
  {
    if (tlControl.mode() != TrafficLightController::OFF)
    {
      tlControl.switchOff();
    }
    else
    {
      tlControl.switchToNormal();
    }
    while (digitalRead(redButtonPIN) == LOW); // wait until button no longer pressed
  }

  // Run TrafficLightController loop. This is needed for the controller to work.
  // The controller will check on millis() and length of traffic light phases
  // to switch on/off the lights.
  tlControl.loop();
}