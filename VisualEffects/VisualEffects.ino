#include "CubeInterface.h"
#include "DynamicLED.h"
#include "Direction.h"
#include "Box.h"

CubeInterface *cube;

DynamicLED *leds[64];
Box *box;

float distFromCenter[8][8];
float offset;

long currentTime;

void setup()
{
  cube = new CubeInterface(1);
  
  for(byte i=0; i < 64; i++)
  {
    leds[i] = NULL;
  } // for

  initBoxGrowShrink();
} // setup

void loop()
{
  initPattern1();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    pattern1();

  initRain();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    rain();

  initPattern4();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    pattern4();

  initPattern3();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    pattern3();

  initSineWave();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    sineWave();

  initBoxGrowShrink();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    boxGrowShrink();
} // loop

void initBoxGrowShrink()
{
  reset();

  box = new Box(0, 0, 0, 7);
} // initBoxGrowShrink

void boxGrowShrink()
{
  box->xOrigin = (byte)random(0, 2)*7;
  box->yOrigin = (byte)random(0, 2)*7;
  box->zOrigin = (byte)random(0, 2)*7;

  for(byte i=0; i < 6; i++)
  {
    box->updateCube(cube);
    box->boxSize--;
    cube->wait(50);
    cube->clearAll();
  } // for
  for(byte i=0; i < 6; i++)
  {
    box->updateCube(cube);
    box->boxSize++;
    cube->wait(50);
    cube->clearAll();
  } // for
} // boxGrowShrink

void initSineWave()
{
  reset();
  offset = 0;

  for(byte x=0; x < 8; x++)
    for(byte y=0; y < 8; y++)
    {
      distFromCenter[x][y]
        = ((sqrt(sq((x < 4) ? (3.5-x) : (x-3.5)) + sq((y < 4) ? (3.5-y) : (y-3.5))))) / 3.183;
    } // for
} // initSineWave

void sineWave()
{
  cube->clearAll();
  for(byte x=0; x < 8; x++)
    for(byte y=0; y < 8; y++)
    {
      byte z = (sin(distFromCenter[x][y] + offset) + 1) * 4;
      cube->light(x, y, z);
    } // for
    offset+=0.2;
    cube->wait(30);
} // sineWave

void initPattern4()
{
  reset();

  byte i=0;
  for(byte x=0; x < 8; x++)
    for(byte y=0; y < 8; y++)
    {
      leds[i] = new DynamicLED(x, y, (byte)(random(0, 2)*7));
      leds[i]->updateCube(cube);
      i++;
    } // for
} // initPattern4

void pattern4()
{
  byte randIndex = (byte)random(0, 64);
  if(leds[randIndex]->zPos == 0)
    leds[randIndex]->updateTargetZ(7);
  else
    leds[randIndex]->updateTargetZ(0);

  moveAllToTarget(20);
  cube->wait(200);
} // pattern4

void initPattern3()
{
  reset();
  
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
    leds[i]->updateTargetZ((byte)random(1, 7));
  } // for
  moveAllToTarget(60);
  cube->wait(500);
  
  for(int i=1; i < 64; i+=2)
  {
    leds[i]->updateTargetZ((byte)random(1, 7));
  } // for
  moveAllToTarget(60);
  cube->wait(500);
} // pattern3

void initRain()
{
  reset();
} // initRain

void rain()
{
  for(int i=0; i < 10; i++)
  {
    moveDynamicLEDS();
    if(leds[i] != NULL)
      delete leds[i];
    leds[i] = new DynamicLED((byte)random(0, 8), (byte)random(0, 8), 7);
    leds[i]->updateTargetZ(0);

    // uncomment this to double number of rain drops
//    if(leds[i+10] != NULL)
//      delete leds[i+10];
//    leds[i+10] = new DynamicLED((byte)random(0, 8), (byte)random(0, 8), 7);
//    leds[i+10]->updateTargetZ(0);

    updateCube();
    cube->wait(50);
  } // for
} // rain

void initPattern1()
{
  reset();
  
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
    leds[i]->updateTargetY((byte)random(0, 8));
  moveAllToTarget(15);
  cube->wait(450);
  
  for(byte i=0; i < 64; i++)
    leds[i]->updateTargetY(7);
  moveAllToTarget(15);
  cube->wait(450);

  for(byte i=0; i < 64; i++)
    leds[i]->updateTargetY((byte)random(0, 8));
  moveAllToTarget(15);
  cube->wait(450);

  for(byte i=0; i < 64; i++)
    leds[i]->updateTargetY(0);
  moveAllToTarget(15);
} // pattern1

void reset()
{
  cube->clearAll();
  
  for(byte i=0; i < 64; i++)
    if(leds[i] != NULL)
    {
      delete leds[i];
      leds[i] = NULL;
    } // for

  if(box != NULL)
  {
    delete box;
    box = NULL;
  } // if
} // resetArray

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

