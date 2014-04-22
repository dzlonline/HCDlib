//************************************************************************
//  HCD flying example
//  (C) DZL December2013
//
// Inputs:
// Throttle  analog 0
// Yaw       analog 1
// Pitch     analog 2
// Roll      analog 3
//
//************************************************************************

#include <HCD.h>

HCD drone0;

//Drone ID's (pick 4 random numbers)
unsigned char ID0[]={
  0x16,0x01,0x55,0x11};

void setup()
{
  Serial.begin(19200);
  Serial.println("Press 0 to bind to HCD");
}

unsigned long timer=0;

void loop()
{
  if(Serial.available())
  {
    unsigned char c=Serial.read();

    switch(c)
    {
    case '0':              //-Press zero to
      if(drone0.inactive())
        drone0.bind(ID0);
      break;
    }
  }

  if(millis()>=timer)
  {
    timer+=20;
    drone0.update(analogRead(0)/4,analogRead(1)/4,0x40,analogRead(2)/4,analogRead(3)/4,0x40,0x40,0);
  }
}
































