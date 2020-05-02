
#ifndef PRINT_BUFFER_H
  #define PRINT_BUFFER_H

  #include <avr/io.h>
  #include <util/delay.h>

  #define TH 30 * 10//Hold Time
  #define TC 5  //End of Bit

  void printByte(char buffer)
  {
    for(int j = 0; j < 8; j++)
    {
      if(buffer & (1<<j))
        PORTB |= (1<<PB1);
      else
        PORTB &= ~(1<<PB1);

      _delay_ms(TH);
      PORTB &= ~(1<<PB1);
      _delay_ms(TC);
      PORTB |= (1<<PB1);
      _delay_ms(TC);
      PORTB &= ~(1<<PB1);
      _delay_ms(TC);
    }
  }

  void printBuffer(uint8_t * data, uint8_t length)
  {
    uint8_t i = 0;
    while(length--)
    {
      printByte(data[i]);
      i++;
      _delay_ms(TH + TH*4);
      PORTB &= ~(1<<PB1);
      _delay_ms(TC);
      PORTB |= (1<<PB1);
      _delay_ms(TC);
      PORTB &= ~(1<<PB1);
      _delay_ms(TC);
      PORTB |= (1<<PB1);
      _delay_ms(TC);
      PORTB &= ~(1<<PB1);
      _delay_ms(TC);
    }
  }

#endif
