#include "DynamicLED.h"

byte xPos, yPos, zPos, direction;
byte targetX, targetY, targetZ;

DynamicLED::DynamicLED(byte initX, byte initY, byte initZ, byte initDirection)
{
  xPos = targetX = initX;
  yPos = targetY = initY;
  zPos = targetZ = initZ;
  direction = initDirection;
} // DynamicLED

void DynamicLED::move()
{
  direction = smartDirectionChange();
  if(xPos != targetX)
    xPos += Direction::xDelta(direction);
  if(yPos != targetY)
    yPos += Direction::yDelta(direction);
  if(zPos != targetZ)
    zPos += Direction::zDelta(direction);
} // move

void DynamicLED::updateCube(CubeInterface *cube)
{
  cube->light(xPos, yPos, zPos);
} // updateCube

byte DynamicLED::smartDirectionChange()
{
  if(xPos < targetX)
    return Direction::RIGHT;
  else if(xPos > targetX)
    return Direction::LEFT;
  else if(yPos < targetY)
    return Direction::FORWARD;
  else if(yPos > targetY)
    return Direction::BACKWARD;
  else if(zPos < targetZ)
    return Direction::UP;
  else if(zPos > targetZ)
    return Direction::DOWN;
} // smartDirectionChange
