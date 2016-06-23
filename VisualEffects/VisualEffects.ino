#include "CubeInterface.h"
#include "DynamicLED.h"
#include "Direction.h"

CubeInterface *cube;

DynamicLED *leds[64];

void setup()
{
  cube = new CubeInterface(1);
} // setup

void loop()
{
  initPattern1();
  while(millis() < 10000)
    pattern1();
  endPattern1();
} // loop

void moveDynamicLEDS()
{
  for(byte moveCount=0; moveCount < 8; moveCount++)
  {
    cube->clearAll();
    for(byte i=0; i < 64; i++)
      leds[i]->updateCube(cube);
    cube->wait(15);
    for(byte i=0; i < 64; i++)
      leds[i]->move();
  } // for
} // moveDynamicLEDS

