#ifndef MULTIOUTLETDATAPACKAT_H_
#define MULTIOUTLETDATAPACKAT_H_
#include "DataPacket.h"
#include <cstdint>



class MultiOutletDataPacket: public DataPacket
{
public:
  uint32_t state;
};


#endif
