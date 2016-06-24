#include "Box.h"

Box::Box(byte initX, byte initY, byte initZ, byte initSize)
{
  xOrigin = initX;
  yOrigin = initY;
  zOrigin = initZ;
  boxSize = initSize;
} // Box

// destructor
Box::~Box(){}

void Box::updateCube(CubeInterface *cube)
{
  for(int i=0; i < boxSize; i++)
  {
    cube->light(abs(xOrigin - i), yOrigin,                zOrigin);
    cube->light(abs(xOrigin - i), abs(yOrigin - boxSize), zOrigin);
    cube->light(abs(xOrigin - i), yOrigin,                abs(zOrigin - boxSize));
    cube->light(abs(xOrigin - i), abs(yOrigin - boxSize), abs(zOrigin - boxSize));

    cube->light(xOrigin,                abs(yOrigin - i), zOrigin);
    cube->light(abs(xOrigin - boxSize), abs(yOrigin - i), zOrigin);
    cube->light(xOrigin,                abs(yOrigin - i), abs(zOrigin - boxSize));
    cube->light(abs(xOrigin - boxSize), abs(yOrigin - i), abs(zOrigin - boxSize));

    cube->light(xOrigin,                yOrigin,                abs(zOrigin - i));
    cube->light(abs(xOrigin - boxSize), yOrigin,                abs(zOrigin - i));
    cube->light(xOrigin,                abs(yOrigin - boxSize), abs(zOrigin - i));
    cube->light(abs(xOrigin - boxSize), abs(yOrigin - boxSize), abs(zOrigin - i));
  } // for
  
  cube->light(abs(xOrigin - boxSize), abs(yOrigin - boxSize), abs(zOrigin - boxSize));
} // updateCube
