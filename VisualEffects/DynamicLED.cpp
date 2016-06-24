#include "DynamicLED.h"

const byte DynamicLED::X_PLANE = 0, DynamicLED::Y_PLANE = 1, DynamicLED::Z_PLANE = 2;

DynamicLED::DynamicLED(byte initX, byte initY, byte initZ)
{
  xPos = targetX = initX;
  yPos = targetY = initY;
  zPos = targetZ = initZ;
  direction = Direction::STILL;
} // DynamicLED

// destructor
DynamicLED::~DynamicLED(){}

void DynamicLED::move()
{
  if(xPos != targetX)
    xPos += Direction::xDelta(direction);
  if(yPos != targetY)
    yPos += Direction::yDelta(direction);
  if(zPos != targetZ)
    zPos += Direction::zDelta(direction);
} // move

void DynamicLED::updateTargetPos(byte newX, byte newY, byte newZ)
{
  targetX = newX; targetY = newY; targetZ = newZ;
  
  if(xPos < targetX)
    direction = Direction::RIGHT;
  else if(xPos > targetX)
    direction = Direction::LEFT;
  else if(yPos < targetY)
    direction = Direction::FORWARD;
  else if(yPos > targetY)
    direction = Direction::BACKWARD;
  else if(zPos < targetZ)
    direction = Direction::UP;
  else if(zPos > targetZ)
    direction = Direction::DOWN;
} // updateTargetPos

void DynamicLED::updateTargetX(byte newX)
{
  targetX = newX;
  
  if(xPos < targetX)
    direction = Direction::RIGHT;
  else if(xPos > targetX)
    direction = Direction::LEFT;
} // updateTargetX

void DynamicLED::updateTargetY(byte newY)
{
  targetY = newY;

  if(yPos < targetY)
    direction = Direction::FORWARD;
  else if(yPos > targetY)
    direction = Direction::BACKWARD;
} // updateTargetY

void DynamicLED::updateTargetZ(byte newZ)
{
  targetZ = newZ;

  if(zPos < targetZ)
    direction = Direction::UP;
  else if(zPos > targetZ)
    direction = Direction::DOWN;
} // updateTargetZ

void DynamicLED::updateTarget(byte newCoord, byte plane)
{
  switch(plane)
  {
    case X_PLANE: this->updateTargetX(newCoord); break;
    case Y_PLANE: this->updateTargetY(newCoord); break;
    case Z_PLANE: this->updateTargetZ(newCoord); break;
  } // switch
} // updateTarget

boolean DynamicLED::atTarget()
{
  return xPos == targetX && yPos == targetY && zPos == targetZ;
} // atTarget

void DynamicLED::updateCube(CubeInterface *cube)
{
  if(xPos < 8 && yPos < 8 && zPos < 8
         && xPos >=0 && yPos >= 0 && zPos >=0)
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
