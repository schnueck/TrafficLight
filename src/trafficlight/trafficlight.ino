/**
 * @file   main.cpp
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
TrafficLight tl1(A2,A1,A0);
TrafficLight tl2(A5,A4,A3);
TrafficLight tl3(6,5,4);  
TrafficLight tl4(10,9,8);
TrafficLightController tlControl(&tl1, &tl2);

/**
 * @brief Define PIN for button.
 * 
 */
const int yellowButtonPIN = 7;

/**
 * @brief Initialize stuff.
 * 
 */
void setup()
{
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(yellowButtonPIN, INPUT_PULLUP);
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
      Serial.println("Switching to mainenance mode.");
      tlControl.switchToMaintenance();
    }
    else if (tlControl.mode() == TrafficLightController::MAINTENANCE)
    {
      Serial.println("Switching to normal mode.");
      tlControl.switchToNormal();
    }
    while (digitalRead(yellowButtonPIN) == LOW); // wait until button no longer pressed
  }

  // Run TrafficLightController loop. This is needed for the controller to work.
  // The controller will check on millis() and length of traffic light phases
  // to switch on/off the lights.
  tlControl.loop();
}
