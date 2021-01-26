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
const int buttonPIN = 13;

/**
 * @brief Initialize stuff.
 * 
 */
void setup()
{
  // put your setup code here, to run once:
  pinMode(buttonPIN, INPUT_PULLUP);
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

  if (digitalRead(buttonPIN) == LOW)
  {
    if (tlControl.mode() == TrafficLightController::NORMAL)
    {
      tlControl.switchToMaintenance();
    }
    else if (tlControl.mode() == TrafficLightController::MAINTENANCE)
    {
      tlControl.switchToNormal();
    }
    while (digitalRead(buttonPIN) == LOW); // wait until button no longer pressed
  }

  tlControl.loop();
}