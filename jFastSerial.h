#ifndef JSERIAL_H
  #define JSERIAL_H

  #include <avr/io.h>
  #include <util/delay.h>

  #include "jFastSerialConf.h"
  #include "./jTypes.h"

  #ifdef CHECKPAIRITY
    #include "pairityCheck.h"
  #endif

  //Default F_CPU for AtTiny85 on internal RC Oscillator
  #ifndef F_CPU
    #define F_CPU 1000000L
  #endif


  #ifdef RX
    //Read serial Byte
    uint8_t RdByte()
    {
    	uint8_t buffer = 0;
      uint16_t timeOut = BYTETIMEOUT;

    	while(!RX_D && timeOut--); //wait for rising edge

      if(timeOut == 0)
        return FALSE;

      _delay_us(BITDELAY + 5);

    	for(uint8_t c=0;c<8;c++)
    	{
    		buffer=buffer>>1; // shift to free MSB

    		if(RX_D)
    			buffer=buffer|128; //set MSB
    		_delay_us(BITDELAY);
    	}
    	return ~buffer;
    }


    //Receive startByte 3 times, then return true
    uint8_t receiveStart()
    {
      //Receive STARTBYTE 3 times to start receiving data
      if(RdByte() == STARTBYTE)
        if(RdByte() == STARTBYTE)
          if(RdByte() == STARTBYTE)
            return TRUE;
      return FALSE;
    }


    // Full receive Routine
    // try tro receive a message for <timeOut> times
    // this includes receiving the startsequence and basic verifying of content
    uint8_t receiveMessage(uint8_t * buffer, uint8_t size, uint8_t timeOut)
    {
      uint8_t lastByte = 0;
      uint8_t byte = 0;

      while(timeOut--)
      {
        if(receiveStart())
        {
          for(uint8_t k = 0; k < size;)
          {
            byte = RdByte();

            //no equal consecutive bytes allowed
            if((byte != FALSE) && (byte != lastByte))
            {
              buffer[k] = byte;
              lastByte = byte;
              k++;
            }
          }
          return TRUE;
        }
      }
      return FALSE;
    }


    #ifdef CHECKPAIRITY
      uint8_t receivePacket(jPacket * pack)
      {
        initializePacket(pack);

        if(receiveMessage(pack->data.raw, pack->rawSize, TIMEOUT))
          return correctData(pack->data.f.data, pack->size, pack->data.f.pairityVertical, pack->data.f.pairityHorizontal);
        return FALSE;
      }
    #endif
  #endif


  #ifdef TX
    // Write serial Byte
    void WrByte(uint8_t buffer)
    {
    	TX_HIGH;    // TXD = 1
    	_delay_us(BITDELAY - 5);
    	for (uint8_t c=0;c<8;c++)
    	{
    		if(!(buffer & 1))
    			TX_HIGH;    // TXD = 1
    		else
    			TX_LOW;   // TXD = 0
    		buffer=buffer>>1;
    		_delay_us(BITDELAY-1);
    	}
    	TX_LOW;   // TXD = 0
    }


    //send start-sequence
    void sendStart()
    {
      //send startByte 3 times
      WrByte(STARTBYTE);
      _delay_us(STARTDELAY);
      WrByte(STARTBYTE);
      _delay_us(STARTDELAY);
      WrByte(STARTBYTE);
      _delay_us(STARTDELAY);
    }


    //send buffer (no start sequence)
    void sendByte(uint8_t byte)
    {
      //resend every byte      vvv      times
      for(int k = 0; k < BYTE_REDUNDANCY; k++)
      {
        //send data
        WrByte(byte);
        _delay_us(SENDDELAY);
      }
    }


    //Send a full message with startsequence
    void sendMessage(uint8_t * buffer, uint8_t size)
    {
      sendStart();
      for(uint8_t i = 0; i < size; i++)
      {
        sendByte(buffer[i]);
        _delay_us(BYTEDELAY);
      }
    }


    #ifdef CHECKPAIRITY
      void sendPacket(uint8_t * buffer)
      {
        jPacket pack;
        initializePacket(&pack);

        writeData(&pack, buffer);
        pack.data.f.pairityVertical = getVerticalPairity(buffer, pack.size);
        pack.data.f.pairityHorizontal = getHorizontalPairity(buffer, pack.size);

        sendMessage(pack.data.raw, pack.rawSize);
      }
    #endif
  #endif
#endif
