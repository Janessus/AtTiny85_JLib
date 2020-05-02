#ifndef PAIRITYCHECK_H
  #define PAIRITYCHECK_H
/*
  | | | | | | | | |   |
  | | | | | | | | |   |
  | | | | | | | | |   V
  | | | | | | | | | VerticalPairity
  | | | | | | | | |
  | | | | | | | | |
  | | | | | | | | |
  | | | | | | | | |
  ==> HorizontalPairity
*/

  #define USE_CORRECTION
  //Maximum size is 8
  uint8_t getVerticalPairity(uint8_t * data, uint8_t size)
  {
    uint8_t pairity = 0;
    uint8_t count = 0;

    for(uint8_t i = 0; i < size; i++)
    {
      count = 0;
      for(uint8_t k = 0; k < 8; k++)
      {
        count += ((data[i] & (1<<k)) > 0);
      }
      pairity |= ((count % 2)<<i);

      //if(i != (size - 1))
        //pairity <<= 1;
    }
    return pairity;
  }


  //Maximum size is 8
  uint8_t getHorizontalPairity(uint8_t * data, uint8_t size)
  {
    uint8_t pairity = 0;
    uint8_t count = 0;

    for(uint8_t i = 0; i < 8; i++)
    {
      count = 0;

      for(uint8_t k = 0; k < size; k++)
      {
        count += ((data[k] & (1<<i)) > 0);
      }
      pairity |= ((count % 2)<<i);
    }
    return pairity;
  }

  //returns 0 if there is an error
  uint8_t check2DPairity(uint8_t * data, uint8_t size, uint8_t pairityVertical, uint8_t pairityHorizontal)
  {
    if((getVerticalPairity(data, size) == pairityVertical)
    && (getHorizontalPairity(data, size) == pairityHorizontal))
      return 1;
    return 0;
  }


  #ifdef USE_CORRECTION
    //counts how many '1's are in a binary number
    uint8_t countOnes(uint8_t num)
    {
      uint8_t count = 0;
      for(uint8_t k = 0; k < 8; k++)
      {
        count += ((num & (1<<k)) > 0);
      }
      return count;
    }

    //correct 1 bit error if possible
    uint8_t correctData(uint8_t * data, uint8_t size, uint8_t pairityVertical, uint8_t pairityHorizontal)
    {
      if(!check2DPairity(data, size, pairityVertical, pairityHorizontal))
      {
        uint8_t compPairityV = getVerticalPairity(data, size);
        uint8_t compPairityH = getHorizontalPairity(data, size);

        uint8_t verticalError = pairityVertical ^ compPairityV;
        uint8_t horizontalError = pairityHorizontal ^ compPairityH;

        uint8_t vIndex, hIndex;
        uint8_t vCount = countOnes(verticalError);
        uint8_t hCount = countOnes(horizontalError);

        vIndex = 0;
        hIndex = 0;

        // 1 bit error can be corrected
        if((vCount == 1) && (hCount == 1))
        {
          while((verticalError >> vIndex) > 1)
          vIndex++;
          while((horizontalError >> hIndex) > 1)
          hIndex++;
          //flip bit
          data[vIndex] ^= (1<<hIndex);
          return 1;
        }
        return 0;
      }
      return 1;
    }
    
  #endif
#endif
