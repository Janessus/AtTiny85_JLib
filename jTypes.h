#ifndef JTYPES_H
  #define JTYPES_H

  #include <stdint.h>
  #include <avr/io.h>

  #include "jPacket.h"

  #define TRUE 1
  #define FALSE 0


  void true()
  {
  	PORTB |= (1<<PB1);
  	_delay_ms(5);
  	PORTB &= ~(1<<PB1);
  	_delay_ms(5);
  }


  void false()
  {
  	PORTB |= (1<<PB1);
  	_delay_ms(1);
  	PORTB &= ~(1<<PB1);
  	_delay_ms(1);
  	PORTB |= (1<<PB1);
  	_delay_ms(1);
  	PORTB &= ~(1<<PB1);
  	_delay_ms(1);
  }
#endif
