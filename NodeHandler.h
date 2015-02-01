#ifndef NODE_HANDLER_H_
#define NODE_HANDLER_H_

#include "DataPacket.h"

class NodeHandler
{
private:

public:
  NodeHandler();
  void InitRadio();
  bool WriteData(DataPacket*, int size);
  ~NodeHandler();


};

#endif
