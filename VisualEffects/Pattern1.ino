void initPattern1()
{
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

void endPattern1()
{
  cube->clearAll();
  for(byte i=0; i < 64; i++)
  {
    delete leds[i];
    leds[i] = NULL;
  } // for
} // endPattern1
