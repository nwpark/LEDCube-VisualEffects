#include "Sphere.h"

Sphere::Sphere(float initX, float initY, float initZ, byte initSize)
{
  xOrigin = initX;
  yOrigin = initY;
  zOrigin = initZ;
  sphereSize = initSize;
} // Sphere

// destructor
Sphere::~Sphere(){}

void Sphere::updateCube(CubeInterface *cube)
{
  for(byte x=0; x < 8; x++)
    for(byte y=0; y < 8; y++)
      for(byte z=0; z < 8; z++)
        if((byte)sqrt(sq(abs(xOrigin-x)) 
                      + sq(abs(yOrigin-y))
                      + sq(abs(zOrigin-z))) <= sphereSize)
          cube->light(x, y, z);
} // updateCube
