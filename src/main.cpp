#include <Arduino.h>
#include <TrafficLight.h>
#include <TrafficLightController.h>

/**
 * @brief Instantiate two traffic light objects and provide PIN numbers.
 * 
 */
TrafficLight ampel1 = TrafficLight(4, 5, 6);
TrafficLight ampel2 = TrafficLight(8, 9, 10);
TrafficLightController tlControl(&ampel1, &ampel2);

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
  Serial.begin(9600);
  tlControl.switchToNormal();
}

/**
 * @brief Main loop.
 * 
 */
void loop()
{
  // put your main code here, to run repeatedly:

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

  tlControl.loop();
}