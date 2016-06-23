#include "CubeInterface.h"
#include "DynamicLED.h"
#include "Direction.h"

CubeInterface *cube;

DynamicLED *leds[64];

void setup()
{
  cube = new CubeInterface(1);
  
  for(byte i=0; i < 64; i++)
  {
    leds[i] = NULL;
  } // for
} // setup

void loop()
{
//  initPattern1();
//  while(millis() < 10000)
//    pattern1();
//  endPattern1();
  pattern2();
} // loop

void pattern2()
{
  for(int i=0; i < 10; i++)
  {
    moveDynamicLEDS();
    if(leds[i] != NULL)
      delete leds[i];
    leds[i] = new DynamicLED((byte)random(0, 8), (byte)random(0, 8), 7);
    leds[i]->targetZ = 0;

    updateCube();
    cube->wait(50);
  } // for
} // pattern2

void moveAllToTarget(int delay)
{
  for(byte moveCount=0; moveCount < 8; moveCount++)
  {
    moveDynamicLEDS();
    updateCube();
    cube->wait(delay);
  } // for
} // moveAllToTarget

void moveDynamicLEDS()
{
  for(byte i=0; i < 64; i++)
    if(leds[i] != NULL)
      leds[i]->move();
} // moveDynamicLEDS

void updateCube()
{
  cube->clearAll();
  for(byte i=0; i < 64; i++)
    if(leds[i] != NULL)
      leds[i]->updateCube(cube);
} // updateCube

