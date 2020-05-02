#define DATA_BYTES 8
#define PAIRITY_BYTES 2
#define PACKETSIZE (DATA_BYTES + PAIRITY_BYTES + 1) // +1 bc packetIndex


struct jPacket
{
  uint8_t size;// = DATA_BYTES;
  uint8_t pairityBytes;// = PAIRITY_BYTES;
  uint8_t rawSize;
  union
  {
    uint8_t raw[PACKETSIZE];
    struct
    {
      uint8_t data[DATA_BYTES];
      uint8_t pairityVertical;
      uint8_t pairityHorizontal;
      uint16_t packetIndex;
    } f;
  } data;
};

typedef struct jPacket jPacket;


void writeData(jPacket * pack, uint8_t * src)
{
  for(uint8_t i = 0; i < pack->size; i++)
    pack->data.f.data[i] = src[i];
}

void writeRaw(jPacket * pack, uint8_t * src)
{
  for(uint8_t i = 0; i < pack->rawSize; i++)
    pack->data.f.data[i] = src[i];
}

void initializePacket(jPacket * pack)
{
  pack->size = DATA_BYTES;
  pack->pairityBytes = PAIRITY_BYTES;
  pack->rawSize = PACKETSIZE;

  pack->packetIndex = 0;

  // initializeBuffer with 0's
  for(uint8_t i = 0; i < PACKETSIZE; i++)
    pack->data.raw[i] = 0;
}
