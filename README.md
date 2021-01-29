# TrafficLight

This is an *Arduino* library to control a bunch of colored LEDs to make up a traffic light.
There are also *frizzing* and GBR files for the traffic lights that are ready to use to order 
traffic light PCBs. The traffic light controller *frizzing* file ist not yet finished.

The current version allows to control two traffic lights each consisting of one red,
one yellow and one green LED. There are two "hardcoded" traffic light control programs 
between you can switch:

1. NORMAL
2. MAINTENANCE (yellow blink of all traffic lights)

## Traffic Light Control States

You can set traffic light control states on the controller
to run a specific program of light phases.
### TrafficLightControl::NORMAL state

In TrafficLightControl::NORMAL state, the following program is run on the
two traffic lights:

| Traffic Light 1 | Traffic Light 2 | Duration |
|-----------------|-----------------|----------|
| RED             | RED             | 2s       |
| RED_YELLOW      | RED             | 1s       |
| GREEN           | RED             | 8s       |
| YELLOW          | RED             | 2s       |
| RED             | RED             | 2s       |
| RED             | RED_YELLOW      | 2s       |
| RED             | GREEN           | 8s       |
| RED             | YELLOW          | 1s       |
| RED             | RED             | 2s       |

### TrafficLightControl::MAINTENANCE state

In TrafficLightControl::MAINTENANCE state, all traffic lights will blink yellow.