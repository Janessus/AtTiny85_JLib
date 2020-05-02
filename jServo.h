#define SERVO_DATA_PORT PORTB
#define SERVO_DATA_PIN PB1

#define SERVO_PWR

#ifdef SERVO_PWR
  #define SERVO_PWR_PIN PB4
  #define SERVO_PWR_PORT PORTB

  void servoOn()
  {
    SERVO_PWR_PORT |= (1<<SERVO_PWR_PIN);
  }


  void servoOff()
  {
    SERVO_PWR_PORT &= ~(1<<SERVO_PWR_PIN);
  }
#endif


//pos 0 - 100
void servoPosition(uint8_t time, uint8_t pos)
{
  uint16_t low, high;

  if(pos > 100)
    pos = 100;

  //Correction curves for linear position(pos) behaviour
  // -- JAMARA Micro 9g
  high = (pos*pos/20 + 10*pos + 350);
  low = 14300 - high;

  //scale down resolution to prevent bug ---> for(...) _delay_us(1); does not work as expected, probably bc. low F_CPU (1mhz)
  high /= 10;
  low /= 10;

  for(int i = 0; i < time; i++)
  {
    SERVO_DATA_PORT |= (1<<SERVO_DATA_PIN);

    for(uint16_t t = high; t > 0; t--)
      _delay_us(10);
    SERVO_DATA_PORT &= ~(1<<SERVO_DATA_PIN);

    for(uint16_t t = low; t > 0; t--)
      _delay_us(10);
  }
}
