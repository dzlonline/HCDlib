#ifndef _BLOCKS
#define _BLOCKS

//-Default registers for Hamster Cage Drone

const uint8_t PROGMEM initBlock[]=
{
  2,0X20,0X0A,						//-Power up, receive mode, enable CRC
  2,0X21,0X3F,                      //-Auto ACK all pipes
  2,0X22,0X3F,                      //-Enable all pipes
  2,0X23,0X03,                      //-5 bytes data length
  2,0X24,0X1A,                      //-500µS retransmit rate, 10 times
  2,0X25,0X3C,                      //-Base RF chan (for binding to quadrotor)
  //    2,0X25,0X02,                //-payload chan
  //    2,0X25,0X0b,                //-payload chan
  //    2,0X25,0X00,                //-payload chan
  2,0X26,0X07,                      //-Max RF power ~3mW
  2,0X27,0X07,                      //-Clear status register
  2,0X28,0X00,                      //-Write to packet counter ??
  2,0X29,0X00,                      //-Write to carrier detect ??
  2,0X2C,0XC3,                      //-Pipe 2 LSB address
  2,0X2D,0XC4,                      //-Pipe 3 LSB address
  2,0X2E,0XC5,                      //-Pipe 4 LSB address
  2,0X2F,0XC6,                      //-Pipe 5 LSB address
  2,0X31,0X08,                      //-8 bytes in pipe 0 payload data
  2,0X32,0X08,                      //-8 bytes in pipe 1 payload data
  2,0X33,0X08,                      //-8 bytes in pipe 2 payload data
  2,0X34,0X08,                      //-8 bytes in pipe 3 payload data
  2,0X35,0X08,                      //-8 bytes in pipe 4 payload data
  2,0X36,0X08,                      //-8 bytes in pipe 5 payload data
  2,0X37,0X00,                      //-Write to FIFO status ??
  2,0X3C,0X3F,                      //-Enable variable payload length for all pipes
  2,0X1D,0X00,                      //-Read Feature register
  2,0X50,0X73,                      //-ACTIVATE: R_RX_PL_WID, W_ACK_PAYLOAD, W_TX_PAYLOAD_NOACK
  2,0X3C,0X3F,						//-Enable variable payload length for all pipes (again)
  2,0X3D,0X07,						//-Enable features
  2,0X1D,0X00,						//-Read features ??
  6,0X2A,0X16,0X01,0X55,0X11,0XC1,	//-Set network RX address (Specific to this handset)
  6,0X30,0X16,0X01,0X55,0X11,0XC1,	//-Set network TX address (Specific to this handset)
  2,0X07,0X00,						//-Read status

  2,0X50,0X53,						//-Select register bank 1
  5,0X20,0X40,0X4B,0X01,0XE2,		//-As in datasheet example
  5,0X21,0XC0,0X4B,0X00,0X00,		//-As in datasheet example
  5,0X22,0XD0,0XFC,0X8C,0X02,		//-As in datasheet example
  5,0X23,0X99,0X00,0X39,0X21,		//-As in datasheet example
  5,0X24,0XD9,0X96,0X82,0X1B,		//-As in datasheet example
  5,0X25,0X24,0X06,0X7F,0XA6,		//-As in datasheet example
  5,0X2C,0X00,0X12,0X73,0X00,		//-As in datasheet example
  5,0X2D,0X46,0XB4,0X80,0X00,		//-As in datasheet example
  5,0X24,0XDF,0X96,0X82,0X1B,		//-As in datasheet example
  5,0X24,0XD9,0X96,0X82,0X1B,		//-As in datasheet example
  2,0X07,0X00,                      //-Read status
  2,0X50,0X53,						//-Select register bank 1
  2,0x20,0x0b,						//-PRX mode
  2,0X27,0X7F,

  //6,0X2A,0X16,0X01,0X55,0X11,0XC1, //TX0
  //6,0X30,0X16,0X01,0X55,0X11,0XC1, //TX0
  //6,0X2A,0X6a,0X0d,0X55,0X11,0XC1, //TX0
  //6,0X30,0X6a,0X0d,0X55,0X11,0XC1, //TX0

  6,0X2A,0X65,0X65,0X65,0X65,0X65,
  6,0X30,0X65,0X65,0X65,0X65,0X65,

  //  2,0X00,0X3C,

  //6,0X00,0X16,0X01,0X55,0X11,0XC1,
  //6,0X30,0X16,0X01,0X55,0X11,0XC1,
  //6,0X00,0X16,0X01,0X55,0X11,0XC1,
  //6,0X30,0X16,0X01,0X55,0X11,0XC1,

  1,0XE1,							//-Flush TX
  1,0XE2,							//-Flush RX
  0
};

const uint8_t PROGMEM baseAddress[]=
{
  6,0X2A,0X65,0X65,0X65,0X65,0X65,
  6,0X30,0X65,0X65,0X65,0X65,0X65,
  0
};


const uint8_t PROGMEM readFIFO[]=
{
  9,0x61,0,0,0,0,0,0,0,0,
  0
};

const uint8_t PROGMEM flushRX[]=
{
  1,0xE2,
  0
};

const uint8_t PROGMEM flushTX[]=
{
  1,0xE1,
  0
};

const uint8_t PROGMEM PRX[]=
{
  2,0x20,0x7B,
  0
};

const uint8_t PROGMEM PTX[]=
{
  2,0x20,0x7A,
  0
};

#endif
