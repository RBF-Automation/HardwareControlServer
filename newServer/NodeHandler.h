#ifndef NODE_HANDLER_H_
#define NODE_HANDLER_H_

#include "DataPacket.h"
#include <cstdint>
class NodeHandler
{
private:
  uint64_t writingPipe;
public:
  NodeHandler();
  void InitRadio();
  bool WriteData(DataPacket*, int size);
  void SetWritingPipe(uint64_t pipe);
  ~NodeHandler();


};

#endif
