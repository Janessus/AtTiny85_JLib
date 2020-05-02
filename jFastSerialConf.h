#ifndef JSERIALCONF_H
  #define JSERIALCONF_H

  #define TIMEOUT  30//Max retry's for RX message

  #define RX_PORT PINB
  #define RX_PIN PB0

  #define RX_D (RX_PORT & (1<<RX_PIN))

  #define TX_PORT PORTB
  #define TX_PIN PB1

  #define TX_HIGH (PORTB |= (1<<TX_PIN))
  #define TX_LOW (PORTB &= ~(1<<TX_PIN))

  #define BYTE_REDUNDANCY 1 //Resend every Byte x times
  #define BUFFSIZE 8


//Timing Section
  #define BITDELAY 120
  #define STARTBYTE 0xA5
  //uint16_t (timeout for rising edge listen)
  #define BYTETIMEOUT 0x08FF;


  #define STARTDELAY 200
  #define SENDDELAY 300

  #define BYTERATE 100000
  #define BYTEDELAY 1000000/BYTERATE

  // uncomment desired behaviour or define in code
  //#define RX
  //#define TX
  //#define CHECKPAIRITY
#endif
