#ifndef Sphere_H
#define Sphere_H

#include <Arduino.h>
#include "Direction.h"
#include "CubeInterface.h"

class Sphere
{
  public:
    Sphere(float initX, float initY, float initZ, byte initSize);
    ~Sphere();
    float xOrigin, yOrigin, zOrigin;
    byte sphereSize;
    void updateCube(CubeInterface *cube);
  private:
};

#endif
