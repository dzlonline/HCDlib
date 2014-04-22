#include <HCD.h>

//Drones (as many as you like .. ish)
HCD drone0;
HCD drone1;

//Drone ID's (pick 4 random numbers)
unsigned char ID1[]={
  0x16,0x01,0x55,0x11};
unsigned char ID0[]={
  0x16,0x01,0x55,0x10};

// Payload data:
// THROTTLE,YAW,YAW_TRIM,PITCH,ROLL,PITCH_TRIM,ROLL_TRIM,FLY/RUN
// throttle 0-255
// pitch,roll,yaw 0-255 128=middle
// trims 64=center
// fly/run 0=fly 16=run

unsigned char payload0[]={
  0x05,0x80,0x40,0x80,0x80,0x40,0x40,0x00};
unsigned char payload1[]={
  0x00,0x80,0x40,0x80,0x80,0x40,0x40,0x00};

void setup()
{
  Serial.begin(19200);
  Serial.println("ON");
}

unsigned long timer=0;

void loop()
{
  if(Serial.available())
  {
    unsigned char c=Serial.read();

    switch(c)
    {
    case '0':
      if(drone0.inactive())
        drone0.bind(ID0);
      break;
    case '1':
      if(drone1.inactive())
        drone1.bind(ID1);
      break;
    case 'a':
      drone0.reconnect(ID0);
      break;
    case 'b':
      drone1.reconnect(ID1);
      break;
    case 'q':
      drone0.unbind();
      drone1.unbind();
      break;
    }
  }

  if(millis()>=timer)
  {
    timer+=20;
    drone0.update(0,0x80,0x40,0x80,0x80,0x40,0x40,0);    //-Method 1 (same order as payload)
    drone1.update(payload1);                             //-Method 2
  }
}
































