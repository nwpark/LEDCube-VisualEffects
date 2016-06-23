#include "Direction.h"

// ascii hex values for input keys (w, a, s, d, pgup, pgdn)
const byte Direction::FORWARD = 87, Direction::BACKWARD = 83, Direction::LEFT = 65,
           Direction::RIGHT = 68, Direction::UP = 33, Direction::DOWN = 34, Direction::STILL = 0;

// return a direction of opposite direction to the given one
byte Direction::opposite(byte givenDirection)
{
  // cant use switch statement cuz c++ sucks -.-
  if(givenDirection == FORWARD) return BACKWARD;
  if(givenDirection == BACKWARD) return FORWARD;
  if(givenDirection == LEFT) return RIGHT;
  if(givenDirection == RIGHT) return LEFT;
  if(givenDirection == UP) return DOWN;
  if(givenDirection == DOWN) return UP;
  return STILL;
} // opposite

// return the difference in the x plane after moving in the given
// direction
byte Direction::xDelta(byte givenDirection)
{
  if(givenDirection == LEFT) return -1;
  else if(givenDirection == RIGHT) return 1;
  else return 0;
} // xDelta

// return the difference in the y plane after moving in the given
// direction
byte Direction::yDelta(byte givenDirection)
{
  if(givenDirection == FORWARD) return 1;
  else if(givenDirection == BACKWARD) return -1;
  else return 0;
} // yDelta

// return the difference in the z plane after moving in the given
// direction
byte Direction::zDelta(byte givenDirection)
{
  if(givenDirection == UP) return 1;
  else if(givenDirection == DOWN) return -1;
  else return 0;
} // zDelta
