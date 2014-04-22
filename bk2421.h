//************************************************************************
//	Quick and dirty BK2421 2.4GHz tranceiver chip library
//	(C) Dzl December 2013
//  http://dzlsevilgeniuslair.blogspot.dk/
//************************************************************************

// Connections:

// BK2421:     Arduino:

// CE          PIN 8
// CSN         PIN 10
// SCK         PIN 13
// MOSI        PIN 11
// MISO        PIN 12


#ifndef _BK2421
#define _BK2421

#include <arduino.h>
#include "blocks.h"

#define SET(x,y) (x |=(1<<y))					//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+


class BK2421
{
public:
  unsigned char txbuf[256];
  unsigned char rxbuf[256];

  BK2421()
  {
    SET(PORTB,2);
    SET(DDRB,2);      //SS=output
    CLR(PORTB,0);
    SET(DDRB,0);      //SE=output
    SET(DDRB,5);      //SCK
    SET(DDRB,3);      //MOSI
    SPCR=0b01010011;  //Master

	for(unsigned long i=0;i<800000;i++)
		asm("nop");
    block(initBlock);
	for(unsigned long i=0;i<800000;i++)
		asm("nop");
    online();
  }

  void offline()
  {
  	asm("nop");
  	asm("nop");
    CLR(PORTB,0);        //-CLR CE
  	asm("nop");
  	asm("nop");
  }

  void online()
  {
  	asm("nop");
  	asm("nop");
    SET(PORTB,0);        //-SET CE
  	asm("nop");
  	asm("nop");
  }

  void sendBuffer(unsigned char n)
  {
    unsigned char rxptr=0;
  	asm("nop");
  	asm("nop");
    CLR(PORTB,2);
  	asm("nop");
  	asm("nop");

    for(unsigned char i=0;i<n;i++)
    {
      SET(SPSR,SPIF);
      SPDR=txbuf[i];
      while(!CHK(SPSR,SPIF))
        asm("nop");
      rxbuf[rxptr++]=SPDR;
    }
  	asm("nop");
  	asm("nop");
    SET(PORTB,2);
  	asm("nop");
  	asm("nop");
  }

  void block(const uint8_t PROGMEM *p)
  {
    unsigned char rxptr=0;
    unsigned char len=pgm_read_byte(&p[0]);
    unsigned char adr=1;
    while(len)
    {
      CLR(PORTB,2);
	  asm("nop");
  	  asm("nop");
      rxptr=0;
      for(unsigned char i=0;i<len;i++)
      {
        unsigned char b=pgm_read_byte(&p[adr++]);

        SET(SPSR,SPIF);
        SPDR=b;
        while(!CHK(SPSR,SPIF))
          asm("nop");
        rxbuf[rxptr++]=SPDR;
      }

  	  asm("nop");
  	  asm("nop");
      SET(PORTB,2);
      len=pgm_read_byte(&p[adr++]);
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
    }
  }

  unsigned char getStatus()
  {
    txbuf[0]=0x00;
    txbuf[1]=0xff;
    sendBuffer(2);     //-Read status
    return rxbuf[0];  //-Get status
  }

  void clrStatus()
  {
    txbuf[0]=0x27;
    txbuf[1]=0x70;
    sendBuffer(2);    //-Clear status
  }

};

#endif
