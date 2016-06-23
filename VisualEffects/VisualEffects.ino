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
  initPattern1();
  while(millis() < 10000)
    pattern1();

  initRain();
  while(millis() < 20000)
    rain();

  initPattern4();
  while(millis() < 30000)
    pattern4();

  initPattern3();
  while(millis() < 40000)
    pattern3();
} // loop

void initPattern4()
{
  cube->clearAll();
  for(byte i=0; i < 64; i++)
  {
    delete leds[i];
    leds[i] = NULL;
  } // for

  byte i=0;
  for(byte x=0; x < 8; x++)
    for(byte y=0; y < 8; y++)
    {
      leds[i] = new DynamicLED(x, y, (byte)random(0, 2)*7);
      leds[i]->updateCube(cube);
      i++;
    } // for
} // initPattern4

void pattern4()
{
  byte randIndex = (byte)random(0, 64);
  if(leds[randIndex]->zPos == 0)
    leds[randIndex]->targetZ = 7;
  else
    leds[randIndex]->targetZ = 0;

  moveAllToTarget(20);
  cube->wait(200);
} // pattern4

void initPattern3()
{
  cube->clearAll();
  for(byte i=0; i < 64; i++)
  {
    delete leds[i];
    leds[i] = NULL;
  } // for
  
  byte i=0;
  for(byte x=0; x < 8; x++)
    for(byte y=0; y < 8; y++)
    {
      leds[i] = new DynamicLED(x, y, (byte)random(1, 7));
      leds[i]->updateCube(cube);
      i++;
    } // for
} // initPattern1

void pattern3()
{
  for(int i=0; i < 63; i+=2)
  {
    leds[i]->targetZ = (byte)random(1, 7);
  } // for
  moveAllToTarget(60);
  cube->wait(500);
  
  for(int i=1; i < 64; i+=2)
  {
    leds[i]->targetZ = (byte)random(1, 7);
  } // for
  moveAllToTarget(60);
  cube->wait(500);
} // pattern3

void initRain()
{
  cube->clearAll();
  for(byte i=0; i < 64; i++)
  {
    delete leds[i];
    leds[i] = NULL;
  } // for
} // initRain

void rain()
{
  for(int i=0; i < 10; i++)
  {
    moveDynamicLEDS();
    if(leds[i] != NULL)
      delete leds[i];
    leds[i] = new DynamicLED((byte)random(0, 8), (byte)random(0, 8), 7);
    leds[i]->targetZ = 0;

    // uncomment this to double number of rain drops
//    if(leds[i+10] != NULL)
//      delete leds[i+10];
//    leds[i+10] = new DynamicLED((byte)random(0, 8), (byte)random(0, 8), 7);
//    leds[i+10]->targetZ = 0;

    updateCube();
    cube->wait(50);
  } // for
} // rain

void initPattern1()
{
  cube->clearAll();
  for(byte i=0; i < 64; i++)
  {
    delete leds[i];
    leds[i] = NULL;
  } // for
  
  byte i=0;
  for(byte x=0; x < 8; x++)
    for(byte z=0; z < 8; z++)
    {
      leds[i] = new DynamicLED(x, 0, z);
      leds[i]->updateCube(cube);
      i++;
    } // for
} // initPattern1

void pattern1()
{
  cube->wait(450);
  
  for(byte i=0; i < 64; i++)
    leds[i]->targetY = (byte)random(0, 8);
  moveAllToTarget(15);
  cube->wait(450);
  
  for(byte i=0; i < 64; i++)
    leds[i]->targetY = 7;
  moveAllToTarget(15);
  cube->wait(450);

  for(byte i=0; i < 64; i++)
    leds[i]->targetY = (byte)random(0, 8);
  moveAllToTarget(15);
  cube->wait(450);

  for(byte i=0; i < 64; i++)
    leds[i]->targetY = 0;
  moveAllToTarget(15);
} // pattern1

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

