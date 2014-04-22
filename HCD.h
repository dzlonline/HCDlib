//************************************************************************
//	Communicarion library for "Hamster Cage Drones"
//	(C) Dzl December 2013
//  http://dzlsevilgeniuslair.blogspot.dk/
//************************************************************************

#ifndef _HCD
#define _HCD
#include "bk2421.h"

extern BK2421 radio;

#define HS_UNINITIALIZED 0
#define HS_INITIALIZED 1
#define HS_CONNECT 2
#define HS_CONNECTED 3

class HCD
{
private:
  unsigned char noteID[4];
  unsigned char state;
  unsigned char initialized;
public:
  HCD();
  void bind(unsigned char *ID);
  void unbind();
  void reconnect(unsigned char *ID);
  unsigned char inactive();
  void update(unsigned char throttle,unsigned char yaw,unsigned char yawtrim,unsigned char pitch,unsigned char roll,unsigned char pitchtrim,unsigned char rolltrim,unsigned char flyrun);
  void update(unsigned char *payload);
};
#endif




