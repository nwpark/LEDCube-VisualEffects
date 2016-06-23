void initPattern1()
{
  byte i=0;
    for(byte x=0; x < 8; x++)
      for(byte z=0; z < 8; z++)
      {
        leds[i] = new DynamicLED(x, 0, z, Direction::FORWARD);
        leds[i]->updateCube(cube);
        i++;
      } // for
} // initPattern1

void pattern1()
{
  cube->wait(450);
  
  for(byte i=0; i < 64; i++)
    leds[i]->targetY = (byte)random(0, 8);
  moveDynamicLEDS();
  cube->wait(450);
  
  // cant use for each loop in c++98 mode fml
  for(byte i=0; i < 64; i++)
    leds[i]->targetY = 7;
  moveDynamicLEDS();
  cube->wait(450);

  for(byte i=0; i < 64; i++)
    leds[i]->targetY = (byte)random(0, 8);
  moveDynamicLEDS();
  cube->wait(450);

  for(byte i=0; i < 64; i++)
    leds[i]->targetY = 0;
  moveDynamicLEDS();
} // pattern1

void endPattern1()
{
  cube->clearAll();
  for(byte i=0; i < 64; i++)
    delete leds[i];
} // endPattern1
