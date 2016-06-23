#ifndef Direction_H
#define Direction_H

#include <Arduino.h>
#include "DynamicLED.h"

class Direction
{
  public:
    static const byte FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN, STILL;
    static byte opposite(byte givenDirection);
    static byte xDelta(byte givenDirection);
    static byte yDelta(byte givenDirection);
    static byte zDelta(byte givenDirection);
}; // class Direction

#endif
