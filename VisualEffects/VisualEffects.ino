#include "CubeInterface.h"
#include "DynamicLED.h"
#include "Direction.h"
#include "Box.h"
#include "Sphere.h"

CubeInterface *cube;

DynamicLED *leds[64];
Box *box = NULL;
Sphere *sphere = NULL;

// used for sine wave pattern
float distFromCenter[8][8];
float theta;

long currentTime;

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
  initPattern7(DynamicLED::Y_PLANE);
  currentTime = millis();
  while(millis()-currentTime < 5000)
  {
    pattern7(DynamicLED::Y_PLANE);
    pattern7(DynamicLED::X_PLANE);
    pattern7(DynamicLED::Z_PLANE);
  } // while

  initRain();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    rain();

  initPattern4();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    pattern4();

  initSpiral();
  currentTime = millis();
  while(millis()-currentTime < 7000)
    // 1.5708, 3.1416, 4.7124
    spiral(0, 1);
  currentTime = millis();
  while(millis()-currentTime < 7000)
    // 1.5708, 3.1416, 4.7124
    spiral(1.5708, -1);

  initBoxGrowShrink();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    boxGrowShrink();

  initPattern1(DynamicLED::Y_PLANE);
  currentTime = millis();
  while(millis()-currentTime < 10000)
  {
    pattern1(DynamicLED::Y_PLANE);
    pattern1(DynamicLED::Y_PLANE);
    pattern1(DynamicLED::X_PLANE);
    pattern1(DynamicLED::X_PLANE);
  } // while

  initSineWave();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    sineWave();

  initPattern8(DynamicLED::Y_PLANE, 0);
  currentTime = millis();
  while(millis()-currentTime < 10000)
  {
    pattern8(DynamicLED::Y_PLANE, 7);
    pattern8(DynamicLED::Y_PLANE, 0);
    pattern8(DynamicLED::X_PLANE, 7);
    pattern8(DynamicLED::X_PLANE, 0);
  } // while

  initPattern3();
  currentTime = millis();
  while(millis()-currentTime < 10000)
    pattern3();

//  initSphere();
//  spherePattern();
} // loop

//=============================//PATTERN1//===========================//
void initPattern1(byte plane)
{
  reset();
  
  byte i=0;
  for(byte x=0; x < 8; x++)
    for(byte z=0; z < 8; z++)
    {
      if(plane == DynamicLED::X_PLANE) leds[i] = new DynamicLED(0, x, z);
      if(plane == DynamicLED::Y_PLANE) leds[i] = new DynamicLED(x, 0, z);
      if(plane == DynamicLED::Z_PLANE) leds[i] = new DynamicLED(x, z, 0);
      leds[i]->updateCube(cube);
      i++;
    } // for
} // initPattern1

void pattern1(byte plane)
{
  initPattern1(plane);
    
  pattern1PositionUpdater(-1, plane);
  pattern1PositionUpdater(7, plane);
  pattern1PositionUpdater(-1, plane);
  pattern1PositionUpdater(0, plane);
} // pattern1

void pattern1PositionUpdater(int newPosition, byte plane)
{
  cube->wait(200);
  for(byte i=0; i < 64; i++)
    if(newPosition == -1)
      leds[i]->updateTarget((byte)random(0, 8), plane);
    else
      leds[i]->updateTarget(newPosition, plane);
      
  moveAllToTarget(15);
  cube->wait(250);
} // pattern1PositionUpdater

//=============================//  RAIN  //===========================//
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

//=============================//PATTERN4//===========================//
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

//=============================//PATTERN3//===========================//
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

//=============================//SINE WAVE//===========================//
void initSineWave()
{
  reset();
  theta = 0;

  for(byte x=0; x < 8; x++)
    for(byte y=0; y < 8; y++)
    {
      distFromCenter[x][y]
        = (sqrt(sq((x < 4) ? (3.5-x) : (x-3.5)) 
                + sq((y < 4) ? (3.5-y) : (y-3.5)))) / 3.183;
    } // for
} // initSineWave

void sineWave()
{
  cube->clearAll();
  for(byte x=0; x < 8; x++)
    for(byte y=0; y < 8; y++)
    {
      byte z = (sin(distFromCenter[x][y] + theta) + 1) * 4;
      cube->light(x, y, z);
    } // for
    theta+=0.2;
    cube->wait(30);
} // sineWave

//=============================//BOX GROW//===========================//
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

//=============================//PATTERN7//===========================//
void initPattern7(byte plane)
{
  reset();
  
  byte i=0;
  for(byte x=0; x < 8; x++)
    for(byte z=0; z < 8; z++)
    {
      if(plane == DynamicLED::X_PLANE) leds[i] = new DynamicLED(0, x, z);
      if(plane == DynamicLED::Y_PLANE) leds[i] = new DynamicLED(x, 0, z);
      if(plane == DynamicLED::Z_PLANE) leds[i] = new DynamicLED(x, z, 0);
      leds[i]->updateCube(cube);
      i++;
    } // for

//  cube->wait(500);
} // initPattern7

void pattern7(byte plane)
{
  initPattern1(plane);
    
  for(byte i=0; i < 64; i++)
  {
    leds[i]->updateTarget(7, plane);
    //leds[63-i]->updateTarget(7, plane);
    moveDynamicLEDS();
    updateCube();
    cube->wait(8);
  } // for
      
  moveAllToTarget(8);

  for(byte i=0; i < 64; i++)
  {
    leds[i]->updateTarget(0, plane);
    moveDynamicLEDS();
    updateCube();
    cube->wait(8);
  } // for
      
  moveAllToTarget(8);
} // pattern7

//=============================//PATTERN8//===========================//
void initPattern8(byte plane, byte initCoord)
{
  reset();
  
  byte i=0;
  for(byte x=0; x < 8; x++)
    for(byte z=0; z < 8; z++)
    {
      if(plane == DynamicLED::X_PLANE) leds[i] = new DynamicLED(initCoord, x, z);
      if(plane == DynamicLED::Y_PLANE) leds[i] = new DynamicLED(x, initCoord, z);
      if(plane == DynamicLED::Z_PLANE) leds[i] = new DynamicLED(x, z, initCoord);
      leds[i]->updateCube(cube);
      i++;
    } // for
} // initPattern8

void pattern8(byte plane, byte targetCoord)
{
  initPattern8(plane, 7-targetCoord);
    
  for(int i=0; i < 64; i++)
  {
    byte index = (byte)random(0, 64);
    leds[index]->updateTarget(targetCoord, plane);

    moveDynamicLEDS();
    updateCube();
    cube->wait(10);
  } // while

  for(byte i=0; i < 32; i++)
  {
      leds[i]->updateTarget(targetCoord, plane);
      leds[63-i]->updateTarget(targetCoord, plane);
      moveDynamicLEDS();
      updateCube();
      cube->wait(10);
  } // for

  moveAllToTarget(15);
} // pattern8

//=============================// SPIRAL //===========================//
void initSpiral()
{
  reset();
  theta = 0;
} // initSpiral

void spiral(float offset, int direction)
{
  for(byte i=0; i < 16; i++)
  {
    if(leds[i] != NULL)
    {
      delete leds[i];
      leds[i] = NULL;
    } // if
    if(leds[i+32] != NULL)
    {
      delete leds[i+32];
      leds[i+32] = NULL;
    } // if
    
    byte x1 = (byte)(4 + (4 * cos(direction*theta + offset)));
    byte y1 = (byte)(4 + (4 * sin(direction*theta + offset)));
    leds[i] = new DynamicLED(x1, y1, 0);
    leds[i]->updateTargetPos(x1, y1, 7);
    byte x2 = (byte)(4 + (3 * cos(theta)));
    byte y2 = (byte)(4 + (3 * sin(theta)));
    leds[i+32] = new DynamicLED(x2, y2, 0);
    leds[i+32]->updateTargetPos(x2, y2, 7);

    updateCube();
    cube->wait(20);
    // 0.4833, 0.6283
    theta += 0.2094;

    if(i % 2 == 0)
      moveDynamicLEDS();
  } // for
} // spiral

//=============================// SPHERE //===========================//
void initSphere()
{
  reset();
  
  sphere = new Sphere(1.5, 1.5, 1.5, 1);
} // initSphere

void spherePattern()
{
//  sphere->updateCube(cube);
//  cube->wait(5000);
  for(int i=0; i < 4; i++)
  {
    cube->clearAll();
    sphere->yOrigin++;
    sphere->updateCube(cube);
    cube->wait(50);
  } // for
  for(int i=0; i < 4; i++)
  {
    cube->clearAll();
    sphere->yOrigin--;
    sphere->updateCube(cube);
    cube->wait(50);
  } // for
} // spherePattern

//=========================//GENERAL METHODS//=======================//
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
  if(sphere != NULL)
  {
    delete sphere;
    sphere = NULL;
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

