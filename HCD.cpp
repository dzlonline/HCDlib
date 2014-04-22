//************************************************************************
//	Communicarion library for "Hamster Cage Drones"
//	(C) Dzl December 2013
//  http://dzlsevilgeniuslair.blogspot.dk/
//************************************************************************

#include "bk2421.h"
#include "HCD.h"

HCD::HCD()
{
  state=HS_UNINITIALIZED;
  initialized=0;
}

void HCD::bind(unsigned char *ID)
{
  for(unsigned char i=0;i<4;i++)
    noteID[i]=ID[i];
  state=HS_CONNECT;
}

unsigned char HCD::inactive()
{
  if(state==HS_CONNECTED)
    return 0;
  return 1;
}

void HCD::unbind()
{
  if(state!=HS_UNINITIALIZED)
    state=HS_INITIALIZED;
}

void HCD::reconnect(unsigned char *ID)
{
  for(unsigned char i=0;i<4;i++)
    noteID[i]=ID[i];
  state=HS_CONNECTED;
}

void HCD::update(unsigned char throttle,unsigned char yaw,unsigned char yawtrim,unsigned char pitch,unsigned char roll,unsigned char pitchtrim,unsigned char rolltrim,unsigned char flyrun)
{
  unsigned char payload[8];
  payload[0]=throttle;
  payload[1]=yaw;
  payload[2]=yawtrim;
  payload[3]=pitch;
  payload[4]=roll;
  payload[5]=pitchtrim;
  payload[6]=rolltrim;
  payload[7]=flyrun;
  update(payload);

}

void HCD::update(unsigned char *payload)
{
  unsigned char c=0;

  switch(state)
  {
  case HS_CONNECT:

    radio.offline();

    radio.txbuf[0]=0x25;
    radio.txbuf[1]=0x3C;
    radio.sendBuffer(2);      //-Chan

    radio.block(baseAddress);
    radio.block(flushTX);

    radio.txbuf[0]=0xA0;
    radio.txbuf[1]=noteID[0];
    radio.txbuf[2]=noteID[1];
    radio.txbuf[3]=noteID[2];
    radio.txbuf[4]=noteID[3];
    radio.txbuf[5]=0x56;
    radio.txbuf[6]=0xaa;
    radio.txbuf[7]=0x40;
    radio.txbuf[8]=0x00;
    radio.sendBuffer(9);      //-tx data
    radio.block(PTX);
    radio.online();

    while(!c)
      c=radio.getStatus();
    radio.clrStatus();

    if(c&0x10)  //MRT
    {
      state=HS_UNINITIALIZED;
    }

    if(c&0x20)  //ACK
    {
      //        Serial.println("ACK");
      state=HS_CONNECTED;
    }
    break;

  case HS_CONNECTED:

    radio.offline();

    radio.txbuf[0]=0x25;
    radio.txbuf[1]=0x4B;
    radio.sendBuffer(2);      //-Chan


    radio.txbuf[0]=0x2a;
    radio.txbuf[1]=noteID[0];
    radio.txbuf[2]=noteID[1];
    radio.txbuf[3]=noteID[2];
    radio.txbuf[4]=noteID[3];
    radio.txbuf[5]=0xC1;
    radio.sendBuffer(6);      //-tx data

    radio.txbuf[0]=0x30;
    radio.txbuf[1]=noteID[0];
    radio.txbuf[2]=noteID[1];
    radio.txbuf[3]=noteID[2];
    radio.txbuf[4]=noteID[3];
    radio.txbuf[5]=0xC1;
    radio.sendBuffer(6);      //-tx data

    radio.online();

    radio.block(flushTX);

    radio.txbuf[0]=0xA0;
    radio.txbuf[1]=payload[0];
    radio.txbuf[2]=payload[1];
    radio.txbuf[3]=payload[2];
    radio.txbuf[4]=payload[3];
    radio.txbuf[5]=payload[4];
    radio.txbuf[6]=payload[5];
    radio.txbuf[7]=payload[6];
    radio.txbuf[8]=payload[7];
    radio.sendBuffer(9);      //-tx data

    radio.txbuf[0]=0x20;
    radio.txbuf[1]=0x7A;  //-TX
    radio.sendBuffer(2);

    while(!c)
      c=radio.getStatus();
    radio.clrStatus();


    if(c&0x10)  //MRT
    {
      //        Serial.println("MRT");
    }

    if(c&0x20)  //ACK
    {
      //        Serial.println("ACK");
    }

    break;

  }
}



