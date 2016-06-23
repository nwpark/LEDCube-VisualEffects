#ifndef Box_H
#define Box_H

#include <Arduino.h>
#include "Direction.h"
#include "CubeInterface.h"

class Box
{
  public:
    Box(byte initX, byte initY, byte initZ, byte initSize);
    ~Box();
    byte xOrigin, yOrigin, zOrigin, boxSize;
    void updateCube(CubeInterface *cube);
  private:
};

#endif
