#ifndef MULTISWITCHDATAPACKAT_H_
#define MULTISWITCHDATAPACKAT_H_
#include "DataPacket.h"
#include <cstdint>



class MultiSwitchDataPacket: public DataPacket
{
public:
  uint32_t outletNum;
  uint32_t state;
};


#endif
