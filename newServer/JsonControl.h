#ifndef JSON_CONTROL_H_
#define JSON_CONTROL_H_
#include "SwitchDataPacket.h"

class JsonControl
{
private:

public:
  JsonControl();
  void DecodeJsonObject(const char*jsonData);
  ~JsonControl();

};

#endif
