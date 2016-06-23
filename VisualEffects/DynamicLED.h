#ifndef DynamicLED_H
#define DynamicLED_H

#include <Arduino.h>
#include "Direction.h"
#include "CubeInterface.h"

class DynamicLED
{
  public:
    DynamicLED(byte initX, byte initY, byte initZ);
    ~DynamicLED();
    byte xPos, yPos, zPos, direction;
    byte targetX, targetY, targetZ;
    void move();
    void updateTargetPos(byte newX, byte newY, byte newZ);
    void updateTargetX(byte newX);
    void updateTargetY(byte newY);
    void updateTargetZ(byte newZ);
    void updateCube(CubeInterface *cube);
    byte smartDirectionChange();
  private:
};

#endif
