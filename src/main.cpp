#include <Arduino.h>
#include <TrafficLight.h>

/**
 * @brief Instantiate two traffic light objects and provide PIN numbers.
 * 
 */
TrafficLight ampel1 = TrafficLight(4,5,6);
TrafficLight ampel2 = TrafficLight(8,9,10);

unsigned long timer = 0;
byte phase = 0;

/**
 * @brief Define PIN for button.
 * 
 */
const int buttonPIN = 13;

/**
 * @brief Initialize stuff.
 * 
 */
void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPIN, INPUT_PULLUP);
}

/**
 * @brief Main loop.
 * 
 */
void loop() {
  // put your main code here, to run repeatedly:

}