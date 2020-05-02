
#ifndef CRC8_H
  #define CRC8_H

  #define POLYNOMIAL 0xA5

  //checksum for 1 byte
  uint8_t crc8(uint8_t data)
  {
    uint8_t crc = 0xFF; // same as previousCrc32 ^ 0xFFFFFFFF

    crc ^= data++;
    for (uint8_t j = 0; j < 8; j++)
      if (crc & 1)
        crc = (crc >> 1) ^ POLYNOMIAL;
      else
        crc =  crc >> 1;
    return ~crc; // same as crc ^ 0xFFFFFFFF
  }
#endif
