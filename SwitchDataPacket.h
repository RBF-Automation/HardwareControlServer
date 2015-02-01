#ifndef SWITCH_DATA_PACKET_H_
#define SWITCH_DATA_PACKET_H_
#include "DataPacket.h"
#include <cstdint>



class SwitchDataPacket: public DataPacket
{
public:
  uint32_t state;
};


#endif
