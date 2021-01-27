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

int program[9][3] = {
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
  tlControl.setProgram(program);
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